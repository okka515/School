/**
 * クラス?��A
 * 学籍番号?�?231205044
 * 氏名?��岡田�?�?
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 1024 //bufferのサイズ

// エラーメ�?セージ出力関数
void error_message(const char *message)
{
    fprintf(stderr, "%s\n", message);
}

int main(int argc, char *argv[])
{
    // コマンドライン引数が想定外�?�場�?
    if (argc != 3)
    {
        error_message("usage: 231205044_6-2 <input file> <output file>");
        return EXIT_FAILURE; //プログラ�?異常のため強制終�?
    }
    /*input file, output fileのファイルポインタとinput fileを�?�納するbufferを宣言*/
    FILE *input_file;
    FILE *output_file;
    char buffer[MAX_LEN];

    /*inputfileを開�?*/
    input_file = fopen(argv[1], "r");
    if (input_file == NULL) //ファイルを開けなかった�?��?
    {
        error_message("入力ファイルを開けませんでした�?");
        return 1; //プログラ�?異常のため強制終�?
    }
    /*outputfileを開�?*/
    output_file = fopen(argv[2], "w");
    if (output_file == NULL) //ファイルが開けなかった�?��?
    {
        error_message("出力ファイルを開けませんでした�?");
        fclose(input_file);
        return EXIT_FAILURE; //プログラ�?異常のため強制終�?
    }

    // ファイル�?容を空白また�?�タブで�?割して出力する�?��?
    while (fgets(buffer, sizeof(buffer), input_file))
    {
        char *ptr = buffer; // バッファ探索する�?字型
        char tmp[MAX_LEN]; // 改行で�?割した�?字�?�を保持
        int tmp_index = 0;

        while (*ptr != '\0')
        {
            if (isspace(*ptr)) // 空白また�?�タブを検�?�
            {
                if (tmp_index > 0) // 改行�?�みの行をスキ�?�?
                {
                    tmp[tmp_index] = '\0'; // 現在の�?字�?�を終�?
                    fprintf(output_file, "%s\n", tmp); // 出�?
                    tmp_index = 0; // 初期�?
                }
            }
            else //空白また�?�タブがな�?場�?
            {
                tmp[tmp_index] = *ptr; //部�?�?字�?�に�?字を追�?
                tmp_index++; //次の�?字�?�格納�?�所に移�?
            }
            ptr++; //次の�?字�?�解析に移�?
        }

        /*最後まで空白また�?�タブがなかった�?�合，そのままの�?字�?�を格�?*/
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
