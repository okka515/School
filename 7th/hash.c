/*
* hash.c: ハッシュ表の型とその操作用関数の定義
* （ハッシュ表のキー：文字列，値：非負の整数）
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

#if defined(__APPLE__) || defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__CYGWIN64__)
#define _strdup strdup
#endif

#define HASH_SIZE 997 /* ハッシュ表の内部配列のサイズ */
#define HASH_RADIX 97 /* ハッシュ関数用の基数 */

/* ハッシュ表内の連結リストに含まれるノードとそのポインタの型． */
typedef struct hash_node HashNode;
typedef HashNode *HashNodePtr;

/* ハッシュ表内の連結リストに含まれるノードの構造体． */
struct hash_node { /* ハッシュ表内の連結リストのノード */
    char *key; /* キー */
    int value; /* キーに対応する値 */
    int id;    /* キーに付与された通し番号 */
    struct hash_node *next; /* 次のノードへのポインタ */
};

/* ハッシュ表の構造体． */
struct hashtable {
    HashNodePtr *heads; /* 内部配列 */
    int serial_id; /* 通し番号管理用の変数 */
    int size; /* 内部配列のサイズ */
};

/* static 関数のプロトタイプ宣言 */
static unsigned int hash(char *s);
static int get_index(HashTablePtr t, char *key);

/* 文字列 s のハッシュ値を計算する． */
static unsigned int hash(char *s)
{
    unsigned int v;

    v = 0;
    while (*s != '\0') {
        v = v * HASH_RADIX + *s;
        s++;
    }

    return v;
}

/* ハッシュ表を一つ生成し，そのポインタを返す．*/
HashTablePtr create_hashtable(void)
{
    HashTablePtr t = NULL;
    int i;

    t = malloc(sizeof(HashTable));
    if (t == NULL) {
        fprintf(stderr, "Couldn't allocate memory for a hashtable\n");
        exit(EXIT_FAILURE);
    }

    t->serial_id = 0;
    t->size = HASH_SIZE;
    t->heads = malloc(sizeof(HashNodePtr) * t->size);
    if (t->heads == NULL) {
        fprintf(stderr, "Couldn't allocate memory for a hashtable's header array\n");
        exit(EXIT_FAILURE);
    }

    /* 各連結リストの先頭要素へのポインタは必ず NULL に初期化する */
    for (i = 0; i < t->size; i++) {
        t->heads[i] = NULL;
    }

    return t;
}

/* ハッシュ表の実質的な解放作業を行う．
* （次々と free() するので free() 後の NULL 代入は省略）
*/
void delete_hashtable0(HashTablePtr t)
{
    HashNodePtr n = NULL, m = NULL;
    int i;

    /* free() と同様，NULLポインタに対しては何も行わない */
    if (t == NULL) {
        return;
    }

    /* 各連結リストの領域を解放 */
    for (i = 0; i < t->size; i++) {
        n = t->heads[i];
        while (n != NULL) {
            m = n;
            n = n->next;
            free(m);
        }
    }

    /* 最後に連結リストの先頭ポインタの領域を解放 */
    free(t->heads);
    free(t);
}

/* ハッシュ表 t に登録されているキーと値のペアの数を返す．*/
int get_cardinality(HashTablePtr t)
{
    assert(t);
    return t->serial_id;
}

/* ハッシュ表 t の内部配列の添え字を返す */
static int get_index(HashTablePtr t, char *key)
{
    return hash(key) % t->size;
}

/* ハッシュ表 t にてキー key が登録されていれば1,
* されていなければ0を返す．
*/
int has_key(HashTablePtr t, char *key)
{
    assert(t && key);
    return (lookup(t, key) >= 0) ? 1 : 0;
}

/* ハッシュ表 t にてキー key に対応する値を返す．
* 値が見つからなかったら -1 を返す．
* （ハッシュ表の値として登録できるのは非負の整数値と仮定）
*/
int lookup(HashTablePtr t, char *key)
{
    HashNodePtr n = NULL;
    int index;

    assert(t && key);

    /* ハッシュ表の内部配列の添え字を計算 */
    index = get_index(t, key);

    /* index 番目の連結リストを先頭から順に走査 */
    n = t->heads[index];
    while (n != NULL) {
        /* 引数で指定された key とハッシュ表内のキーが一致したら
        直ちに対応する値を返す */
        if (strcmp(key, n->key) == 0) {
            return n->value;
        }

        /* 走査を次に進める */
        n = n->next;
    }

    /* キーが見つからなかったので -1 を返す */
    return -1;
}

/* キー key と値 value のペアをハッシュ表 t に登録し，その通し番号を返す．
* （値 value は非負であると仮定）
*/
int enter(HashTablePtr t, char *key, int value)
{
    HashNodePtr n = NULL, m = NULL;
    int index;

    assert(t && key);

    /* 仕様上のエラーなので非負の値が渡されたときはメッセージを出す */
    if (value < 0) {
        fprintf(stderr, "Invalid value %d for key %s\n", value, key);
        exit(EXIT_FAILURE);
    }

    /* 内部配列の添え字を計算 */
    index = get_index(t, key);

    /* キー key が既に登録されているか探し，
    * 登録されている場合は値を value に更新する．
    */
    n = t->heads[index]; /* index 番目の head を出発点とする */
    while (n != NULL) {
        if (strcmp(key, n->key) == 0) { /* 登録されていた */
            n->value = value; /* 値を更新 */
            return n->id;
        }
        n = n->next;
    }

    /* 新しいノードを生成 */
    m = malloc(sizeof(HashNode));
    if (m == NULL) {
        fprintf(stderr, "Couldn't allocate memory for a hash node\n");
        exit(EXIT_FAILURE);
    }

    m->key = _strdup(key);
    m->id = t->serial_id;
    m->value = value;

    /* 新しいノードを先頭に挿入 */
    m->next = t->heads[index];
    t->heads[index] = m;

    t->serial_id++; /* 次の通し番号に更新 */

    return m->id; /* 登録したキーと値のペアに付与された通し番号を返す */
}

/*
* ハッシュ表 t に登録されるキーの配列を返す．
*（この配列のサイズは get_hash_cardinality() で取得可能）
*/
char **get_keys(HashTablePtr t)
{
    char **keys = NULL;
    HashNodePtr n;
    int i;

    assert(t);

    keys = malloc(sizeof(char *) * t->serial_id);
    if (keys == NULL) {
        fprintf(stderr, "Couldn't allocate memory for hashtable keys\n");
        exit(EXIT_FAILURE);
    }

    /* 各連結リストを走査し，配列に詰め込む */
    for (i = 0; i < t->size; i++) {
        n = t->heads[i];
        while (n != NULL) {
            keys[n->id] = n->key; /* 通し番号を配列添え字に */
            n = n->next;
        }
    }

    return keys; /* 後で free() する必要あり */
}

/* ハッシュ表の内容を表示する．*/
void print_hashtable(HashTablePtr t)
{
    HashNodePtr n = NULL;
    int i;

    assert(t);

    for (i = 0; i < t->size; i++) {
        n = t->heads[i];
        while (n != NULL) {
            printf("%s => %d\n", n->key, n->value);
            n = n->next;
        }
    }
}
