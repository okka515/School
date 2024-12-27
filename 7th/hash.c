/*
* hash.c: �n�b�V���\�̌^�Ƃ��̑���p�֐��̒�`
* �i�n�b�V���\�̃L�[�F������C�l�F�񕉂̐����j
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

#if defined(__APPLE__) || defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__CYGWIN64__)
#define _strdup strdup
#endif

#define HASH_SIZE 997 /* �n�b�V���\�̓����z��̃T�C�Y */
#define HASH_RADIX 97 /* �n�b�V���֐��p�̊ */

/* �n�b�V���\���̘A�����X�g�Ɋ܂܂��m�[�h�Ƃ��̃|�C���^�̌^�D */
typedef struct hash_node HashNode;
typedef HashNode *HashNodePtr;

/* �n�b�V���\���̘A�����X�g�Ɋ܂܂��m�[�h�̍\���́D */
struct hash_node { /* �n�b�V���\���̘A�����X�g�̃m�[�h */
    char *key; /* �L�[ */
    int value; /* �L�[�ɑΉ�����l */
    int id;    /* �L�[�ɕt�^���ꂽ�ʂ��ԍ� */
    struct hash_node *next; /* ���̃m�[�h�ւ̃|�C���^ */
};

/* �n�b�V���\�̍\���́D */
struct hashtable {
    HashNodePtr *heads; /* �����z�� */
    int serial_id; /* �ʂ��ԍ��Ǘ��p�̕ϐ� */
    int size; /* �����z��̃T�C�Y */
};

/* static �֐��̃v���g�^�C�v�錾 */
static unsigned int hash(char *s);
static int get_index(HashTablePtr t, char *key);

/* ������ s �̃n�b�V���l���v�Z����D */
static unsigned int hash(char *s)
{
    unsigned int v;

    v = 0;
    while (*s != '\0') {
        v = v * HASH_RADIX + *s;
        s++;
    }

    return v;
}

/* �n�b�V���\����������C���̃|�C���^��Ԃ��D*/
HashTablePtr create_hashtable(void)
{
    HashTablePtr t = NULL;
    int i;

    t = malloc(sizeof(HashTable));
    if (t == NULL) {
        fprintf(stderr, "Couldn't allocate memory for a hashtable\n");
        exit(EXIT_FAILURE);
    }

    t->serial_id = 0;
    t->size = HASH_SIZE;
    t->heads = malloc(sizeof(HashNodePtr) * t->size);
    if (t->heads == NULL) {
        fprintf(stderr, "Couldn't allocate memory for a hashtable's header array\n");
        exit(EXIT_FAILURE);
    }

    /* �e�A�����X�g�̐擪�v�f�ւ̃|�C���^�͕K�� NULL �ɏ��������� */
    for (i = 0; i < t->size; i++) {
        t->heads[i] = NULL;
    }

    return t;
}

/* �n�b�V���\�̎����I�ȉ����Ƃ��s���D
* �i���X�� free() ����̂� free() ��� NULL ����͏ȗ��j
*/
void delete_hashtable0(HashTablePtr t)
{
    HashNodePtr n = NULL, m = NULL;
    int i;

    /* free() �Ɠ��l�CNULL�|�C���^�ɑ΂��Ă͉����s��Ȃ� */
    if (t == NULL) {
        return;
    }

    /* �e�A�����X�g�̗̈����� */
    for (i = 0; i < t->size; i++) {
        n = t->heads[i];
        while (n != NULL) {
            m = n;
            n = n->next;
            free(m);
        }
    }

    /* �Ō�ɘA�����X�g�̐擪�|�C���^�̗̈����� */
    free(t->heads);
    free(t);
}

/* �n�b�V���\ t �ɓo�^����Ă���L�[�ƒl�̃y�A�̐���Ԃ��D*/
int get_cardinality(HashTablePtr t)
{
    assert(t);
    return t->serial_id;
}

/* �n�b�V���\ t �̓����z��̓Y������Ԃ� */
static int get_index(HashTablePtr t, char *key)
{
    return hash(key) % t->size;
}

/* �n�b�V���\ t �ɂăL�[ key ���o�^����Ă����1,
* ����Ă��Ȃ����0��Ԃ��D
*/
int has_key(HashTablePtr t, char *key)
{
    assert(t && key);
    return (lookup(t, key) >= 0) ? 1 : 0;
}

