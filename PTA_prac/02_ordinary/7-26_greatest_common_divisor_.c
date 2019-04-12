/*
 * 这是中M2019年春季班（第8期）的C语言入门和进阶两门课的练习题目集。
 * 普通编程题，标号7-26，最大公约数和最小公倍数 （15 分)
 * PTA，程序设计类实验辅助教学平台，https://pintia.cn
 * 作者：hitmanl
 * 日期：2019-04-12
 * 体会：
 * （1）之前看过也仿照写过求最大公约数、最小公倍数的函数，记得比较清楚的是辗转相除法，
 * （2）但是辗转相除法的具体过程没有记得很清楚，在做这道题的时候还是打了草稿，推演了一下的。
 * （3）还好，还是记得大数去对小数取余，然后辗转。
 * （4）有了最大公约数之后，再推导最小公倍数就简单了，把两数与最大公约数的倍数以及最大公约数
 * （5）三者相乘就可以了。
 * 收获：
 * （1）理解了计算最大公约数的辗转相除法，可以自行推导了，比死记硬背好。
 */

#include <stdio.h>

int zdgys(int a, int b);
int zxgbs(int a, int b);

int main(int argc, char const *argv[])
{
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%d and %d , zdgys = %d\n", a, b, zdgys(a, b));
	printf("%d and %d , zxgbs = %d\n", a, b, zxgbs(a, b));
	return 0;
}

// 最大公约数，辗转相除法
int zdgys(int a, int b)
{
	int min, max;
	if (a > b) {
		min = b;
		max = a;
	} else {
		min = a;
		max = b;
	}
	while (max % min != 0) {
		int temp = min;
		min = max % min;
		max = temp;
	}
	return min;
}

// 最小公倍数，利用最大公约数来计算
int zxgbs(int a, int b)
{
	int gys = zdgys(a, b);
	int gbs = (a / gys) * (b / gys) * gys;
	return gbs;
}