/*
 *�N���X:A
 *�w�Дԍ��F231205044
 *�����F���c�ї�
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* �ۑ�1�̏ꍇ�͈ȉ���0��1�ɁC�ۑ�2�̏ꍇ��2�ɕύX���� */
#define KADAI_NUMBER 1
/* ���p�ۑ�1�̏ꍇ�͈ȉ��̃R�����g���O�� */
/*#define PRINT_REVERSE*/

/* �A�����X�g���̃m�[�h�̍\���� */
struct node {
    int val; /* �l */
    struct node *next; /* ���m�[�h */
};

/* �Z���Ƃ��̃|�C���^�̌^ */
typedef struct node Node;
typedef Node *NodePtr;

/* �Z��������� */
NodePtr create_node(int v)
{
    NodePtr n = NULL;

    n = malloc(sizeof(Node));
    n->val = v;
    n->next = NULL;

    return n;
}

/* �Z����\�� */
void print_node(NodePtr n)
{
    if (n != NULL) {
        printf("<%d>", n->val);
    }
    else {
        printf("(null)");
    }
}

/* �A�����X�g�̍\���� */
struct list {
    /* �擪�Z���ւ̃|�C���^ */
    NodePtr head;
};

/* �A�����X�g�Ƃ��̃|�C���^�̌^ */
typedef struct list List;
typedef List *ListPtr;

/* ��̘A�����X�g�𐶐� */
ListPtr create_list(void)
{
    ListPtr l = NULL;
    l = malloc(sizeof(List));
    l->head = NULL;
    return l;
}

/* �A�����X�g l ���󂩂ǂ������� */
int is_empty(ListPtr l)
{
    return (l->head == NULL);
}

/* ���X�g l �̓��e���t���ŕ\���i���p�ۑ�1�j*/
void print_list_in_reverse(ListPtr l)
{
}

/* ���X�g l �̓��e��\�� */
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

/* ���X�g l �̐擪�ɃZ����}�� */
void add_first(ListPtr l, int val)
{
    NodePtr n = NULL;
    n = create_node(val);
    n->next = l->head;
    l->head = n;
}

/* ���X�g l �̐擪�Z�����폜 */
int delete_first(ListPtr l)
{
    NodePtr n = NULL;
    int v;

    /* ���X�g����Ȃ� -1 ��Ԃ��i���̒l�̓��X�g�Ɋ܂܂�Ȃ��Ɖ���j*/
    if (is_empty(l)) return -1;

    v = l->head->val;
    n = l->head;
    l->head = l->head->next;
    free(n);
    n = NULL;

    return v;
}

/* �A�����X�g l �̃T�C�Y���擾 */
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
 * �A�����X�g l �ɂ����� index �Ԗڂ̃Z���̒l���擾
 * �i���̂悤�ȃZ�������݂��Ȃ���� -1 ��Ԃ��j
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

/* ���X�g l ���̑S�Z�����폜�i���[�v�Łj*/
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

/* �Z�� n �ȍ~��S�č폜�i���������p�̍ċA�֐��j*/
void delete_rest(NodePtr n)
{
    if (n->next != NULL) delete_rest(n->next);
    free(n);
}

/* ���X�g l ���̑S�Z�����폜�i�ċA�Łj*/
void delete_all_recursively(ListPtr l)
{
    if (l->head == NULL) return;
    delete_rest(l->head);
    l->head = NULL;
}

/* ���X�g l �S�̂��폜 */
#define delete_list(l) (delete_list0(l),l=NULL)
void delete_list0(ListPtr l)
{
    delete_all(l);
    free(l);
}

/* ���X�g l �ɂ����Ēl val �����Z���̈ʒu��Ԃ� */
int get_index(ListPtr l, int val)
{
    NodePtr n = l->head;
    int index = 0;

    while (n != NULL) //n��null�̏ꍇ�C�I��
    {
        if (n->val == val) {
            return index;
        }
        n = n->next;
        index++;
    }

    return -1; // �l val �����Z�������݂��Ȃ��ꍇ
}

/* ���X�g l �̈ʒu index �ɒl val �����Z����}�� */
void add(ListPtr l, int index, int val)
{
    /* �ۑ�2:�����ɐ��������s���e������! */
}

/* �A�����X�g�̎g�p�� */
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

    /* �����Đ擪�v�f�̓��X�g�ɒǉ����Ȃ� */
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