/* �n�b�V���\ t �ɂăL�[ key �ɑΉ�����l��Ԃ��D
* �l��������Ȃ������� -1 ��Ԃ��D
* �i�n�b�V���\�̒l�Ƃ��ēo�^�ł���͔̂񕉂̐����l�Ɖ���j
*/
int lookup(HashTablePtr t, char *key)
{
    HashNodePtr n = NULL;
    int index;

    assert(t && key);

    /* �n�b�V���\�̓����z��̓Y�������v�Z */
    index = get_index(t, key);

    /* index �Ԗڂ̘A�����X�g��擪���珇�ɑ��� */
    n = t->heads[index];
    while (n != NULL) {
        /* �����Ŏw�肳�ꂽ key �ƃn�b�V���\���̃L�[����v������
        �����ɑΉ�����l��Ԃ� */
        if (strcmp(key, n->key) == 0) {
            return n->value;
        }

        /* ���������ɐi�߂� */
        n = n->next;
    }

    /* �L�[��������Ȃ������̂� -1 ��Ԃ� */
    return -1;
}

/* �L�[ key �ƒl value �̃y�A���n�b�V���\ t �ɓo�^���C���̒ʂ��ԍ���Ԃ��D
* �i�l value �͔񕉂ł���Ɖ���j
*/
int enter(HashTablePtr t, char *key, int value)
{
    HashNodePtr n = NULL, m = NULL;
    int index;

    assert(t && key);

    /* �d�l��̃G���[�Ȃ̂Ŕ񕉂̒l���n���ꂽ�Ƃ��̓��b�Z�[�W���o�� */
    if (value < 0) {
        fprintf(stderr, "Invalid value %d for key %s\n", value, key);
        exit(EXIT_FAILURE);
    }

    /* �����z��̓Y�������v�Z */
    index = get_index(t, key);

    /* �L�[ key �����ɓo�^����Ă��邩�T���C
    * �o�^����Ă���ꍇ�͒l�� value �ɍX�V����D
    */
    n = t->heads[index]; /* index �Ԗڂ� head ���o���_�Ƃ��� */
    while (n != NULL) {
        if (strcmp(key, n->key) == 0) { /* �o�^����Ă��� */
            n->value = value; /* �l���X�V */
            return n->id;
        }
        n = n->next;
    }

    /* �V�����m�[�h�𐶐� */
    m = malloc(sizeof(HashNode));
    if (m == NULL) {
        fprintf(stderr, "Couldn't allocate memory for a hash node\n");
        exit(EXIT_FAILURE);
    }

    m->key = _strdup(key);
    m->id = t->serial_id;
    m->value = value;

    /* �V�����m�[�h��擪�ɑ}�� */
    m->next = t->heads[index];
    t->heads[index] = m;

    t->serial_id++; /* ���̒ʂ��ԍ��ɍX�V */

    return m->id; /* �o�^�����L�[�ƒl�̃y�A�ɕt�^���ꂽ�ʂ��ԍ���Ԃ� */
}

/*
* �n�b�V���\ t �ɓo�^�����L�[�̔z���Ԃ��D
*�i���̔z��̃T�C�Y�� get_hash_cardinality() �Ŏ擾�\�j
*/
char **get_keys(HashTablePtr t)
{
    char **keys = NULL;
    HashNodePtr n;
    int i;

    assert(t);

    keys = malloc(sizeof(char *) * t->serial_id);
    if (keys == NULL) {
        fprintf(stderr, "Couldn't allocate memory for hashtable keys\n");
        exit(EXIT_FAILURE);
    }

    /* �e�A�����X�g�𑖍����C�z��ɋl�ߍ��� */
    for (i = 0; i < t->size; i++) {
        n = t->heads[i];
        while (n != NULL) {
            keys[n->id] = n->key; /* �ʂ��ԍ���z��Y������ */
            n = n->next;
        }
    }

    return keys; /* ��� free() ����K�v���� */
}

/* �n�b�V���\�̓��e��\������D*/
void print_hashtable(HashTablePtr t)
{
    HashNodePtr n = NULL;
    int i;

    assert(t);

    for (i = 0; i < t->size; i++) {
        n = t->heads[i];
        while (n != NULL) {
            printf("%s => %d\n", n->key, n->value);
            n = n->next;
        }
    }
}
