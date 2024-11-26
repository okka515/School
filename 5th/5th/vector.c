/**
 * クラス：A
 * 学籍番号：231205044
 * 氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>

/* 可変長配列の初期サイズ */
#define INIT_SIZE 5

/* 可変長型配列の構造体 */
struct vector {
    int *elems;   /* 要素の配列（固定長）*/
    int size;     /* 可変長配列のサイズ */
    int capacity; /* 可変長配列の最大容量 */
};

typedef struct vector Vector;
typedef Vector *VectorPtr;

/* 可変長配列を生成する */
VectorPtr create_vector()
{
    VectorPtr v = NULL;

    v = malloc(sizeof(Vector));

    v->elems = malloc(sizeof(int) * INIT_SIZE);
    v->size = 0;  /* 初期使用サイズは 0 */
    v->capacity = INIT_SIZE;

    return v;
}

/* 可変長配列 v を解放する（マクロで定義しておく） */
#define delete_vector(v) (delete_vector0(v),v=NULL)
void delete_vector0(VectorPtr v)
{
    free(v->elems);
    free(v);
}

/* 可変長配列 v を拡大する */
void expand_vector(VectorPtr v)
{
    /* 最大容量を2倍に増やす */
    v->capacity *= 2;

    /* 新しい最大容量を持つ領域を確保 */
    v->elems = realloc(v->elems, sizeof(int) * v->capacity);

    /* サイズを変更できなかった場合のエラー処理 */
    if (v->elems == NULL) {
        fprintf(stderr, "Couldn't allocate memory\n");
        exit(EXIT_FAILURE);
    }
}

/* 可変長配列 v の最後に整数要素 e を追加 */
void append(VectorPtr v, int e)
{
    /* 容量が一杯になったら容量を拡大する */
    if (v->size == v->capacity) {
        expand_vector(v);
    }
    v->elems[v->size] = e; /* 最後に要素を追加 */
    v->size++; /* 使用部分のサイズを1つ増やす */
}

/* 可変長配列 v における添え字 index の要素を取得 */
int get_elem(VectorPtr v, int index)
{
    /* 配列添え字の範囲をチェック */
    if (index < 0 || index >= v->size) {
        fprintf(stderr, "Index out of bounds");
        exit(EXIT_FAILURE);
    }
    /* 指定された添え字の値を返す */
    return v->elems[index];
}

/*バブルソートアルゴリズムの使用*/
void sort(VectorPtr v)
{
    int i, j, temp;
    for (i = 0; i < v->size - 1; i++)
    {
        for (j = 0; j < v->size - 1 - i; j++)
        {
            if (v->elems[j] > v->elems[j + 1])
            {
                /*交換*/
                temp = v->elems[j];
                v->elems[j] = v->elems[j + 1];
                v->elems[j + 1] = temp;
            }
        }
    }
}


/* 可変長配列の使用例 */
int main(void)
{
    VectorPtr v = NULL;
    int i, r;

    /* 可変長配列を生成 */
    v = create_vector();

    /* ランダムに整数を生成し，可変長配列に追加 */
    srand((unsigned int)time(NULL));
    for (i = 0; i < 10; i++) {
        r = rand() % 1000;
        append(v, r);
        printf("Added: %d\n", r);
    }

    /* 可変長配列のサイズと最大容量を表示 */
    printf("\n");
    printf("Size = %d\n", v->size);
    printf("Capacity = %d\n", v->capacity);
    printf("\n");

    /* 可変長配列の内容を表示 */
    printf("Contents:\n");
    for (i = 0; i < v->size; i++) {
        printf("  %d\n", get_elem(v, i));
    }

    /*可変長配列の内容を昇順に整列*/
    sort(v);

    /*整列後の可変長配列の内容を表示*/
    printf("Contents:\n");
    for (i = 0; i < v->size; i++)
    {
        printf("  %d\n", get_elem(v, i));
    }

    /* 可変長配列を削除 */
    delete_vector(v);

    return 0;
}
