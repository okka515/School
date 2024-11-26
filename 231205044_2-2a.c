/**
 * クラス:A
 * 学籍番号:231205044
 * 氏名:岡田采留
 */
#include <stdio.h>
#define N (3)

int main (void)
{
    int i, j;
    int x[N][N] = {{2, 0, 5},
                   {1, 4, 6},
                   {8, 7, 3}};

    printf("Before:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf(" %d", x[i][j]);
        }
        printf("\n");
    }

    /*転置行列の操作プログラムをここに挿入*/
    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            int temp = x[i][j];
            x[i][j] = x[j][i];
            x[j][i] = temp;
        }
    }

    printf("After:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf(" %d", x[i][j]);
        }
        printf("\n");
    }
    return 0;
}