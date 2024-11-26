/*
* 作者名：岡田 采留
* 学籍番号：231205044
* 課題番号1-1B
* 作成日:2024/9/17
*/
#include <stdio.h>
int main(void)
{
    const int MIN_MULTIPLICATION_TABLE = 1; // 九九の被乗数と乗数の最小値
    const int MAX_MULTIPLICATION_TABLE = 9; // 九九の被乗数と乗数の最大値

    // 九九を計算する処理(被乗数が乗数以下の場合のみ表示)
    for (int i = MIN_MULTIPLICATION_TABLE; i <= MAX_MULTIPLICATION_TABLE; i++) //被乗数のfor文
    {
        for (int j = i; j <= MAX_MULTIPLICATION_TABLE; j++) //乗数のfor文
        {
            printf("%d * %d = %d\n", i, j, i * j);
        }
    }
    return 0;
}
