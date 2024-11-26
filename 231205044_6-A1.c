/**
 * クラス：A
 * 学籍番号：231205044
 * 氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_LEN 1024

// エラーメッセージ出力関数
void error_message()
{
    fprintf(stderr, "usage: 231205044_6-3 [options...] <input file> <output file>\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "   -p   : enable pass-through mode\n");
    fprintf(stderr, "   -h   : display this message\n");
}

int main(int argc, char *argv[])
{
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    char buffer[MAX_LEN];
    bool is_p = false; // pコマンドのブール管理
    int c;
    // コマンドライン引数の解析
    if (argc < 3)
    {
        error_message();
        return 1;
    }

    /*コマンドラインの解析処理*/
    opterr = 0;
    while ((c = getopt(argc, argv, "hp:")) != -1)
    {
        switch (c)
        {
            case 'h':
                error_message();
                return EXIT_FAILURE; //プログラム異常のため強制終了
            case 'p':
                is_p = true;
                break;
            case '?':
                fprintf(stderr, "用意していないコマンドラインオプションを指定しています: -%c\n", optopt);
            case ':':
                fprintf(stderr, "コマンドライン引数がありません", optopt);
            default:
            break;
        }
    }

    for (int i = optind; i < argc; i++)
    {
        if (input_file == NULL) input_file = fopen(argv[i], "r");
        else if (output_file == NULL) output_file = fopen(argv[i], "w");
    }

    if (input_file == NULL || output_file == NULL)
    {
        error_message();
        return EXIT_FAILURE; //プログラム異常のため強制終了
    }

    // 入力ファイルの処理
    while (fgets(buffer, sizeof(buffer), input_file))
    {
        /*通常課題1通りの処理*/
        if (is_p)
        {
            fputs(buffer, output_file);
        }
        else //通常課題2通りの処理
        {
            char *ptr = buffer;
            char tmp[MAX_LEN];
            int tmp_index = 0;

            while (*ptr != '\0')
            {
                if (isspace(*ptr))
                {
                    if (tmp_index > 0)
                    {
                        tmp[tmp_index] = '\0';
                        fprintf(output_file, "%s\n", tmp);
                        tmp_index = 0;
                    }
                }
                else
                {
                    tmp[tmp_index++] = *ptr;
                }
                ptr++;
            }

            if (tmp_index > 0)
            {
                tmp[tmp_index] = '\0';
                fprintf(output_file, "%s\n", tmp);
            }
        }
    }

    // ファイルを閉じる
    fclose(input_file);
    fclose(output_file);

    return 0;
}
