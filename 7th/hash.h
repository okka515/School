/*
* hash.h: �n�b�V���\�̌^�Ƃ��̑���p�֐��̃w�b�_�t�@�C��
* �i�n�b�V���\�̃L�[�F������C�l�F�񕉂̐����j
*/
#ifndef HASH_H
#define HASH_H

/* �n�b�V���\�Ƃ��̃|�C���^�̌^ */
typedef struct hashtable HashTable;
typedef HashTable *HashTablePtr;

/* �n�b�V���\����������C���̃|�C���^��Ԃ��D*/
HashTablePtr create_hashtable(void);

/* �n�b�V���\�̍폜���s���D*/
#define delete_hashtable(t) (delete_hashtable0(t),t=NULL)
void delete_hashtable0(HashTablePtr t);

/* �n�b�V���\ t �ɓo�^����Ă���L�[�ƒl�̃y�A�̐���Ԃ��D*/
int get_cardinality(HashTablePtr t);

/* �n�b�V���\ t �ɂăL�[ key ���o�^����Ă����1, ����Ă��Ȃ����0��Ԃ��D*/
int has_key(HashTablePtr t, char *key);

/* �n�b�V���\ t �ɂăL�[ key �ɑΉ�����l��Ԃ��D
 * �i�l��������Ȃ������� -1 ��Ԃ��j
 */
int lookup(HashTablePtr t, char *key);

/* �L�[ key �Ɛ��̐����l value �̃y�A���n�b�V���\ t �ɓo�^���C���̒ʂ��ԍ���Ԃ��D*/
int enter(HashTablePtr t, char *key, int value);

/* �n�b�V���\ t �ɓo�^�����L�[�̔z���Ԃ��D
 * �Ԃ��Ă����z��͌�� free() ����K�v������D
 */
char **get_keys(HashTablePtr t);

/* �n�b�V���\�̓��e��\������D*/
void print_hashtable(HashTablePtr t);

#endif
