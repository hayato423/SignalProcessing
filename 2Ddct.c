#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#define MAX_SIZE 4096
//入力によって数字を変える
#define m 8  //行
#define n 8  
//列
// const int m = 4, n = 4;

// Function to find discrete cosine transform and print it
int dctTransform(double matrix[][n]) {
  int i, j, k, l;

  // dct will store the discrete cosine transform
  double dct[m][n];

  double ci, cj, dct1, sum;

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      // ci and cj depends on frequency as well as
      // number of row and columns of specified matrix
      if (i == 0)
        ci = 1 / sqrt(m);
      else
        ci = sqrt(2) / sqrt(m);
      if (j == 0)
        cj = 1 / sqrt(n);
      else
        cj = sqrt(2) / sqrt(n);

      // sum will temporarily store the sum of
      // cosine signals
      sum = 0;
      for (k = 0; k < m; k++) {
        for (l = 0; l < n; l++) {
          dct1 = matrix[k][l] * cos((2 * k + 1) * i * M_PI / (2 * m)) *
                 cos((2 * l + 1) * j * M_PI / (2 * n));
          sum = sum + dct1;
        }
      }
      dct[i][j] = sum;
    }
  }

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("%f\t", dct[i][j]);
    }
    printf("\n");
  }
  return 1;
}

// Driver code
int main(int argc, char *argv[]) {
  double matrix[m][n];
  FILE *fp;
  fp = fopen(argv[1], "r");
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      fscanf(fp, "%lf", &matrix[i][j]);
    }
  }
  fclose(fp);
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("%lf ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  dctTransform(matrix);
  return 0;
}
