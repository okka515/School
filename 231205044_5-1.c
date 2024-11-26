/*
 *クラス:A
 *学籍番号：231205044
 *氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 課題1の場合は以下の0を1に，課題2の場合は2に変更する */
#define KADAI_NUMBER 1
/* 応用課題1の場合は以下のコメントを外す */
/*#define PRINT_REVERSE*/

/* 連結リスト中のノードの構造体 */
struct node {
    int val; /* 値 */
    struct node *next; /* 次ノード */
};

/* セルとそのポインタの型 */
typedef struct node Node;
typedef Node *NodePtr;

/* セルを一つ生成 */
NodePtr create_node(int v)
{
    NodePtr n = NULL;

    n = malloc(sizeof(Node));
    n->val = v;
    n->next = NULL;

    return n;
}

/* セルを表示 */
void print_node(NodePtr n)
{
    if (n != NULL) {
        printf("<%d>", n->val);
    }
    else {
        printf("(null)");
    }
}

/* 連結リストの構造体 */
struct list {
    /* 先頭セルへのポインタ */
    NodePtr head;
};

/* 連結リストとそのポインタの型 */
typedef struct list List;
typedef List *ListPtr;

/* 空の連結リストを生成 */
ListPtr create_list(void)
{
    ListPtr l = NULL;
    l = malloc(sizeof(List));
    l->head = NULL;
    return l;
}

/* 連結リスト l が空かどうか判定 */
int is_empty(ListPtr l)
{
    return (l->head == NULL);
}

/* リスト l の内容を逆順で表示（応用課題1）*/
void print_list_in_reverse(ListPtr l)
{
}

/* リスト l の内容を表示 */
void print_list(ListPtr l)
{
    NodePtr n = NULL;

    if (is_empty(l)) {
        printf("(empty)\n");
        return;
    }

    n = l->head;
    while (n != NULL) {
        print_node(n);
        n = n->next;
    }
    printf("\n");
}

/* リスト l の先頭にセルを挿入 */
void add_first(ListPtr l, int val)
{
    NodePtr n = NULL;
    n = create_node(val);
    n->next = l->head;
    l->head = n;
}

/* リスト l の先頭セルを削除 */
int delete_first(ListPtr l)
{
    NodePtr n = NULL;
    int v;

    /* リストが空なら -1 を返す（負の値はリストに含まれないと仮定）*/
    if (is_empty(l)) return -1;

    v = l->head->val;
    n = l->head;
    l->head = l->head->next;
    free(n);
    n = NULL;

    return v;
}

/* 連結リスト l のサイズを取得 */
int get_list_size(ListPtr l)
{
    NodePtr n = NULL;
    int size;

    size = 0;
    n = l->head;
    while (n != NULL) {
        size++;
        n = n->next;
    }
    return size;
}

/*
 * 連結リスト l における index 番目のセルの値を取得
 * （そのようなセルが存在しなければ -1 を返す）
 */
int get_value(ListPtr l, int index)
{
    NodePtr n = NULL;
    if (index < 0) return -1;

    n = l->head;
    while (index > 0 && n != NULL) {
        n = n->next;
        index--;
    }

    return (n == NULL) ? -1 : n->val;
}

/* リスト l 中の全セルを削除（ループ版）*/
void delete_all(ListPtr l)
{
    NodePtr n = NULL, m = NULL;

    n = l->head;
    while (n != NULL) {
        m = n;
        n = n->next;
        free(m);
    }

    l->head = NULL;
}

/* セル n 以降を全て削除（内部処理用の再帰関数）*/
void delete_rest(NodePtr n)
{
    if (n->next != NULL) delete_rest(n->next);
    free(n);
}

/* リスト l 中の全セルを削除（再帰版）*/
void delete_all_recursively(ListPtr l)
{
    if (l->head == NULL) return;
    delete_rest(l->head);
    l->head = NULL;
}

/* リスト l 全体を削除 */
#define delete_list(l) (delete_list0(l),l=NULL)
void delete_list0(ListPtr l)
{
    delete_all(l);
    free(l);
}

/* リスト l において値 val を持つセルの位置を返す */
int get_index(ListPtr l, int val)
{
    NodePtr n = l->head;
    int index = 0;

    while (n != NULL) //nがnullの場合，終了
    {
        if (n->val == val) {
            return index;
        }
        n = n->next;
        index++;
    }

    return -1; // 値 val を持つセルが存在しない場合
}

/* リスト l の位置 index に値 val を持つセルを挿入 */
void add(ListPtr l, int index, int val)
{
    /* 課題2:ここに正しい実行内容を書く! */
}

/* 連結リストの使用例 */
void main0(void)
{
    ListPtr l = NULL;

    l = create_list();

    add_first(l, 28);
    add_first(l, 40);
    add_first(l, 33);
    add_first(l, 15);

#ifdef PRINT_REVERSE
    print_list_in_reverse(l);
#else
    print_list(l);
#endif

    delete_first(l);
    print_list(l);
    delete_first(l);
    print_list(l);
    delete_first(l);
    print_list(l);
    delete_first(l);
    print_list(l);
}

#if KADAI_NUMBER == 1
void main1(void)
{
    ListPtr l = NULL;
    int a[] = {72, 28, 40, 33, 15};
    int n = sizeof(a)/sizeof(a[0]);
    int i;

    l = create_list();

    /* あえて先頭要素はリストに追加しない */
    for (i = 1; i < n; i++)
        add_first(l, a[i]);

#ifdef PRINT_REVERSE
    print_list_in_reverse(l);
#else
    print_list(l);
#endif

    for (i = 0; i < n; i++)
        printf("Index of %d = %d\n", a[i], get_index(l, a[i]));

    delete_all(l);
}
#endif

#if KADAI_NUMBER == 2
void main2(void)
{
    ListPtr l = NULL;
    int i;

    l = create_list();

    add_first(l, 28);
    add_first(l, 40);
    add_first(l, 33);
    add_first(l, 15);

    print_list(l);

    add(l, 2, 92);
    print_list(l);
    add(l, 0, 87);
    print_list(l);
    add(l, 6, 5);
    print_list(l);
    add(l, 9, 36);

#ifdef PRINT_REVERSE
    print_list_in_reverse(l);
#else
    print_list(l);
#endif

    for (i = 0; i < 8; i++) {
        delete_first(l);
        print_list(l);
    }
}
#endif

int main(void)
{
#if KADAI_NUMBER == 1
    main1();
#elif KADAI_NUMBER == 2
    main2();
#else
    main0();
#endif
    
    return 0;
}
