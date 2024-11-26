/**
 * クラス：A
 * 学籍番号：231205044
 * 氏名：岡田采留
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (30)
#define N (5)

struct person {
    char name[MAX_NAME]; /*名前*/
    int age; /*年齢*/
};

int compare_person (const void *p, const void *q)
{
    /*比較関数の内容*/
    struct person *person1 = p;
    struct person *person2 = q;

    if (person1->age > person2->age) return 1;
    else if (person1->age == person2->age) return strcmp(person1->name, person2->name);
    else return -1;
}

int main(void)
{
    struct person a[N] = {
        {"Shiogama Hanako", 23},
        {"Shiogama Saburo", 22},
        {"Yagoto Shiro", 22},
        {"Meijo Taro", 25},
        {"Meijo Jiro", 22}
    };

    int i;

    qsort(a, N, sizeof(struct person), compare_person);

    for (i = 0; i < N; i++)
    {
        printf("(name=%s, age=%d)\n", a[i].name, a[i].age);
    }
    
    return 0;
}