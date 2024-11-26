/*
 * hash.c: �n�b�V���\�̗�v���O����
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 997 /* �n�b�V���\�̓����z��̃T�C�Y */
#define HASH_RADIX 97 /* �n�b�V���֐��p�̊ */

/* �n�b�V���\���̘A�����X�g�Ɋ܂܂��m�[�h�̍\���� */
struct hash_node { /* �n�b�V���\���̘A�����X�g�̃m�[�h */
    char *key; /* �L�[ */
    int val;   /* �L�[�ɑΉ�����f�[�^�l */
    int id;    /* �L�[�ɕt�^���ꂽ�ʂ��ԍ� */
    struct hash_node *next; /* ���̃m�[�h�ւ̃|�C���^ */
};

typedef struct hash_node HashNode;
typedef HashNode *HashNodePtr;

/* �n�b�V���\�̍\���� */
struct hashtable {
    HashNodePtr *heads; /* �����z�� */
    int serial_id; /* �ʂ��ԍ��Ǘ��p�̕ϐ� */
    int size; /* �����z��̃T�C�Y */
};

typedef struct hashtable HashTable;
typedef HashTable *HashTablePtr;

/* ������ s �̃n�b�V���l���v�Z���� */
unsigned int hash(char *s)
{
    unsigned int v;

    v = 0;
    while (*s != '\0') {
        v = v * HASH_RADIX + *s;
        s++;
    }

    return v;
}

/* �n�b�V���\����������C���̃|�C���^��Ԃ� */
HashTablePtr create_hashtable()
{
    HashTablePtr t = NULL;
    int i;

    t = malloc(sizeof(HashTable));

    t->serial_id = 0;
    t->size = HASH_SIZE;
    t->heads = malloc(sizeof(HashNodePtr) * t->size);

    /* �e�A�����X�g�̐擪�v�f�ւ̃|�C���^�͕K�� NULL �ɏ��������� */
    for (i = 0; i < t->size; i++) {
        t->heads[i] = NULL;
    }

    return t;
}

/* �w�肵���|�C���^�ϐ��� NULL �������ďI��邽�߂̃}�N�� */
#define delete_hashtable(t) \
	(delete_hashtable0(t),t=NULL)

/* �����I�ȍ폜��Ƃ��s���֐��ifree ��� NULL ����͏ȗ��j*/
void delete_hashtable0(HashTablePtr t)
{
    HashNodePtr n = NULL, m = NULL;
    int i;

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

/* �n�b�V���\ t �ɓo�^����Ă���L�[�ƃf�[�^�l�̃y�A�̐���Ԃ� */
int get_cardinality(HashTablePtr t)
{
    return t->serial_id;
}

/* �n�b�V���\ t �ɂăL�[ key �ɑΉ�����f�[�^�l�𒲂ׂ� */
int lookup(HashTablePtr t, char *key)
{
    HashNodePtr n = NULL;
    int index;

    /* �n�b�V���\�̓����z��̓Y�������v�Z */
    index = hash(key) % t->size;

    /* index �Ԗڂ̘A�����X�g��擪���珇�ɑ��� */
    n = t->heads[index];
    while (n != NULL) {
        /* �����Ŏw�肳�ꂽ key �ƃn�b�V���\���̃L�[����v������
           �����ɑΉ�����f�[�^�l��Ԃ� */
        if (strcmp(key, n->key) == 0) {
            return n->val;
        }

        /* ���������ɐi�߂� */
        n = n->next;
    }
    /* �����ł̓L�[�ɑΉ�����f�[�^�l�͔񕉂ł���Ɖ��肵�C
       ������Ȃ������� -1 ��Ԃ� */
    return -1;
}

/* �L�[ key �ƃf�[�^�l val �̃y�A���n�b�V���\ t �ɓo�^���C���̒ʂ��ԍ���Ԃ� */
int enter(HashTablePtr t, char *key, int val)
{
    HashNodePtr n = NULL, m = NULL;
    int index;

    index = hash(key) % t->size; /* �����z��̓Y�������v�Z */

    /* �L�[�����ɑ��݂��Ă��邩�ǂ����`�F�b�N�ilookup() �Ɠ��������j*/
    n = t->heads[index];
    while (n != NULL) {
        if (strcmp(key, n->key) == 0) { /* �o�^����Ă��� */
            return n->id; /* �ʂ��ԍ���Ԃ� */
        }
        n = n->next;
    }

    /* �V�����m�[�h�𐶐� */
    m = malloc(sizeof(HashNode));
    m->key = _strdup(key);
    m->id = t->serial_id;
    m->val = val;

    /* �A�����X�g�� add_first() �Ɠ��l�ɂ��ĘA�����X�g�ɒǉ� */
    m->next = t->heads[index];
    t->heads[index] = m;
    t->serial_id++; /* ���̒ʂ��ԍ��ɍX�V */

    return m->id; /* �o�^�����L�[�ƃf�[�^�l�̃y�A�ɕt�^���ꂽ�ʂ��ԍ���Ԃ� */
}

/*
* �n�b�V���\ t �ɓo�^�����L�[�̔z���Ԃ�
*�i���̔z��̃T�C�Y�� get_cardinality() �Ŏ擾�\�j
*/
char **get_keys(HashTablePtr t)
{
    char **keys = NULL;
    HashNodePtr n = NULL;
    int i;

    keys = malloc(sizeof(char *) * t->serial_id);

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

void print_hashtable(HashTablePtr t)
{
    /* �ۑ�: �����Ɏ��s���e������! */
}

/* �n�b�V���\�̎g�p�� */
int main(void)
{
    HashTablePtr t = NULL;

    t = create_hashtable();

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
