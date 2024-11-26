/**
 * クラス：A
 * 学籍番号：231205044
 * 氏名：岡田采留
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
    unsigned int v = 0;
    while (*s != '\0') {
        v = v * HASH_RADIX + *s;
        s++;
    }
    return v;
}

/* ハッシュ表を一つ生成し，そのポインタを返す */
HashTablePtr create_hashtable()
{
    HashTablePtr t = malloc(sizeof(HashTable));
    t->serial_id = 0;
    t->size = HASH_SIZE;
    t->heads = malloc(sizeof(HashNodePtr) * t->size);

    /* 各連結リストの先頭要素へのポインタは必ず NULL に初期化する */
    for (int i = 0; i < t->size; i++) {
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
    for (int i = 0; i < t->size; i++) {
        n = t->heads[i];
        while (n != NULL) {
            m = n;
            n = n->next;
            free(m);
        }
    }
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
    int index = hash(key) % t->size;
    HashNodePtr n = t->heads[index];
    while (n != NULL) {
        if (strcmp(key, n->key) == 0) {
            return n->val;
        }
        n = n->next;
    }
    return -1; // キーに対応するデータ値が見つからない場合
}

/* キー key とデータ値 val のペアをハッシュ表 t に登録し，その通し番号を返す */
int enter(HashTablePtr t, char *key, int val)
{
    int index = hash(key) % t->size;
    HashNodePtr n = t->heads[index];
    while (n != NULL) 
    {
        if (strcmp(key, n->key) == 0) 
        {
            n->val = val; // キーが既に存在する場合は値を更新
            return n->id;
        }
        n = n->next;
    }

    HashNodePtr m = malloc(sizeof(HashNode));
    m->key = strdup(key);
    m->id = t->serial_id;
    m->val = val;

    m->next = t->heads[index];
    t->heads[index] = m;
    t->serial_id++;

    return m->id; // 登録したキーとデータ値のペアに付与された通し番号を返す
}

/*
* ハッシュ表 t に登録されるキーの配列を返す
*（この配列のサイズは get_cardinality() で取得可能）
*/
char **get_keys(HashTablePtr t)
{
    char **keys = malloc(sizeof(char *) * t->serial_id);
    HashNodePtr n = NULL;
    for (int i = 0; i < t->size; i++) {
        n = t->heads[i];
        while (n != NULL) {
            keys[n->id] = n->key;
            n = n->next;
        }
    }
    return keys;
}

void print_hashtable(HashTablePtr t)
{
    HashNodePtr current = NULL;
    for (int i = 0; i < t->size; i++) 
    {
        current = t->heads[i];
        while (current != NULL) 
        {
            printf("%s => %d\n", current->key, current->val);
            current = current->next;
        }
    }
}

/* ハッシュ表の使用例 */
int main(void)
{
    HashTablePtr t = create_hashtable();

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
