/*
* hash.h: ハッシュ表の型とその操作用関数のヘッダファイル
* （ハッシュ表のキー：文字列，値：非負の整数）
*/
#ifndef HASH_H
#define HASH_H

/* ハッシュ表とそのポインタの型 */
typedef struct hashtable HashTable;
typedef HashTable *HashTablePtr;

/* ハッシュ表を一つ生成し，そのポインタを返す．*/
HashTablePtr create_hashtable(void);

/* ハッシュ表の削除を行う．*/
#define delete_hashtable(t) (delete_hashtable0(t),t=NULL)
void delete_hashtable0(HashTablePtr t);

/* ハッシュ表 t に登録されているキーと値のペアの数を返す．*/
int get_cardinality(HashTablePtr t);

/* ハッシュ表 t にてキー key が登録されていれば1, されていなければ0を返す．*/
int has_key(HashTablePtr t, char *key);

/* ハッシュ表 t にてキー key に対応する値を返す．
 * （値が見つからなかったら -1 を返す）
 */
int lookup(HashTablePtr t, char *key);

/* キー key と正の整数値 value のペアをハッシュ表 t に登録し，その通し番号を返す．*/
int enter(HashTablePtr t, char *key, int value);

/* ハッシュ表 t に登録されるキーの配列を返す．
 * 返ってきた配列は後で free() する必要がある．
 */
char **get_keys(HashTablePtr t);

/* ハッシュ表の内容を表示する．*/
void print_hashtable(HashTablePtr t);

#endif
