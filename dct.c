#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#define MAX_SIZE 4096
int DCT(int , double*, double*);
int iDCT(int ,double*, double*);
double rounding(double,int);

double input[MAX_SIZE] ,output[MAX_SIZE] /*,output_idct[MAX_SIZE]*/;
int main(int argc, char *argv[]){
    FILE *fp;
    fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("ファイル読み込みエラー\n");
        return -1;
    }
    int n = 0;
    while(fscanf(fp,"%lf",&input[n]) != EOF){
        n++;
    }
    fclose(fp);
    int m;
    printf("DCT:0,iDCT:1 ");
    scanf("%d",&m);
    if(m == 0)
        DCT(n,input,output);
    else
        iDCT(n,input,output);
    fp = fopen(argv[2],"w");
    int i = 0;
    for(i = 0; i < n; i++){
        fprintf(fp,"%lf\n",output[i]);
    }
    fclose(fp);
    // if(m == 1) {
    // iDCT(n,input,output);
    // fp = fopen(argv[3],"w");
    // for(i = 0; i < n; i++) {
    //     fprintf(fp,"%lf\n",output[i]);
    // }
    // fclose(fp);
    // }
}

int DCT(int N, double *input, double *output){
    int k;
    for(k = 0;k < N; k++) {
        int i;
        for(i = 0; i < N;i++) {
            output[k] += input[i] * cos((2.0*i+1.0) * k * M_PI/ (2.0*N));
        }
        //output[k] = rounding(output[k],0);
    }
    return 0;
}

int iDCT(int N,double *input, double *output) {
    int n;
    for(n = 0; n < N; n++) {
        int k;
        output[n] += input[0] / 2.0;
        for(k = 1; k < N;k++) {
            output[n] += input[k] * cos((2*n+1)*k*M_PI/(2.0*N));
        }
        output[n] = output[n] * 2 / N;
    }
    return 0;
}

double rounding(double x,int n) {
  x = x * pow(10,n);
  x = floor(x+0.5) / pow(10,n);
  return x;
}
