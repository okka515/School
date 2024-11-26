/**
 * クラス：A
 * 学籍番号：231205044
 * 氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char msg[][20] = {"Welcome", "to", "Meijo", "University"};
    char out[1000] = {0};

    /*文字列を末尾にコピー*/
    for (int i = 0; i < sizeof(msg) / sizeof(msg[0]); i++)
    {
        strcat(out, msg[i]);
        /*単語間に空白を挿入(最後の単語には空白入れない)*/
        if (i < sizeof(msg) / sizeof(msg[0]) - 1)
        {
            strcat(out, " ");
        }
    }

    printf("<<%s>>\n", out);
    return EXIT_SUCCESS;
}