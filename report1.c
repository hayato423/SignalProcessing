#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc , char *argv[]) {
    FILE *fp;
    double freq,time;
    // double freq = atof(argv[1]);
    // double time = atof(argv[2]);
    printf("freq: "); scanf("%lf",&freq);
    printf("time: "); scanf("%lf",&time);
    printf("\n");
    double interval = 1.0 / freq;
    fp  = fopen(argv[1],"w");
    double t;
    int N = 3;
    for(t = 0.0 ; t < time; t += interval)
    {
        double y = cos(400*M_PI*t) + 2 * sin(1300*M_PI*(t+1));
        fprintf(fp,"%lf\n",y);
    }
    fclose(fp);
    return 0;
}
