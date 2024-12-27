/*
 * vector.c: 文字列の可変長配列の型とその操作用関数の定義
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

#if defined(__APPLE__) || defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__CYGWIN64__)
#define _strdup strdup
#endif

/* 可変長配列の初期サイズ */
#define INIT_SIZE 5

/* 可変長型配列の構造体 */
struct vector {
    char **elems; /* 要素（文字列）の配列（固定長）*/
    int size;     /* 可変長配列のサイズ */
    int capacity; /* 可変長配列の最大容量 */
};

/* static 関数のプロトタイプ宣言 */
static void expand_vector(VectorPtr v);

/* 可変長配列を生成する */
VectorPtr create_vector(void)
{
    VectorPtr v = NULL;

    v = malloc(sizeof(Vector));
    if (v == NULL) {
        fprintf(stderr, "Couldn't allocate memory for a vector\n");
        exit(EXIT_FAILURE);
    }

    v->elems = malloc(sizeof(char *) * INIT_SIZE);
    v->size = 0;  /* 初期使用サイズは 0 */
    v->capacity = INIT_SIZE;

    return v;
}

/* 可変長配列の実質的な解放作業を行う．
 * （次々と free() するので free() 後の NULL 代入は省略）
 */
void delete_vector0(VectorPtr v)
{
    int i;

    /* free() と同様，NULLポインタに対しては何も行わない */
    if (v == NULL) {
        return;
    }

    /* 各要素（文字列）の領域を解放 */
    for (i = 0; i < v->size; i++) {
        free(v->elems[i]);
    }
    free(v->elems); /* 内部配列の領域を解放 */
    free(v); /* 外側の枠も解放 */
}

/* 可変長配列 v を初期化する（未使用状態にするだけで領域は解放しない）．*/
void clear_vector(VectorPtr v)
{
    int i;

    assert(v);

    /* 要素の各文字列を解放 */
    for (i = 0; i < v->size; i++) {
        free(v->elems[i]);
        v->elems[i] = NULL;
    }

    /* 使用サイズを0にする */
    v->size = 0;
}

/* 可変長配列 v を拡大する */
static void expand_vector(VectorPtr v)
{
    assert(v);

    /* 最大容量を2倍に増やす */
    v->capacity *= 2;

    /* 新しい最大容量を持つ領域を確保 */
    v->elems = realloc(v->elems, sizeof(char *) * v->capacity);

    /* サイズを変更できなかった場合のエラー処理 */
    if (v->elems == NULL) {
        fprintf(stderr, "Couldn't re-allocate memory for a vector\n");
        exit(EXIT_FAILURE);
    }
}

/* 可変長配列 v の最後に文字列 s を追加 */
void append(VectorPtr v, char *s)
{
    assert(s);

    /* 容量が一杯になったら容量を拡大する */
    if (v->size == v->capacity) {
        expand_vector(v);
    }
    v->elems[v->size] = _strdup(s); /* 最後に要素を追加 */
    v->size++; /* 使用部分のサイズを1つ増やす */
}

/* 可変長配列の（使用部分の）サイズを返す．*/
int get_vector_size(VectorPtr v)
{
    assert(v);
    return v->size;
}

/* 可変長配列 v における添え字 index の要素（文字列）を取得 */
char *get_elem(VectorPtr v, int index)
{
    assert(v);

    /* 配列添え字の範囲をチェック */
    if (index < 0 || index >= v->size) {
        fprintf(stderr, "Index out of bounds");
        exit(EXIT_FAILURE);
    }
    /* 指定された添え字の値を返す */
    return v->elems[index];
}

/* 可変長配列の内容を横に並べて表示する．*/
void print_vector(VectorPtr v)
{
    int i;

    assert(v);

    if (v->size == 0) {
        printf("(empty)\n");
        return;
    }

    for (i = 0; i < v->size; i++) {
        printf(">>%s", v->elems[i]);
    }
    printf("\n");
}
