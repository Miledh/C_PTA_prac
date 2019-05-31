/*
C语言程序设计进阶，第4周编程练习，逆序输出（10分）

题目内容：
你的程序会读入一系列的正整数，预先不知道正整数的数量，一旦读到-1，就表示输入结束。
然后，按照和输入相反的顺序输出所读到的数字，不包括最后标识结束的-1。

输入格式:
一系列正整数，输入-1表示结束，-1不是输入的数据的一部分。

输出格式：
按照与输入相反的顺序输出所有的整数，每个整数后面跟一个空格以与后面的整数区分，最后的整数后面也有空格。

输入样例：
1 2 3 4 -1

输出样例：
4 3 2 1 

时间限制：500ms内存限制：32000kb
*/

/*
代码思路：
（1）建立有头、尾结点的链表，尾结点有实用数据；
（2）采用双向链表，便于反向遍历，一次性遍历。
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _num {
	int value;
	struct _num *previous;
	struct _num *next;
} Num;

typedef struct _list_num {
	Num *head;
	Num *tail;
} List;

void create_list_head(List *p_list);
void append_list(List *p_list, int digit);
void print_list_rev(List *p_list);

int main(int argc, char const *argv[])
{
	int digit;
	List mylist = { NULL, NULL };
	create_list_head(&mylist);
	scanf("%d", &digit);
	while (-1 != digit) {
		append_list(&mylist, digit);
		scanf("%d", &digit);
	}
	print_list_rev(&mylist);
	return 0;
}

void create_list_head(List *p_list)
{
	p_list->head = (Num *)malloc(sizeof(Num));
	if (p_list->head) {
		p_list->head->value = -1;
		p_list->head->previous = NULL;
		p_list->head->next = NULL;
		p_list->tail = p_list->head;
	} else {
		printf("list head malloc failed.\n");
		exit(EXIT_FAILURE);
	}
}

void append_list(List *p_list, int digit)
{
	p_list->tail->next = (Num *)malloc(sizeof(Num));
	if (p_list->tail->next) {
		p_list->tail->next->value = digit;
		p_list->tail->next->next = NULL;
		p_list->tail->next->previous = p_list->tail;
		p_list->tail = p_list->tail->next;
	} else {
		printf("list append malloc failed.\n");
		exit(EXIT_FAILURE);
	}
}

void print_list_rev(List *p_list)
{
	Num *arrow = p_list->tail;
	while (p_list->head != arrow) {
		printf("%d ", arrow->value);
		arrow = arrow->previous;
	}
}

/*
用例测试结果	运行时间	占用内存	提示	得分
用例1通过	2ms	        360kb	                2
用例2通过	2ms	        128kb	                2
用例3通过	2ms	        256kb	                2
用例4通过	2ms	        256kb	                2
用例5通过	13ms	        996kb	                2
*/