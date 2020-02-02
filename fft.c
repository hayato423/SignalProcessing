#define _USE_MATH_DEFINES
#define MAX_SIZE 4096

#include <math.h>
#include <stdio.h>
//#include <sys/time.h>

//実虚数型
typedef struct COMPLEX {
  double Re;
  double Im;
} complex;

int power(int);
int bit_inverse(int, complex *);
int block(int, int, complex *, complex *);
complex W(double, double);
int fft(int, complex *, complex *);
double rounding(double, int);

complex input[5][MAX_SIZE] = {0.0, 0.0};
complex output[5][MAX_SIZE] = {0.0, 0.0};
double amp_s[MAX_SIZE] = {0.0};
double pha_s[MAX_SIZE] = {0.0};
double pow_s[MAX_SIZE] = {0.0};

int difftime;
double time[MAX_SIZE];
int main(int argc, char *argv[]) {
  int i, j, N, mode;
  N = 0;
  FILE *fp;
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("ファイル読み込みエラー\n");
    return -1;
  }
  printf("fft:0,ifft:1");
  scanf("%d", &mode);
  if (mode == 0) {
    while (fscanf(fp, "%lf %lf %lf %lf %lf %lf", &time[N], &input[0][N].Re,
                  &input[1][N].Re, &input[2][N].Re, &input[3][N].Re,
                  &input[4][N].Re) != EOF) {
      N++;
    }
    fclose(fp);
    for (i = 0; i < 5; i++) {
      bit_inverse(N, input[i]);
      fft(N, input[i], output[i]);
    }
  }
  fp = fopen(argv[2], "w");
  for (j = 0; j < 5; j++) {
    double ans = 0;
    for (i = 0; i < N; i++) {
      ans += pow(output[j][i].Re, 2) + pow(output[j][i].Im, 2);
      // fprintf(fp, "%lf %lf\n", rounding(output[i].Re,2),
      // rounding(output[i].Im,2));
    }
    fprintf(fp,"%lf ",ans/N);
  }
  fclose(fp);
}

//ビット反転および並び替え
int bit_inverse(int n, complex *input) {
  complex temp[MAX_SIZE];
  int i, j, k, num, ans;
  int m = power(n);
  int p1, p2;
  // inputの値をコピー
  for (i = 0; i < n; i++) {
    temp[i] = input[i];
  }
  for (i = 0; i < n; i++) {
    ans = 0;
    j = 0;
    num = i;
    int bin[10] = {0};
    // 10進数から2進数に変換
    while (num > 0) {      // numが0になるまで0で割り続ける
      bin[j++] = num % 2;  // 0で割った余りを代入
      num = num / 2;
    }
    p1 = m - 1;
    p2 = 0;
    //入れ替え作業
    while (p1 > (m - 1) / 2) {  // p1がbin配列の真ん中を超えるまで繰り返し
      int temp = bin[p1];
      bin[p1] = bin[p2];
      bin[p2] = temp;
      p1 -= 1;
      p2 += 1;
    }
    // 2指数を10進数に変換
    for (k = m - 1; k >= 0; --k) {
      ans += pow(2, k) * bin[k];
      // printf("%d",bin[k]);
    }
    // printf("%d\n",ans);
    input[i] = temp[ans];
  }
}

//引数nが2の何乗かを返す
int power(int n) {
  double m = log(n) / log(2.0);
  return (int)m;
}

//ブロック
int block(int N, int index, complex *input, complex *output) {
  int n;
  int offset = N / 2;
  for (n = index; n < N + index; n++) {
    complex w = W(n % N, N);
    if (n < N / 2 + index) {  //上半分
      output[n].Re = input[n].Re + input[n + offset].Re * w.Re -
                     input[n + offset].Im * w.Im;
      output[n].Im = input[n].Im + input[n + offset].Re * w.Im +
                     input[n + offset].Im * w.Re;
    } else {  //下半分
      output[n].Re =
          input[n - offset].Re + input[n].Re * w.Re - input[n].Im * w.Im;
      output[n].Im =
          input[n - offset].Im + input[n].Re * w.Im + input[n].Im * w.Re;
    }
    // printf("output[%d] : %lf %lf ,
    // offset:%d\n",n,output[n].Re,output[n].Im,offset);
  }
  // printf("\n");
}

//回転子
complex W(double m, double N) {
  complex w;
  w.Re = cos((-1) * 2 * M_PI * m / N);
  w.Im = sin((-1) * 2 * M_PI * m / N);
  return w;
}

int fft(int N, complex *input, complex *output) {
  int i, j, n,
      index;  // index:ブロック計算の開始時のnの値.これが無いとずっと最初の２つで計算し続けることになる
  int m = power(N);
  for (i = 1; i <= m;
       i++) {  //ステップ数はlog2(データ数).ここはステップ数だけ繰り返す
    index = 0;
    n = pow(2, i);
    for (j = 0; j < pow(2, m - i); j++) {  //ステップとブロックの関係:ブロック数
                                           //= 2^(ステップ数-ステップi番目)
      block(n, index, input, output);
      index += n;
    }
    for (j = 0; j < N; j++) {
      input[j] = output[j];
    }
  }
}

int ifft(int N, complex *input, complex *output) {
  fft(N, input, output);
  int k;
  for (k = 0; k < N; k++) {
    output[k].Re /= N;
    output[k].Im /= N;
  }
}

double rounding(double x, int n) {
  x = x * pow(10, n);
  x = floor(x + 0.5) / pow(10, n);
  return x;
}
