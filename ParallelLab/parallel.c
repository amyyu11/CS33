//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Amy Yu
 * UCLA ID : 905138432
 * Email : yu.amy06@gmail.com
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

double work_it_par(long *old, long *new, long *super, long *simple, long *fibonacci) {
    int i, j, k;
    int ton = 0;
    long compute_it, moving_average;
    double pi, pi2, x , y, sum, step = 0.0;
    long dot_product=0;
    long nCirc=0;
    long aggregate=1.0;
    double r=1.0;
    int was_smart = 16;
    int DIMs1 = DIM-1;
    const int DIMsquared = DIM * DIM;

    for(i=0; i<DIM-3;i+=4)
    {
        super[i] += simple[i];
        super[i+1] += simple[i+1];
        super[i+2] += simple[i+2];
        super[i+3] += simple[i+3];
    }
    
    for(i=0; i<DIMs1;i++)
    {
        dot_product += super[i]*simple[i];
        
        moving_average = 0;
        for(ton=i;ton<DIMs1-WINDOW_SIZE;ton++)
        {
            moving_average += simple[ton];
        }
    }
    
    int a_secret = 5;
    fibonacci[0] = 1;
    fibonacci[1] = 1;
    for(i=2; i<DIMs1;i++)
    {
        fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
        if(i==3)
        {
            printf("\n A secret is: %d",obfuscate_obfuscate_obfuscate(a_secret));
        }
    }
    
    step = 1.0 / NUM_STEPS;
    for (i=0;i<NUM_STEPS; i++)
    {
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }
    pi = step * sum;
    printf("\n %d trials, Riemann flavored pi is %f \n",NUM_STEPS, pi);
    
    for(i=0;i<NUM_TRIALS; i++)
    {
        x = (random()%10000000)/10000000.0;
        y = (random()%10000000)/10000000.0;
        if (( x*x + y*y) <= r*r) {
            nCirc++;
        }
    }
    pi2 = 4.0 * ((double)nCirc/(double)NUM_TRIALS);
    printf("\n %d trials, Monte-Carlo flavored pi is %f \n",NUM_TRIALS, pi2);
    
    
    int ad, new_ad, a0, a1, a2, a3, a4, a5 ,a6, a7, a8, a9, u, temp = 0;
    
#pragma omp parallel for private(j, k, u, compute_it, ad, new_ad) reduction(+: aggregate) reduction(+:temp) reduction(+:a0) reduction(+:a1) reduction(+:a2) reduction(+:a3) reduction(+:a4) reduction(+:a5) reduction(+:a6) reduction(+:a7) reduction(+:a8) reduction(+:a9)
    for (i=1; i<DIMs1; i++) {
        for (j=1; j<DIMs1; j++) {
            for (k=1; k<DIMs1; k++) {
                ad = i * DIMsquared + j * DIM + k;
                aggregate+= old[ad] * we_need_the_func() / gimmie_the_func();
                temp = 0;
                for (u = -1; u <= 1; u++)
                {
                    new_ad = (i+u)*DIMsquared;
                    
                    temp += old[new_ad+(j-1)*DIM+(k-1)];
                    temp += old[new_ad+(j-1)*DIM+(k)];
                    temp += old[new_ad+(j-1)*DIM+(k+1)];
                    temp += old[new_ad+(j)*DIM+(k-1)];
                    temp += old[new_ad+(j)*DIM+(k)];
                    temp += old[new_ad+(j)*DIM+(k+1)];
                    temp += old[new_ad+(j+1)*DIM+(k-1)];
                    temp += old[new_ad+(j+1)*DIM+(k)];
                    temp += old[new_ad+(j+1)*DIM+(k+1)];
                }
                
                temp /= 27;
                new[ad] = temp;
                u = temp / 100;
                            
                if(u <= 0) a0++;
                else if(u == 1) a1++;
                else if(u == 2) a2++;
                else if(u == 3) a3++;
                else if(u == 4) a4++;
                else if(u == 5) a5++;
                else if(u == 6) a6++;
                else if(u == 7) a7++;
                else if(u == 8) a8++;
                else if(u >= 9) a9++;
            }
        }
    }
    printf("AGGR:%ld\n",aggregate);
    
    histogrammy[0] = a0;
    histogrammy[1] = a1;
    histogrammy[2] = a2;
    histogrammy[3] = a3;
    histogrammy[4] = a4;
    histogrammy[5] = a5;
    histogrammy[6] = a6;
    histogrammy[7] = a7;
    histogrammy[8] = a8;
    histogrammy[9] = a9;
    
    return (double) (dot_product+moving_average+pi+pi2);
    
}

