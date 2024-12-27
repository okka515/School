#include <stdio.h>
#include <ctype.h> // isalphaを使用するために必要

int main(void)
{
    char *a = "My name is Ayato Okada -- Nice to meet you"; // ポインタで文字列を格納
    char *p = a; // ポインタを使って文字列を操作

    // 文字列の末尾までループ
    while (*p != '\0') // ポインタがヌル文字を指すまで繰り返す
    {
        if (isalpha(*p)) // 現在の文字がアルファベットか判定
        {
            printf("Character '%c' is an alphabet.\n", *p);
        }
        else
        {
            printf("Character '%c' is not an alphabet.\n", *p);
        }
        p++; // 次の文字を指す
    }

    return 0;
}
