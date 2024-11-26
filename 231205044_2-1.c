/**
 * クラス:A
 * 学籍番号:231205044
 * 氏名:岡田采留
 */
#include <stdio.h>

int my_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

int main(void) 
{
    printf("%d\n", my_strlen("Hello,World!"));
    printf("%d\n", my_strlen("Meijo University"));
    printf("%d\n", my_strlen(""));
    return 0;
}