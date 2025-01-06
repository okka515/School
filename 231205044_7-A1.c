/**
 * クラス：A
 * 学籍番号：231205044
 * 氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "./7th/hash.c"

#define MAX_LEN 1024

// エラーメッセージ出力関数
void error_message()
{
    fprintf(stderr, "usage: 231205044_7-3 [options...] <input file> <output file>\n");
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

/* 最初と最後の記号を取り除き，所有格も取り除く関数*/
void remove_symbol_start_and_end_and_prossessive(char *a)
{
    char *start = a; // 文字列の先頭ポインタを所持
    char *end = a + strlen(a) - 1; // 文字列の末尾ポインタの所持

    // 先頭の記号を削除
    while (*start && !isalpha(*start)) 
    {
        start++;
    }

    // 末尾の記号を削除
    while (end > start && !isalpha(*end)) 
    {
        *end-- = '\0';
    }

    // 所有格を削除
    if (end > start && end[-1] == '\'' && end[0] == 's') 
    {
        end[-1] = '\0';
    }

    // 開始位置を調整した文字列を元の配列にコピー
    if (*start == '\0') 
    {
        a[0] = '\0'; // 完全に削除された場合
    } 
    else 
    {
        memmove(a, start, strlen(start) + 1);
    }
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

// 単語の回数をハッシュで記録して，出力する関数
HashTablePtr count_words(FILE *in, FILE *out, int mode)
{
    int c, value;
    char buf[MAX_LEN];
    HashTablePtr t = NULL;

    if (mode != 0) t = create_hashtable();

    while (fgets(buf, sizeof(buf), in) != NULL)
    {
        if (mode == 0) fputs(buf, out);
        else
        {
            char *ptr = buf;
            char word[MAX_LEN];
            int tmp_index = 0;

            while (*ptr != '\0')
            {
                if (isspace(*ptr)) //タブまたは空白の検出
                {
                    if (tmp_index > 0) //単語が存在する場合
                    {
                        word[tmp_index] = '\0'; //文字列を終了
                        remove_symbol_start_and_end_and_prossessive(word);
                        if (contain_alpha(word))
                        {
                            for (int i = 0; i < tmp_index; i++)
                            {
                                word[i] = big_to_small(word[i]);
                            }

                            /* ハッシュのkeyから単語を走査し，値を得る*/
                            c = lookup(t, word);
                            value = (c < 0) ? 1 : c + 1; // lookup関数の返り値は，keyが見つからなった場合-1なのでc < 0で比較
                            enter(t, word, value);
                        }
                        tmp_index = 0; // 次の単語のためのリセット処理
                    }
                }
                else //タブまたは空白の検出がない場合，次の文字に進む
                {
                    word[tmp_index++] = *ptr;
                }
                ptr++;
            }
        }
    } 
    return t;
}

int main(int argc, char *argv[])
{
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    char buffer[MAX_LEN];
    int is_p = 2; // pコマンドオプション
    int n_words;
    char **keys;

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
                is_p = 0;
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
    HashTablePtr t = count_words(input_file, output_file, is_p);
    if (t != NULL && is_p >= 2 )
    {
        n_words = get_cardinality(t);
        keys = get_keys(t);
        for (int i = 0; i < n_words; i++)
        {
            fprintf(output_file, "%s: %d\n", keys[i], lookup(t, keys[i]));
        }
        free(keys);
    }
    delete_hashtable(t); // ハッシュテーブルのメモリ解放
    // ファイルを閉じる
    fclose(input_file);
    fclose(output_file);

    return 0;
}
