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
    char line_copy[MAX_LINE_LENGTH];
    char *token = NULL;
    int year, month, day, hour;
    int sum_data[DAY_HOURS] = {0};
    int sum_num[DAY_HOURS] = {0};
    
    // ファイルを読み込んでエラー処理
    fp = fopen(OUT_FILE, "r");
    if (fp == NULL) 
    {
        printf("Couldn't open %s\n", OUT_FILE);
        exit(EXIT_FAILURE);
    }

    // ファイルの1行分を取得
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        strcpy(line_copy, line);                // line_copyに文字列lineをコピー
        token = strtok(line, ",");              // コンマでlineを分割
        sscanf(token, "%d/%d/%d", &year, &month, &day); // lineにコピーした文字列をyear, month, dayに格納
        
        // 2014年の7-9月を条件分岐
        if (year == 2014 && month >= 7 && month <= 9) 
        {
            token = strtok(NULL, ",");          // 次のトークンへ移動
            hour = strtol(token, NULL, 10);
            token = strtok(NULL, ",");          // 次のトークンへ移動
            sum_data[hour] += strtol(token, NULL, 10);
            sum_num[hour]++;
        }
    }

    fclose(fp);

    // コンソールに一時間ごとの平均消費電力を表示
    printf("2014年:");
    for (int i = 0; i < DAY_HOURS; i++)
    {
        int ave = sum_data[i] / sum_num[i];
        printf(" %d", ave);
    }
    return 0;
}
