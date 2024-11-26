/**
 * クラス：A
 * 学籍番号：231205044
 * 氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 1024 //bufferのサイズ

// エラーメッセージ出力関数
void error_message(const char *message)
{
    fprintf(stderr, "%s\n", message);
}

int main(int argc, char *argv[])
{
    // コマンドライン引数が想定外の場合
    if (argc != 3)
    {
        error_message("usage: 231205044_6-2 <input file> <output file>");
        return EXIT_FAILURE; //プログラム異常のため強制終了
    }
    /*input file, output fileのファイルポインタとinput fileを格納するbufferを宣言*/
    FILE *input_file;
    FILE *output_file;
    char buffer[MAX_LEN];

    /*inputfileを開く*/
    input_file = fopen(argv[1], "r");
    if (input_file == NULL) //ファイルを開けなかった場合
    {
        error_message("入力ファイルを開けませんでした。");
        return 1; //プログラム異常のため強制終了
    }
    /*outputfileを開く*/
    output_file = fopen(argv[2], "w");
    if (output_file == NULL) //ファイルが開けなかった場合
    {
        error_message("出力ファイルを開けませんでした。");
        fclose(input_file);
        return EXIT_FAILURE; //プログラム異常のため強制終了
    }

    // ファイル内容を空白またはタブで分割して出力する処理
    while (fgets(buffer, sizeof(buffer), input_file))
    {
        char *ptr = buffer; // バッファ探索する文字型
        char tmp[MAX_LEN]; // 改行で分割した文字列を保持
        int tmp_index = 0;

        while (*ptr != '\0')
        {
            if (isspace(*ptr)) // 空白またはタブを検出
            {
                if (tmp_index > 0) // 改行のみの行をスキップ
                {
                    tmp[tmp_index] = '\0'; // 現在の文字列を終了
                    fprintf(output_file, "%s\n", tmp); // 出力
                    tmp_index = 0; // 初期化
                }
            }
            else //空白またはタブがない場合
            {
                tmp[tmp_index] = *ptr; //部分文字列に文字を追加
                tmp_index++; //次の文字の格納場所に移行
            }
            ptr++; //次の文字の解析に移行
        }

        /*最後まで空白またはタブがなかった場合，そのままの文字列を格納*/
        if (tmp_index > 0)
        {
            tmp[tmp_index] = '\0';
            fprintf(output_file, "%s\n", tmp);
        }
    }

    // ファイルを閉じる
    fclose(input_file);
    fclose(output_file);

    return 0;
}
