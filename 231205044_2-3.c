/**
 * クラス：A
 * 学籍番号:231205044
 * 氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>
#define N (5)

/*qsortのための比較関数定義*/
int compare(void *a, void *b)
{
    if (*(double *)a > *(double *)b)
    {
        return 1;
    }
    else if (*(double *)a < *(double *)b)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    double x[N] = {178.1, 185.2, 175.3, 168.9, 178.5};
    double m;
    
    /*配列データのソート*/
    qsort(x, N, sizeof(double), compare);
    if (N % 2 == 0)
    {
        m = (x[N/2 - 1] + x[N/2]) / 2;
    }
    else
    {
        m = x[N/2];
    }


    printf("Median = %.2f\n", m);
    return 0;
}