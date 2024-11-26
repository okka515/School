/**
 * �N���X�FA
 * �w�Дԍ��F231205044
 * �����F���c�ї�
 */

#include <stdio.h>
#include <stdlib.h>

/* �ϒ��z��̏����T�C�Y */
#define INIT_SIZE 5

/* �ϒ��^�z��̍\���� */
struct vector {
    int *elems;   /* �v�f�̔z��i�Œ蒷�j*/
    int size;     /* �ϒ��z��̃T�C�Y */
    int capacity; /* �ϒ��z��̍ő�e�� */
};

typedef struct vector Vector;
typedef Vector *VectorPtr;

/* �ϒ��z��𐶐����� */
VectorPtr create_vector()
{
    VectorPtr v = NULL;

    v = malloc(sizeof(Vector));

    v->elems = malloc(sizeof(int) * INIT_SIZE);
    v->size = 0;  /* �����g�p�T�C�Y�� 0 */
    v->capacity = INIT_SIZE;

    return v;
}

/* �ϒ��z�� v ���������i�}�N���Œ�`���Ă����j */
#define delete_vector(v) (delete_vector0(v),v=NULL)
void delete_vector0(VectorPtr v)
{
    free(v->elems);
    free(v);
}

/* �ϒ��z�� v ���g�傷�� */
void expand_vector(VectorPtr v)
{
    /* �ő�e�ʂ�2�{�ɑ��₷ */
    v->capacity *= 2;

    /* �V�����ő�e�ʂ����̈���m�� */
    v->elems = realloc(v->elems, sizeof(int) * v->capacity);

    /* �T�C�Y��ύX�ł��Ȃ������ꍇ�̃G���[���� */
    if (v->elems == NULL) {
        fprintf(stderr, "Couldn't allocate memory\n");
        exit(EXIT_FAILURE);
    }
}

/* �ϒ��z�� v �̍Ō�ɐ����v�f e ��ǉ� */
void append(VectorPtr v, int e)
{
    /* �e�ʂ���t�ɂȂ�����e�ʂ��g�傷�� */
    if (v->size == v->capacity) {
        expand_vector(v);
    }
    v->elems[v->size] = e; /* �Ō�ɗv�f��ǉ� */
    v->size++; /* �g�p�����̃T�C�Y��1���₷ */
}

/* �ϒ��z�� v �ɂ�����Y���� index �̗v�f���擾 */
int get_elem(VectorPtr v, int index)
{
    /* �z��Y�����͈̔͂��`�F�b�N */
    if (index < 0 || index >= v->size) {
        fprintf(stderr, "Index out of bounds");
        exit(EXIT_FAILURE);
    }
    /* �w�肳�ꂽ�Y�����̒l��Ԃ� */
    return v->elems[index];
}

/*�o�u���\�[�g�A���S���Y���̎g�p*/
void sort(VectorPtr v)
{
    int i, j, temp;
    for (i = 0; i < v->size - 1; i++)
    {
        for (j = 0; j < v->size - 1 - i; j++)
        {
            if (v->elems[j] > v->elems[j + 1])
            {
                /*����*/
                temp = v->elems[j];
                v->elems[j] = v->elems[j + 1];
                v->elems[j + 1] = temp;
            }
        }
    }
}


/* �ϒ��z��̎g�p�� */
int main(void)
{
    VectorPtr v = NULL;
    int i, r;

    /* �ϒ��z��𐶐� */
    v = create_vector();

    /* �����_���ɐ����𐶐����C�ϒ��z��ɒǉ� */
    srand((unsigned int)time(NULL));
    for (i = 0; i < 10; i++) {
        r = rand() % 1000;
        append(v, r);
        printf("Added: %d\n", r);
    }

    /* �ϒ��z��̃T�C�Y�ƍő�e�ʂ�\�� */
    printf("\n");
    printf("Size = %d\n", v->size);
    printf("Capacity = %d\n", v->capacity);
    printf("\n");

    /* �ϒ��z��̓��e��\�� */
    printf("Contents:\n");
    for (i = 0; i < v->size; i++) {
        printf("  %d\n", get_elem(v, i));
    }

    /*�ϒ��z��̓��e�������ɐ���*/
    sort(v);

    /*�����̉ϒ��z��̓��e��\��*/
    printf("Contents:\n");
    for (i = 0; i < v->size; i++)
    {
        printf("  %d\n", get_elem(v, i));
    }

    /* �ϒ��z����폜 */
    delete_vector(v);

    return 0;
}
