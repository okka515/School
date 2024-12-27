/*
* vector.h: ������̉ϒ��z��̌^�Ƃ��̑���p�֐��̃w�b�_�t�@�C��
*/
#ifndef VECTOR_H
#define VECTOR_H

/* �ϒ��z��Ƃ��̃|�C���^�̌^ */
typedef struct vector Vector;
typedef Vector *VectorPtr;

/* �ϒ��z��𐶐����� */
VectorPtr create_vector(void);

/* �ϒ��z�� v ��������� */
#define delete_vector(v) (delete_vector0(v),v=NULL)
void delete_vector0(VectorPtr v);

/* �ϒ��z�� v ������������i���g�p��Ԃɂ��邾���ŗ̈�͉�����Ȃ��j�D*/
void clear_vector(VectorPtr v);

/* �ϒ��z�� v �̍Ō�ɕ����� s ��ǉ� */
void append(VectorPtr v, char *s);

/* �ϒ��z��́i�g�p�����́j�T�C�Y��Ԃ��D*/
int get_vector_size(VectorPtr v);

/* �ϒ��z�� v �ɂ�����Y���� index �̗v�f�i������j���擾 */
char *get_elem(VectorPtr v, int index);

/* �ϒ��z��̓��e�����ɕ��ׂĕ\������D*/
void print_vector(VectorPtr v);

#endif
