/*
 * クラス: X
 * 学籍番号: 2X1205XXX
 * 氏名: 名城太郎
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 一人が持てる書籍の上限 */
#define MAX_BOOKS 3
#define MAX_PERSONS 3

/* 人物型（構造体の仮宣言含む） */
typedef struct person Person;
typedef Person *PersonPtr;

/* 書籍型（構造体の仮宣言含む） */
typedef struct book Book;
typedef Book *BookPtr;

/* 人物データのメンバ */
struct person {
	char *name;  /* 名前 */
	int age;     /* 年齢 */
	int n_books; /* 購入書籍数 */
};

/* 書籍データのメンバ */
struct book {
	char *title; /* タイトル */
	int price;   /* 価格 */
    int n_persons;
    PersonPtr persons[MAX_PERSONS];
};

/* 名前 name, 年齢 age の人物データを生成 */
PersonPtr create_person(char *name,
						int age) {
	PersonPtr u =
			malloc(sizeof(Person));

	u->name = strdup(name);
	u->age = age;
	u->n_books = 0; /* 購入書籍数は初め 0 */

	return u;
}

/* 人物データの内容を表示 */
void print_person(PersonPtr u) {
	int i;

	printf("(name=%s, age=%d)\n",
		u->name, u->age);
}

void delete_person(PersonPtr u) {
	if (u == NULL) return;
	free(u->name);
	free(u);
}

/* 書籍データを生成 */
BookPtr create_book(char *title, int price) {
	BookPtr b = malloc(sizeof(Book));

	b->title = strdup(title);
	b->price = price;
    b->n_persons = 0;

	return b;
}

/* 書籍データを削除 */
void delete_book(BookPtr b) {
	if (b == NULL) return;
	free(b->title);
	free(b);
}

/* 書籍データの内容を表示 */
void print_book(BookPtr b) {
    PersonPtr u = NULL;
	printf("(title=%s, price=%d)\n", b->title, b->price);

    for (int i = 0; i < b->n_persons; i++)
    {
        u = b->persons[i];
        printf("    (name=%s, age=%d)\n", u->name, u->age);
    }
    
}

/* 人物 u が書籍 b を購入 */
void buy(PersonPtr u, BookPtr b) {
	if (u->n_books < MAX_BOOKS) { /* 購入書籍数が上限なら何もしない */
        b->persons[b->n_persons] = u;
		u->n_books++; /* 同時に購入書籍数を1増加しておく */
        b->n_persons++;
	}
}

int main(void) {
	PersonPtr u1 = create_person("名城太郎", 25);
	PersonPtr u2 = create_person("名城次郎", 22);
	PersonPtr u3 = create_person("塩釜花子", 23);
	PersonPtr u4 = create_person("塩釜三郎", 19);
	PersonPtr u5 = create_person("八事四郎", 20);

	BookPtr b1 = create_book("吾輩は猫である", 680);
	BookPtr b2 = create_book("銀河鉄道の夜", 734);
	BookPtr b3 = create_book("赤毛のアン", 724);
	BookPtr b4 = create_book("プログラミング言語C", 3204);
	BookPtr b5 = create_book("シグナル＆ノイズ", 2592);
	BookPtr b6 = create_book("Cアルゴリズム事典", 2516);

	buy(u1, b1);
	buy(u1, b3);
	buy(u2, b2);
	buy(u2, b4);
	buy(u2, b5);
	buy(u3, b2);
	buy(u4, b1);
	buy(u5, b3);
	buy(u5, b5);

	print_book(b1);
	print_book(b2);
	print_book(b3);
	print_book(b4);
	print_book(b5);

	delete_person(u1);
	delete_person(u2);
	delete_person(u3);
	delete_person(u4);
	delete_person(u5);

	delete_book(b1);
	delete_book(b2);
	delete_book(b3);
	delete_book(b4);
	delete_book(b5);
	delete_book(b6);

	return 0;
}
