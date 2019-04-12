/*
 * 这是中M2019年春季班（第8期）的C语言入门和进阶两门课的练习题目集。
 * 普通编程题，标号7-27， 兔子繁衍问题 （15 分)
 * PTA，程序设计类实验辅助教学平台，https://pintia.cn
 * 作者：hitmanl
 * 日期：2019-04-12
 * 体会：
 * （1）第一次接触兔子繁衍问题，在草稿纸上推导了半天，本来想利用基本数据类型计算的，
 * （2）后来还是觉得使用结构体比较容易。
 * （3）第一次提交的时候，自动判题系统给出的结果是3个测试点通过，2个测试点未通过，
 * （4）经过检查没有逻辑问题之后，直接把兔子的变量数组的长度扩大到超出题目要求，
 * （5）然后就全部通过了。
 * （6）也许不是空间、时间复杂度上的好算法，重在理解推演过程和实现过程吧。
 * 收获：
 * （1）结构体是个好东西。
 */

#include <stdio.h>

#define N 20000

typedef struct rabbit {
	int num;
	int months;
} Rabbit;

int main(int argc, char const *argv[])
{
	int dest;
	scanf("%d", &dest);
	Rabbit a[N];
	for (int i = 0; i < N; i++) {
		a[i].num = 0;
		a[i].months = 0;
	}
	a[0].num = 1;
	a[0].months = 1;
	int mon;
	int sum = 0;
	for (mon = 1;; mon++) {
		for (int i = 0; i < N; i++) {
			if (a[i].num == 0) {
				break;
			}

			if (a[i].months > 2) {
				//a[i].num++;
				for (int j = i + 1; j < N; j++) {
					if (a[j].num == 0) {
						a[j].num++;
						a[j].months++;
						break;
					}
				}
			}
			a[i].months++;
		}
		for (int k = 0;; k++) {
			if (a[k].num) {
				sum += a[k].num;
			} else {
				break;
			}
		}

		//printf("month = %d, sum = %d\n", mon, sum);

		if (sum >= dest) {
			printf("%d", mon);
			return 0;
		} else {
			sum = 0;
		}
	}

	return 0;
}

/*
一对兔子，从出生后第3个月起每个月都生一对兔子。
小兔子长到第3个月后每个月又生一对兔子。
假如兔子都不死，请问第1个月出生的一对兔子，
至少需要繁衍到第几个月时兔子总数才可以达到N对？

输入格式:
输入在一行中给出一个不超过10000的正整数N。

输出格式:
在一行中输出兔子总数达到N最少需要的月数。

输入样例:
30
输出样例:
9

*/ 
