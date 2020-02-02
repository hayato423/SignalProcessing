#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#define MAX_SIZE 4096
#define m 4         //行 y
#define n 4         //列 x

typedef struct COMPLEX {
  double Re;
  double Im;
} complex;

complex input[m][n],output[m][n] = {0,0};

int main(int argc ,char *argv[]) {
    FILE *fp;
    fp = fopen(argv[1],"r");
    int i,j;
    for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      fscanf(fp, "%lf", &input[i][j].Re);
      input[i][j].Im = 0;
    }
  }
  fclose(fp);
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("%lf %lf",input[i][j].Re,input[i][j].Im);
      printf(" | ");
    }
    printf("\n");
  }
  printf("\n");
  dft(input,output);
  for(i = 0;i < m; i++) {
      for(j = 0; j < n; j++) {
          printf("%lf %lf",output[i][j].Re,output[i][j].Im);
          printf(" | ");
      }
      printf("\n");
  }

}


dft(complex input[][n],complex output[][n]) {
    int u,v,x,y;
    complex temp[m+1][n+1];
    //x軸方向
    for(y = 0; y < m; y++) {
        for(u = 0; u < n; u++) {
            for(x = 0; x < n; x++) {
                double angle = 2.0*M_PI*x*u/n;
                temp[y][u].Re += input[y][x].Re * cos(angle) + input[y][x].Im * sin(angle);
                temp[y][u].Im += input[y][x].Im * cos(angle) - input[y][x].Re * sin(angle);
            }
        }
    }
    //y軸方向
    for(u = 0; u < n; u++) {
        for(v = 0; v < m; v++) {
            for(y = 0; y < m; y++) {
                double angle = 2.0*M_PI*y*v/m;
                output[v][u].Re += temp[y][u].Re * cos(angle) + temp[y][u].Im * sin(angle);
                output[v][u].Im += temp[y][u].Im * cos(angle) - temp[y][u].Re * sin(angle);
            }
        }
    }

}
