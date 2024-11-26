/**
 * クラス：A
 * 学籍番号：231205044
 * 氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>

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
        error_message("usage: 231205044_6-1 <input file> <output file>"); //コマンドライン引数が値が違う場合，エラーメッセージを送信
        return EXIT_FAILURE; //プログラム異常のため強制終了
    }

    /*input file, output fileのファイルポインタとinput fileを格納するbufferを宣言*/
    FILE *input_file;
    FILE *output_file;
    char buffer[MAX_LEN];

    // ファイルを開く
    input_file = fopen(argv[1], "r");
    output_file = fopen(argv[2], "w");
    /*inputfileが開けなかった場合*/
    if (input_file == NULL)
    {
        error_message("インプットファイルを開けませんでした．");
        return EXIT_FAILURE; //プログラム異常のため終了
    }
    /*outputfileが開けなかった場合*/
    if (output_file == NULL)
    {
        error_message("アウトプットファイルを開けませんでした．");
        return EXIT_FAILURE; //プログラム異常のため終了
    }

    // ファイル内容をコピー
    while (fgets(buffer, sizeof(buffer), input_file))
    {
        fputs(buffer, output_file);
    }

    // ファイルを閉じる
    fclose(input_file);
    fclose(output_file);

    return 0;
}
