/*
 * vector.c: ������̉ϒ��z��̌^�Ƃ��̑���p�֐��̒�`
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

#if defined(__APPLE__) || defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__CYGWIN64__)
#define _strdup strdup
#endif

/* �ϒ��z��̏����T�C�Y */
#define INIT_SIZE 5

/* �ϒ��^�z��̍\���� */
struct vector {
    char **elems; /* �v�f�i������j�̔z��i�Œ蒷�j*/
    int size;     /* �ϒ��z��̃T�C�Y */
    int capacity; /* �ϒ��z��̍ő�e�� */
};

/* static �֐��̃v���g�^�C�v�錾 */
static void expand_vector(VectorPtr v);

/* �ϒ��z��𐶐����� */
VectorPtr create_vector(void)
{
    VectorPtr v = NULL;

    v = malloc(sizeof(Vector));
    if (v == NULL) {
        fprintf(stderr, "Couldn't allocate memory for a vector\n");
        exit(EXIT_FAILURE);
    }

    v->elems = malloc(sizeof(char *) * INIT_SIZE);
    v->size = 0;  /* �����g�p�T�C�Y�� 0 */
    v->capacity = INIT_SIZE;

    return v;
}

/* �ϒ��z��̎����I�ȉ����Ƃ��s���D
 * �i���X�� free() ����̂� free() ��� NULL ����͏ȗ��j
 */
void delete_vector0(VectorPtr v)
{
    int i;

    /* free() �Ɠ��l�CNULL�|�C���^�ɑ΂��Ă͉����s��Ȃ� */
    if (v == NULL) {
        return;
    }

    /* �e�v�f�i������j�̗̈����� */
    for (i = 0; i < v->size; i++) {
        free(v->elems[i]);
    }
    free(v->elems); /* �����z��̗̈����� */
    free(v); /* �O���̘g����� */
}

/* �ϒ��z�� v ������������i���g�p��Ԃɂ��邾���ŗ̈�͉�����Ȃ��j�D*/
void clear_vector(VectorPtr v)
{
    int i;

    assert(v);

    /* �v�f�̊e���������� */
    for (i = 0; i < v->size; i++) {
        free(v->elems[i]);
        v->elems[i] = NULL;
    }

    /* �g�p�T�C�Y��0�ɂ��� */
    v->size = 0;
}

/* �ϒ��z�� v ���g�傷�� */
static void expand_vector(VectorPtr v)
{
    assert(v);

    /* �ő�e�ʂ�2�{�ɑ��₷ */
    v->capacity *= 2;

    /* �V�����ő�e�ʂ����̈���m�� */
    v->elems = realloc(v->elems, sizeof(char *) * v->capacity);

    /* �T�C�Y��ύX�ł��Ȃ������ꍇ�̃G���[���� */
    if (v->elems == NULL) {
        fprintf(stderr, "Couldn't re-allocate memory for a vector\n");
        exit(EXIT_FAILURE);
    }
}

/* �ϒ��z�� v �̍Ō�ɕ����� s ��ǉ� */
void append(VectorPtr v, char *s)
{
    assert(s);

    /* �e�ʂ���t�ɂȂ�����e�ʂ��g�傷�� */
    if (v->size == v->capacity) {
        expand_vector(v);
    }
    v->elems[v->size] = _strdup(s); /* �Ō�ɗv�f��ǉ� */
    v->size++; /* �g�p�����̃T�C�Y��1���₷ */
}

/* �ϒ��z��́i�g�p�����́j�T�C�Y��Ԃ��D*/
int get_vector_size(VectorPtr v)
{
    assert(v);
    return v->size;
}

/* �ϒ��z�� v �ɂ�����Y���� index �̗v�f�i������j���擾 */
char *get_elem(VectorPtr v, int index)
{
    assert(v);

    /* �z��Y�����͈̔͂��`�F�b�N */
    if (index < 0 || index >= v->size) {
        fprintf(stderr, "Index out of bounds");
        exit(EXIT_FAILURE);
    }
    /* �w�肳�ꂽ�Y�����̒l��Ԃ� */
    return v->elems[index];
}

/* �ϒ��z��̓��e�����ɕ��ׂĕ\������D*/
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
