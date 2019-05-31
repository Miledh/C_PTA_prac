/*
第五周编程练习，2，念整数
题目内容：
你的程序要读入一个整数，范围是[-100000,100000]。然后，用汉语拼音将这个整数的每一位输出出来。
如输入1234，则输出：
yi er san si
注意，每个字的拼音之间有一个空格，但是最后的字后面没有空格。当遇到负数时，在输出的开头加上“fu”，如-2341输出为：
fu er san si yi

输入格式:
一个整数，范围是[-100000,100000]。

输出格式：
表示这个整数的每一位数字的汉语拼音，每一位数字的拼音之间以空格分隔，末尾没有空格。

输入样例：
-30

输出样例：
fu san ling
*/

#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	if (n < -100000 || n > 100000) {
		return 0;
	}

	if (n < 0) {
		printf("fu ");
		n = -n;
	}

	// n的位数最多是6位，定义一个数组来存储各位上的数字
	int m[6] = { -1 };
	int i;
	// count统计n的实际位数，即m[]数组的有效元素个数及下标
	int count = 0;
	//  不在循环条件里使用 n != 0; 的原因是，n可以是0，
	// 至少需要执行1次循环
	for (i = 0;; i++) {
		m[i] = n % 10;
		n = n / 10;
		count++;
		if (n == 0)
			break;
	}

	// count统计的是位数，比数组下标大1
	for (i = count - 1; i >= 0; i--) {
		switch (m[i]) {
		case 0:
			printf("ling");
			break;
		case 1:
			printf("yi");
			break;
		case 2:
			printf("er");
			break;
		case 3:
			printf("san");
			break;
		case 4:
			printf("si");
			break;
		case 5:
			printf("wu");
			break;
		case 6:
			printf("liu");
			break;
		case 7:
			printf("qi");
			break;
		case 8:
			printf("ba");
			break;
		case 9:
			printf("jiu");
			break;
		}
		// 输出空格这样的重复性工作，不要放到字符串里
		if (i != 0) {
			printf(" ");
		}
	}
	return 0;
}
