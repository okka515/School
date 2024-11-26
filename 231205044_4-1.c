/**
 * クラス：A
 * 学籍番号：231205044
 * 氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUT_FILE "./juyo/juyo-2014.csv"
#define MAX_LINE_LENGTH 1024
#define DAY_HOURS 24

int main() 
{
    FILE *fp = NULL;
    char line[MAX_LINE_LENGTH];
    int year, month, day;
    
    /*ファイルを読みだして，例外処理*/
    fp = fopen(OUT_FILE, "r");
    if (fp == NULL) 
    {
        printf("Couldn't open %s\n", OUT_FILE);
        exit(EXIT_FAILURE);
    }

    /*一行分を取得して文字を年月日を抽出して表示*/
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        /*lineにコピーした文字列をyear,month,dayに格納*/=
        sscanf(line, "%d/%d/%d", &year, &month, &day);
        /*2014年の7-9月を条件分岐*/
        if (year == 2014 && month >= 7 && month <= 9) 
        {
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}