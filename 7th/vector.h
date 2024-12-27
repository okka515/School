/*
* vector.h: 文字列の可変長配列の型とその操作用関数のヘッダファイル
*/
#ifndef VECTOR_H
#define VECTOR_H

/* 可変長配列とそのポインタの型 */
typedef struct vector Vector;
typedef Vector *VectorPtr;

/* 可変長配列を生成する */
VectorPtr create_vector(void);

/* 可変長配列 v を解放する */
#define delete_vector(v) (delete_vector0(v),v=NULL)
void delete_vector0(VectorPtr v);

/* 可変長配列 v を初期化する（未使用状態にするだけで領域は解放しない）．*/
void clear_vector(VectorPtr v);

/* 可変長配列 v の最後に文字列 s を追加 */
void append(VectorPtr v, char *s);

/* 可変長配列の（使用部分の）サイズを返す．*/
int get_vector_size(VectorPtr v);

/* 可変長配列 v における添え字 index の要素（文字列）を取得 */
char *get_elem(VectorPtr v, int index);

/* 可変長配列の内容を横に並べて表示する．*/
void print_vector(VectorPtr v);

#endif
