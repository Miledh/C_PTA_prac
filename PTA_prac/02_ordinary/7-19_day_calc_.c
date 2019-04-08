/*
 * 这是中M2019年春季班（第8期）的C语言入门和进阶两门课的练习题目集。
 * 普通编程题，标号7-19，计算天数 （15 分)
 * PTA，程序设计类实验辅助教学平台，https://pintia.cn
 * 作者：hitmanl
 * 日期：2019-04-07
 * 体会：
 * （1）之前做过一次，所以根据回忆，直接使用switch语句。
 * （2）尽管有印象，但还是忘记了细节的处理：闰年的多一天的处理。
 * （3）一开始是把闰年多的一天放到最后面去累加的，但是这样就导致了问题：
 * （4）输入的月份是2月或者1月的话，就会多加一天。
 * （5）最终修正为：把闰年多的一天放到case 3:的语句里面。
 * 收获：
 * （1）题目本身不复杂，除了掌握switch的顺序执行特点外，还要避免逻辑失误。
 */

#include <stdio.h>

int main(int argc, char const *argv[])
{
	int year, month, day;
	int leap = 0;
	int day_num = 0;
	scanf("%d/%d/%d", &year, &month, &day);
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		leap = 1;
	switch (month) {
	case 12:
		day_num += 30;
	case 11:
		day_num += 31;
	case 10:
		day_num += 30;
	case 9:
		day_num += 31;
	case 8:
		day_num += 31;
	case 7:
		day_num += 30;
	case 6:
		day_num += 31;
	case 5:
		day_num += 30;
	case 4:
		day_num += 31;
	case 3:
		day_num += 28 + leap; // 这里是易错点。
	case 2:
		day_num += 31;
	case 1:
		day_num += day;
	}
	printf("%d", day_num);
	return 0;
}

/*
 * 本题要求编写程序计算某年某月某日是该年中的第几天。
 * 输入格式:
 * 输入在一行中按照格式“yyyy/mm/dd”（即“年/月/日”）给出日期。
 * 注意：闰年的判别条件是该年年份能被4整除但不能被100整除、或者能被400整除。
 * 闰年的2月有29天。
 * 输出格式:
 * 在一行输出日期是该年中的第几天。
 * 输入样例1:
 * 2009/03/02
 * 输出样例1:
 * 61
 * 输入样例2:
 * 2000/03/02
 * 输出样例2:
 * 62
 * */
