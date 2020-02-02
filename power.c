#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#define MAX_SIZE 4096

typedef struct COMPLEX
{
    double Re;
    double Im;
} complex;

complex input[MAX_SIZE] = {0.0,0.0};
int main(int argc , char* argv[]) {
    FILE *fp;
    fp = fopen(argv[1],"r");
    int N = 0;
    while( fscanf(fp,"%lf %lf",&input[N].Re,&input[N].Im) != EOF)
    {
        N++;
    }
    fclose(fp);
    fp = fopen(argv[2],"w");
    int n;
    for(n = 0; n < N; n++)
    {
        double power = pow(input[n].Re,2) + pow(input[n].Im,2);
        fprintf(fp,"%d %lf\n",n,power);
    }
    fclose(fp);
    return 0;
}
