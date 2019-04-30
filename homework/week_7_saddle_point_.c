// 鞍点，程序设计入门——C语言，第7周编程练习，题目二

/* 难点和体会：
（1）首先要看清题义、理清思路，查找的是正方形矩阵的元素的值，
（1-2）但是，返回的是元素的行下标、列下标；
（2）尽管有鞍点不存在的情况，但是如果首先预设鞍点不存在的话，
（2-2）反而增加了代码量，因为需要考虑特殊情况；
（3）算法本身不复杂，题目说得很明确了，某行的最大的值且该列的最小值。
*/ 

#include <stdio.h>

// 定义结构体，用来存放鞍点的行下标、列下标
struct pt {
	int col;
	int row;
};

struct pt maxInd(int **a, int col, int row);

int main()
{
	int n;
	scanf("%d", &n);
	int a[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	
        // 获取二维数组的各行的首地址
        int *p[n];
	for (int i = 0; i < n; i++) {
		p[i] = a[i];
	}

	struct pt ret;

	ret = maxInd(p, n, n);

	if (ret.col != -1 || ret.row != -1) {
		printf("%d %d", ret.col, ret.row);
	} else {
		printf("NO");
	}

	return 0;
}

// 查找鞍点，返回鞍点的行下标、列下标，变量类型为结构体pt
struct pt maxInd(int **a, int col, int row)
{
	struct pt maxind;
	// 预置第一个元素为鞍点，或者说，预设鞍点「存在」
	maxind.col = 0;
	maxind.row = 0;

        // 刚开始编写程序的时候，预设鞍点「不存在」，带来了2个问题：
        // （1）对于行数、列数为1的正方形矩阵，程序结果是NO，显然错误;
        // （2）对于所有元素相同的正方形矩阵，程序结果是NO，仍然错误。
        // 所以，改为预设鞍点存在，且置为第一个元素，上述问题消除。
        // 同时，因为有后续代码的对比，如果不是鞍点的话，仍然有正确结果。

	for (int i = 0; i < col; i++) {
		// （1）先找出行的最大值
		int max_c = a[i][0];
		for (int j = 0; j < row; j++) {
			if (max_c < a[i][j]) {
				max_c = a[i][j];
				maxind.col = i;
				maxind.row = j;
			}
		}
		// 检查行的最大值是不是该列的最小值
		for (int k = 0; k < col; k++) {
			if (a[maxind.col][maxind.row] > a[k][maxind.row]) {
				maxind.col = -1;
				maxind.row = -1;
				break;
			}
		}
		if (maxind.col != -1 || maxind.row != -1) {
			break;
		}
	}

	return maxind;
}

/*
题目内容：

给定一个n*n矩阵A。矩阵A的鞍点是一个位置（i，j），在该位置上的元素是第i行上的最大数，第j列上的最小数。一个矩阵A也可能没有鞍点。

你的任务是找出A的鞍点。




输入格式:

输入的第1行是一个正整数n, （1<=n<=100），然后有n行，每一行有n个整数，同一行上两个整数之间有一个或多个空格。


输出格式：

对输入的矩阵，如果找到鞍点，就输出其下标。下标为两个数字，第一个数字是行号，第二个数字是列号，均从0开始计数。

如果找不到，就输出

NO

题目所给的数据保证了不会出现多个鞍点。


输入样例：

4 

1 7 4 1 

4 8 3 6 

1 6 1 2 

0 7 8 9


输出样例：

2 1
时间限制：500ms内存限制：32000kb
*/

/*
特殊情况：
（1）正方形矩阵的行、列数为1的情况，鞍点必然是唯一的那个元素。
（2）正方形矩阵的所有元素相同，或有多个与第一个鞍点值相同的元素时，
（2-1）鞍点按第一个值来取，后面的相同的元素均忽略。
*/