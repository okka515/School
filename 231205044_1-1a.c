/*
* 作者名：岡田 采留
* 学籍番号：231205044
* 課題番号1-1A
* 作成日:2024/9/17
*/
#include <stdio.h>
int main(void)
{
    const int MIN_MALTIPLICATION_TABLE = 1; // 九九の被乗数と乗数の最小値
    const int MAX_MALTIPLICATION_TABLE = 9; // 九九の被乗数と乗数の最大値

    // 九九を計算する処理
    for (int i = MIN_MALTIPLICATION_TABLE; i <= MAX_MALTIPLICATION_TABLE; i++)
    {
        for (int j = MIN_MALTIPLICATION_TABLE; j <= MAX_MALTIPLICATION_TABLE; j++)
        {
            printf("%d * %d = %d\n", i, j, i * j);
        }
    }
    return 0;
}
