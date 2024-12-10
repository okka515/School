/**
 * クラス：A
 * 学籍番号：231205044
 * 氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LEN 1024

// エラーメッセージ出力関数
void error_message()
{
    fprintf(stderr, "usage: 231205044_6-3 [options...] <input file> <output file>\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "   -p   : enable pass-through mode\n");
    fprintf(stderr, "   -h   : display this message\n");
}

char big_to_small(char a)
{
    if (a >= 'A' && a <= 'Z')
    {
        return a + 'a' - 'A';
    }
    return a;
}

bool contain_alpha(char *a)
{
    while (*a != '\0')
    {
        if (isalpha(*a))
        {
            return true;
        }
        a++;
    }
    return false;
}

int main(int argc, char *argv[])
{
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    char buffer[MAX_LEN];
    bool is_p = false; // pコマンドオプションをブール管理

    // コマンドライン引数の解析
    if (argc < 3)
    {
        error_message();
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-') // オプションかどうかの判定
        {
            switch (argv[i][1]) //オプションの内容で分岐
            {
            case 'h': // 使用方法の表示
                error_message();
                return 0;
            case 'p': // パススルーモード
                is_p = true; //pが真
                break;
            default: //用意していないコマンドラインオプションの場合
                fprintf(stderr, "Unknown option: %s\n", argv[i]);
                error_message();
                return EXIT_FAILURE; //プログラム異常のため強制終了
            }
        }
        else //コマンドラインオプションでない場合
        {
            if (input_file == NULL)
            {
                input_file = fopen(argv[i], "r");
                if (input_file == NULL)
                {
                    fprintf(stderr, "ファイルが開けませんでした: %s\n", argv[i]);
                    return EXIT_FAILURE; //プログラム異常のため強制終了
                }
            }
            else if (output_file == NULL)
            {
                output_file = fopen(argv[i], "w");
                if (output_file == NULL)
                {
                    fprintf(stderr, "ファイルが開けませんでした: %s\n", argv[i]);
                    fclose(input_file);
                    return EXIT_FAILURE; //プログラム異常のため強制終了
                }
            }
            else
            {
                error_message();
                return EXIT_FAILURE; //プログラム異常のため強制終了
            }
        }
    }
    
    //入力ファイルの処理
    while (fgets(buffer, sizeof(buffer), input_file))
    {
        /*pコマンドオプションが真のため通常課題1通りの処理*/
        if (is_p)
        {
            fputs(buffer, output_file);
        }
        else //pコマンドが偽のため通常課題2通りの処理
        {
            if (contain_alpha(buffer))
            {
                char *ptr = buffer;
                char tmp[MAX_LEN];
                int tmp_index = 0;

                while (*ptr != '\0')
                {
                    if (isspace(*ptr)) //タブまたは空白の検出
                    {
                        if (tmp_index > 0) //改行のみの行をスキップ
                        {
                            tmp[tmp_index] = '\0';
                            fprintf(output_file, "%s\n", tmp);
                            tmp_index = 0;
                        }
                    }
                    else
                    {
                        char big_small_tmp = big_to_small(*ptr);
                        tmp[tmp_index++] = big_small_tmp;
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
    }

    // ファイルを閉じる
    fclose(input_file);
    fclose(output_file);

    return 0;
}
