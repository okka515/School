/*
 * ファイルを読み込みもう一つのファイルに書き込むプログラム
 * クラス：A
 * 学籍番号：231205033
 * 氏名：宇野伊優
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void usage() {
    fprintf(stderr, "usage: 231205033_7-1 [options] <input file> <output file>\n");
    fprintf(stderr,"options:\n");
    fprintf(stderr, "  -p     : enable pass-through mode\n");
    fprintf(stderr, "  -h     : display this message\n");
}

//文字を小文字に変換する関数
int my_tolower(int c) {
    if (c < 'A' || c > 'Z') return c;
    return 'a' + (c - 'A');
}

//文字列を小文字に変換する関数
void tolostr(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] =my_tolower(str[i]); 
    }
}

//アルファベットを含むかどうか判定する関数
int alphabet(const char *str) {
    for (int i = 0; str[i] !='\0'; i++) {
        if (isalpha(str[i])) {
            return 1;//アルファベットがある
        }
    }
    return 0;//アルファベットがない
}

int main(int argc, char *argv[]) {
    char *in_name = NULL;
    char *out_name = NULL;
    int mode = 0;


    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {//オプションの場合分け
            switch (argv[i][1]) {
                case 'p':  
                    mode = 1;
                    break;
                case 'h':
                    usage();
                    return EXIT_SUCCESS;
            }
        } else {
            if (in_name == NULL) {
                in_name = argv[i];//入力ファイル
            } else if (out_name == NULL) {
                out_name = argv[i];//出力ファイル
            } else {
                fprintf(stderr, "Error\n");
                usage();
                return EXIT_FAILURE;
            }
        }
    }



    if (in_name == NULL || out_name == NULL) {
        usage();
        return EXIT_FAILURE;
    }

    FILE *fp =fopen(in_name, "r");
    if (fp ==NULL) {
        perror("Error");
        return EXIT_FAILURE;
    }

    FILE *fo = fopen(out_name, "w");
    if (fo ==NULL) {
        perror("Error");
        fclose(fp);
        return EXIT_FAILURE;
    }


    if (mode) {//オプションｐ
        char buf[1024];
        while (fgets(buf, sizeof(buf), fp) !=NULL) {
            fputs(buf, fo);
        }
    } else {//オプションなし
        char buf[1024];
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            if (strlen(buf) > 1) { // 改行だけの行をスキップ
                char *line = buf;
                while (1) {
                    char *word = strtok(line, " \t\n");
                    if (word == NULL) { 
                        break; // トークンがなくなったら終了
                    }
                    if (alphabet(word)) { // アルファベットを含むか確認
                        tolostr(word);    // 小文字に変換
                        fputs(word, fo);  // 出力
                        fputc('\n', fo);  // 単語ごとに改行
                    }
                    line = NULL; // 次のトークンを処理するためにNULLをセット
                }
            }
        }
    }
    fclose(fp);
    fclose(fo);

    printf("Completed successfully.\n");
    return EXIT_SUCCESS;
}
