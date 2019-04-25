// 多项式加法，程序设计入门——C语言，第7周编程练习，题目一

/* 难点和体会：
（1）排序、二分搜索算法本身的概念比较明确，不算难点；
（2）关键是，对结果的输出，要考虑多种情况；
（3）比如，某一项是否为0、是否第一项、系数为正为负、系数是否为1、幂是否为1或0等等。
（4）因为题目要求的输出结果是没有圆括号的，要不然的话直接用圆括号把系数括起来最简单。
*/

#include <stdio.h>

struct factor {
	int power; // 幂
	int fac; // 系数
};

typedef struct factor FACTOR;

void sortf(FACTOR a[], int len_a);
int searchf(int power_a, FACTOR b[], int len_b);

int main(void)
{
	FACTOR a[100], b[100];

	int i = -1;
	do {
		i++;
		scanf("%d%d", &a[i].power, &a[i].fac);
	} while (a[i].power != 0);
	int num_a = i + 1;
	sortf(a, num_a);

	i = -1;
	do {
		i++;
		scanf("%d%d", &b[i].power, &b[i].fac);
	} while (b[i].power != 0);
	int num_b = i + 1;
	sortf(b, num_b);

	FACTOR c[100];
	int num_c, index;
	for (num_c = 0; num_c < num_a; num_c++) {
		index = searchf(a[num_c].power, b, num_b);
		if (index != -1) {
			c[num_c].fac = a[num_c].fac + b[index].fac;
			c[num_c].power = a[num_c].power;
			b[index].fac = 111;
			b[index].power = 111;
		} else {
			c[num_c] = a[num_c];
		}
	}
	for (int j = 0; j < num_b; j++) {
		if (b[j].power != 111) {
			c[num_c++] = b[j];
		}
	}
	sortf(c, num_c);
        
	int count_0_fac = 0;
	int k;
	for (k = 0;; k++) {
		if (c[k].power <= 1) {
			break;
		}
		if (c[k].fac != 0) {
			if (count_0_fac == k) {
				if (c[k].fac == 1) {
					printf("x%d", c[k].power);
				} else {
					printf("%dx%d", c[k].fac, c[k].power);
				}
			} else {
				if (c[k].fac == 1) {
					printf("+x%d", c[k].power);
				} else if (c[k].fac > 0) {
					printf("+%dx%d", c[k].fac, c[k].power);
				} else {
					printf("%dx%d", c[k].fac, c[k].power);
				}
			}
		} else {
			count_0_fac++;
		}
	}

	if (c[k].power == 1) {
		if (c[k].fac != 0) {
			if (count_0_fac == k) {
				if (c[k].fac == 1) {
					printf("x");
				} else {
					printf("%dx", c[k].fac);
				}
			} else {
				if (c[k].fac == 1) {
					printf("+x");
				} else if (c[k].fac > 0) {
					printf("+%dx", c[k].fac);
				} else {
					printf("%dx", c[k].fac);
				}
			}
		} else {
			count_0_fac++;
		}
		k++;
	}

	if (c[k].power == 0) {
		if (c[k].fac != 0) {
			if (count_0_fac == k) {
				printf("%d", c[k].fac);
			} else {
				if (c[k].fac > 0) {
					printf("+%d", c[k].fac);
				} else {
					printf("%d", c[k].fac);
				}
			}
		} else {
			count_0_fac++;
		}
	}

	if (count_0_fac == num_c) {
		printf("0");
	}

	return 0;
}

void sortf(FACTOR a[], int len_a)
{
	for (int i = 0; i < len_a - 1; i++) {
		for (int num_c = i; num_c < len_a; num_c++) {
			if (a[i].power < a[num_c].power) {
				FACTOR temp;
				temp = a[i];
				a[i] = a[num_c];
				a[num_c] = temp;
			}
		}
	}
}

int searchf(int power_a, FACTOR b[], int len_b)
{
	int ret = -1;
	int left = 0, right = len_b - 1;
	int mid = (left + right) / 2;
	while (mid != left) {
		if (power_a == b[mid].power) {
			ret = mid;
			break;
		} else if (power_a > b[mid].power) {
			right = mid;
			mid = (left + right) / 2;
		} else {
			left = mid;
			mid = (left + right) / 2;
		}
	}
	if (power_a == b[left].power) {
		ret = left;
	} else if (power_a == b[right].power) {
		ret = right;
	}

	return ret;
}

/*
题目内容：

一个多项式可以表达为x的各次幂与系数乘积的和，比如：

2x6+3x5+12x3+6x+20

现在，你的程序要读入两个多项式，然后输出这两个多项式的和，也就是把对应的幂上的系数相加然后输出。

程序要处理的幂最大为100。


输入格式:

总共要输入两个多项式，每个多项式的输入格式如下：

每行输入两个数字，第一个表示幂次，第二个表示该幂次的系数，所有的系数都是整数。第一行一定是最高幂，最后一行一定是0次幂。

注意第一行和最后一行之间不一定按照幂次降低顺序排列；如果某个幂次的系数为0，就不出现在输入数据中了；0次幂的系数为0时还是会出现在输入数据中。


输出格式：

从最高幂开始依次降到0幂，如：

2x6+3x5+12x3-6x+20

注意其中的x是小写字母x，而且所有的符号之间都没有空格，如果某个幂的系数为0则不需要有那项。


输入样例：

6 2

5 3

3 12

1 6

0 20

6 2

5 3

2 12

1 6

0 20


输出样例：

4x6+6x5+12x3+12x2+12x+40
时间限制：500ms内存限制：32000kb
*/