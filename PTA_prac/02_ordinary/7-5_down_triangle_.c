/*
 * 普通编程题，标号7-5，输出倒三角图案 （5 分)
 * PTA，程序设计类实验辅助教学平台，https://pintia.cn
 * 作者：hitmanl
 * 日期：2019-04-01
 * 体会：
 * （1）对图形进行解析的时候，多计算了最左边一个空格，糊涂了。
 * （2）最后一行的星号后面没有空格了，也需要判断。
 * 收获：需要更细致。
 */

#include <stdio.h>

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < i; j++) {
			printf(" ");
		}
		for (int k = 0; k < 4 - i; k++) {
			printf("*");
			if (k == 3 - i && i != 3)
				printf("\n");
			else if (i != 3)
				printf(" ");
		}
	}
	return 0;
}
