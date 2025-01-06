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

/* アルファベットを大文字から小文字にするメソッド */
char big_to_small(char a)
{
    if (a >= 'A' && a <= 'Z')
    {
        return a + 'a' - 'A';
    }
    return a;
}

/* アルファベットを含んでいるかの判定メソッド */
bool contain_alpha(char *a)
{
    char *p = a;
    while (*p != '\0')
    {
        if (isalpha(*p))
        {
            return true;
        }
        p++;
    }
    return false;
}

int main(int argc, char *argv[])
{
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    char buffer[MAX_LEN];
    bool is_p = false; // pコマンドオプションをブール管理

    // コマンドライン引数の文字数解析
    if (argc < 3)
    {
        error_message();
        return 1;
    }

    // コマンドラインの解析
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
                is_p = true;
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
        char *ptr = buffer;
        char tmp[MAX_LEN];
        int tmp_index = 0;

        while (*ptr != '\0')
        {
            if (isspace(*ptr)) // タブまたは空白の検出
            {
                if (tmp_index > 0) // 単語が存在する場合
                {
                    tmp[tmp_index] = '\0'; // 文字列を終了
                    if (contain_alpha(tmp)) // アルファベットが含まれる場合のみ出力
                    {
                        for (int i = 0; i < tmp_index; i++)
                        {
                            tmp[i] = big_to_small(tmp[i]); // 小文字に変換
                        }
                        fprintf(output_file, "%s\n", tmp); // 出力
                    }
                    tmp_index = 0; // 次の単語処理のためにリセット
                }
            }
            else // タブまたは空白でない場合
            {
                tmp[tmp_index++] = *ptr;
            }
            ptr++;
        }

        if (tmp_index > 0) // 最後の単語を処理
        {
            tmp[tmp_index] = '\0';
            if (contain_alpha(tmp))
            {
                for (int i = 0; i < tmp_index; i++)
                {
                    tmp[i] = big_to_small(tmp[i]);
                }
                fprintf(output_file, "%s\n", tmp);
            }
        }
    }


    // ファイルを閉じる
    fclose(input_file);
    fclose(output_file);

    return 0;
}