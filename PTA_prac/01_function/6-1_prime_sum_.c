/*
 * fn函数题，标号6-1，使用函数求素数和，分数20
 * PTA，程序设计类实验辅助教学平台，https://pintia.cn
 * 作者：hitmanl
 * 日期：2019-04-01
 * 体会：把一个大程序拆分成多个小程序，注意返回值。
 * 收获：多练习，熟悉常见的问题。
 * */

#include <stdio.h>

int prime(int p);
int PrimeSum(int m, int n);

int main()
{
	int m, n, p;
	scanf("%d %d", &m, &n);
	printf("Sum of ( ");
	for (p = m; p <= n; p++) {
		if (prime(p) != 0)
			printf("%d ", p);
	}
	printf(") = %d\n", PrimeSum(m, n));
	return 0;
}

/* 你的代码将被嵌在这里 */

int prime(int p)
{
	if (p < 2)
		return 0;

	if (p > 2 && p % 2 == 0)
		return 0;

	int i;
	for (i = 2; i < p; i++) {
		if (p % i == 0)
			break;
	}
	if (i == p) {
		return 1;
	} else {
		return 0;
	}
}

int PrimeSum(int m, int n)
{
	int sum = 0;
	int p;
	for (p = m; p <= n; p++) {
		if (prime(p) != 0)
			sum += p;
	}
	return sum;
}

/*
 * 本题要求实现一个判断素数的简单函数、以及利用该函数计算给定区间内素数和的函数。
 * 素数就是只能被1和自身整除的正整数。注意：1不是素数，2是素数。
 * 函数接口定义：
 * int prime( int p );
 * int PrimeSum( int m, int n );
 * 其中函数prime当用户传入参数p为素数时返回1，否则返回0；
 * 函数PrimeSum返回区间[m, n]内所有素数的和。
 * 题目保证用户传入的参数 m ≤  n 。
 * 输入样例：
 * -1 10
 * 输出样例：
 * Sum of ( 2 3 5 7 ) = 17
 * */
