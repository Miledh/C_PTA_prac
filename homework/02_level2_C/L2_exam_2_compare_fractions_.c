/*
C语言程序设计进阶，期末考试编程部分题目2，分数比较（10分）

题目内容：
本题要求编写程序，比较两个分数的大小。

输入格式:
输入在一行中按照“a1/b1 a2/b2”的格式给出两个分数形式的有理数，其中分子和分母全是int类型范围内的正整数。

输出格式：
在一行中按照“a1/b1 关系符 a2/b2”的格式输出两个有理数的关系。其中“>”表示“大于”，“<”表示“小于”，“=”表示“等于”。
注意在关系符前后各有一个空格。

输入样例：
1/2 3/4

输出样例：
1/2 < 3/4

时间限制：500ms内存限制：32000kb
*/

/*
代码思路：
（1）对分母通分，然后比较分子的大小；
（2）提升中间过程的数值类型，扩大取值范围，避免数值溢出。
*/

#include <stdio.h>

/* 下面的是比较简单直接的算法，需要注意中间过程最小公倍数是否会溢出类型的取值范围。*/

typedef struct fraction {
	int mol; // 分子
	int den; // 分母
} FC;

long long min_com_mul(int den_a, int den_b);
int max_num_con(int mol, int den);
int compare(int mol_a, int mol_b, int den_a, int den_b, long long mcm);

int main(void)
{
	FC fc_1, fc_2;
	scanf("%d/%d", &fc_1.mol, &fc_1.den);
	scanf("%d/%d", &fc_2.mol, &fc_2.den);
	switch (compare(fc_1.mol, fc_2.mol, fc_1.den, fc_2.den,
			min_com_mul(fc_1.den, fc_2.den))) {
	case 1:
		printf("%d/%d > %d/%d", fc_1.mol, fc_1.den, fc_2.mol, fc_2.den);
		break;
	case 0:
		printf("%d/%d = %d/%d", fc_1.mol, fc_1.den, fc_2.mol, fc_2.den);
		break;
	case -1:
		printf("%d/%d < %d/%d", fc_1.mol, fc_1.den, fc_2.mol, fc_2.den);
		break;
	}
	return 0;
}

// 约分

// 最小公倍数
long long min_com_mul(int den_a, int den_b)
{
	int mnc = max_num_con(den_a, den_b);
	if (1 != mnc) {
		return den_b / mnc * den_a;
	} else {
		return den_a * den_b;
	}
}

// 通分

// 最大公约数
int max_num_con(int den_a, int den_b)
{
	// 辗转相除法
	while (den_b % den_a) {
		den_a = den_b % den_a;
		den_b = den_a;
	}
	return den_a;
}

// 通分为同样的分母后，直接比较分子即可

int compare(int mol_a, int mol_b, int den_a, int den_b, long long mcm)
{
	long long a = mcm / den_a * mol_a;
	long long b = mcm / den_b * mol_b;
	if (a > b) {
		return 1;
	} else if (a == b) {
		return 0;
	} else {
		return -1;
	}
}