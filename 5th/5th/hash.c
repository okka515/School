/*
 * hash.c: ハッシュ表の例プログラム
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 997 /* ハッシュ表の内部配列のサイズ */
#define HASH_RADIX 97 /* ハッシュ関数用の基数 */

/* ハッシュ表内の連結リストに含まれるノードの構造体 */
struct hash_node { /* ハッシュ表内の連結リストのノード */
    char *key; /* キー */
    int val;   /* キーに対応するデータ値 */
    int id;    /* キーに付与された通し番号 */
    struct hash_node *next; /* 次のノードへのポインタ */
};

typedef struct hash_node HashNode;
typedef HashNode *HashNodePtr;

/* ハッシュ表の構造体 */
struct hashtable {
    HashNodePtr *heads; /* 内部配列 */
    int serial_id; /* 通し番号管理用の変数 */
    int size; /* 内部配列のサイズ */
};

typedef struct hashtable HashTable;
typedef HashTable *HashTablePtr;

/* 文字列 s のハッシュ値を計算する */
unsigned int hash(char *s)
{
    unsigned int v;

    v = 0;
    while (*s != '\0') {
        v = v * HASH_RADIX + *s;
        s++;
    }

    return v;
}

/* ハッシュ表を一つ生成し，そのポインタを返す */
HashTablePtr create_hashtable()
{
    HashTablePtr t = NULL;
    int i;

    t = malloc(sizeof(HashTable));

    t->serial_id = 0;
    t->size = HASH_SIZE;
    t->heads = malloc(sizeof(HashNodePtr) * t->size);

    /* 各連結リストの先頭要素へのポインタは必ず NULL に初期化する */
    for (i = 0; i < t->size; i++) {
        t->heads[i] = NULL;
    }

    return t;
}

/* 指定したポインタ変数に NULL を代入して終わるためのマクロ */
#define delete_hashtable(t) \
	(delete_hashtable0(t),t=NULL)

/* 実質的な削除作業を行う関数（free 後の NULL 代入は省略）*/
void delete_hashtable0(HashTablePtr t)
{
    HashNodePtr n = NULL, m = NULL;
    int i;

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

/* ハッシュ表 t に登録されているキーとデータ値のペアの数を返す */
int get_cardinality(HashTablePtr t)
{
    return t->serial_id;
}

/* ハッシュ表 t にてキー key に対応するデータ値を調べる */
int lookup(HashTablePtr t, char *key)
{
    HashNodePtr n = NULL;
    int index;

    /* ハッシュ表の内部配列の添え字を計算 */
    index = hash(key) % t->size;

    /* index 番目の連結リストを先頭から順に走査 */
    n = t->heads[index];
    while (n != NULL) {
        /* 引数で指定された key とハッシュ表内のキーが一致したら
           直ちに対応するデータ値を返す */
        if (strcmp(key, n->key) == 0) {
            return n->val;
        }

        /* 走査を次に進める */
        n = n->next;
    }
    /* ここではキーに対応するデータ値は非負であると仮定し，
       見つからなかったら -1 を返す */
    return -1;
}

/* キー key とデータ値 val のペアをハッシュ表 t に登録し，その通し番号を返す */
int enter(HashTablePtr t, char *key, int val)
{
    HashNodePtr n = NULL, m = NULL;
    int index;

    index = hash(key) % t->size; /* 内部配列の添え字を計算 */

    /* キーが既に存在しているかどうかチェック（lookup() と同じ処理）*/
    n = t->heads[index];
    while (n != NULL) {
        if (strcmp(key, n->key) == 0) { /* 登録されていた */
            return n->id; /* 通し番号を返す */
        }
        n = n->next;
    }

    /* 新しいノードを生成 */
    m = malloc(sizeof(HashNode));
    m->key = _strdup(key);
    m->id = t->serial_id;
    m->val = val;

    /* 連結リストの add_first() と同様にして連結リストに追加 */
    m->next = t->heads[index];
    t->heads[index] = m;
    t->serial_id++; /* 次の通し番号に更新 */

    return m->id; /* 登録したキーとデータ値のペアに付与された通し番号を返す */
}

/*
* ハッシュ表 t に登録されるキーの配列を返す
*（この配列のサイズは get_cardinality() で取得可能）
*/
char **get_keys(HashTablePtr t)
{
    char **keys = NULL;
    HashNodePtr n = NULL;
    int i;

    keys = malloc(sizeof(char *) * t->serial_id);

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

void print_hashtable(HashTablePtr t)
{
    /* 課題: ここに実行内容を書く! */
}

/* ハッシュ表の使用例 */
int main(void)
{
    HashTablePtr t = NULL;

    t = create_hashtable();

    enter(t, "Meijo Taro", 25);
    enter(t, "Meijo Jiro", 22);
    enter(t, "Shiogama Saburo", 19);
    enter(t, "Yagoto Shiro", 20);
    enter(t, "Kani Goro", 28);

    printf("**** Before ****\n");
    print_hashtable(t);

    enter(t, "Meijo Taro", 35);
    enter(t, "Kani Goro", 3);

    printf("**** After ****\n");
    print_hashtable(t);

    delete_hashtable(t);

    return 0;
}
