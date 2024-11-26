/**
 * クラス：A
 * 学籍番号：231205044
 * 氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*my_strdupの定義関数はここに記述する*/
char *my_strdup(const char *str)
{
    int memory = sizeof(str) + sizeof(char); /*\0文の領域の確保*/
    char *str1 = NULL;
    str1 = malloc(memory); /*malloc関数により，ヒープ領域にメモリを確保*/
    return str1;
}

int main(void)
{
    char *s1 = "Meijo University";
    char *s2 = NULL;
    /*s2にs1の文字列をコピーする(違うアドレス)*/
    s2 = my_strdup(s1);


    /*各々が格納されている領域のアドレスは異なる*/
    printf("Address of s1 = %p\n", s1);
    printf("Address of s2 = %p\n", s2);

    /*しかし内容は同一*/
    printf("s1 = %s\n", s1);
    printf("s2 = %s\n", s2);

    /*strdup関数が作ったコピーのメモリ領域を解放*/
    free(s2);
    s2 = NULL;

    return 0;
}
