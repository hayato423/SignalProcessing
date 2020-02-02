#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#define MAX_SIZE 4096

//N:FFTのポイント数 fs:サンプリング周波数   f[n] = fs/N * n (n = 0 ... N-1)

typedef struct COMPLEX {
  double Re;
  double Im;
} complex;

int DFT(int, complex *, complex *);
int iDFT(int, complex *, complex *);
double rounding(double,int);

// double input[MAX_SIZE];
complex output[MAX_SIZE] = {0.0, 0.0};
complex input[MAX_SIZE] = {0.0, 0.0};

int difftime;
struct timeval start,finish;


double time[MAX_SIZE];
int main(int argc, char *argv[]) {
  int i = 0;
  int N = 0;
  FILE *fp;
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("ファイル読み込みエラー\n");
    return -1;
  }
  printf("DFT:0,iDFT:1 ");
  int m = 0;
  scanf("%d", &m);
  if (m == 0) {     //DFT
    while (fscanf(fp, "%lf %lf",&time[N] ,&input[N].Re) != EOF) {
      // printf("%lf %lf\n",input[N].Re,input[N].Im);
      N++;
    }
    fclose(fp);
    printf("N:%d\n",N);
    DFT(256, input, output);
  } else {      //iDFT
    while (fscanf(fp, "%lf %lf", &input[N].Re, &input[N].Im) != EOF) {
      N++;
    }
    fclose(fp);
    iDFT(N, input, output);
  }
  fp = fopen(argv[2], "w");
  for (i = 0; i < N; i++) {
     fprintf(fp, "%lf %lf\n", i, output[i].Re, output[i].Im);
    //fprintf(fp,"%lf\n",output[i].Re);
  }
  fclose(fp);
}

int DFT(int N, complex *input, complex *output) {
  int k;
  for (k = 3839; k < N; k++) {
    int n;
    for (n = 3839; n < N; n++) {
      output[k].Re += input[n].Re * cos((-1) * 2 * M_PI * k * n / N) - input[n].Im * sin((-1) * 2 * M_PI * k * n / N);
      output[k].Im += input[n].Re * sin((-1) * 2 * M_PI * k * n / N) + input[n].Im * cos((-1) * 2 * M_PI * k * n / N);
      // output[k].Re += input[n] * cos((-1)*2 * M_PI * k * n / N);
      // output[k].Im += input[n] * sin((-1)*2 * M_PI * k * n / N);
    }
    //  output[k].Re = rounding(output[k].Re,2);
    //  output[k].Im = rounding(output[k].Im,2);
  }
  return 0;
}

int iDFT(int N, complex *input, complex *output) {
  int k;
  for (k = 0; k < N; k++) {
    int n;
    for (n = 0; n < N; n++) {
      output[k].Re += input[n].Re * cos(2 * M_PI * k * n / N) - input[n].Im * sin(2 * M_PI * k * n / N);
      output[k].Im += input[n].Re * sin(2 * M_PI * k * n / N) + input[n].Im * cos(2 * M_PI * k * n / N);
    }
    output[k].Re = output[k].Re / N;
    output[k].Im = output[k].Im / N;
  }
  return 0;
}


double rounding(double x,int n) {
  x = x * pow(10,n);
  x = floor(x+0.5) / pow(10,n);
  return x;
}
