// 程序设计入门——C语言，第8周「指针与字符串」编程练习，题目二
// 题目：GPS数据处理
// 作者：st2ne
// 日期：2019-05-10

#include <stdio.h>
#include <string.h>

int hex2dec(char *h);
int myxor(const char *x, int n);
int chk_end(const char *e);
void time_utc2bj(const char *u, char *b);

int main(void)
{
	char gprmc[200] = { '\0' };
	int flag = 1;
	char bj_time[9] = { '\0' };
	while (flag) {
		int i;
		char a;
		/*
                //使用getchar()来判断输入的每一行数据，始终不能通过网页的检测
                //换成使用scanf()来接收输入数据，一下子就通过网页的自动检测了
                //猜测是网页的自动检测功能，输入的数据的行尾不仅仅是'\n'
		for (i = 0; (a = getchar()) != '\n'; i++) {
			gprmc[i] = a;
		}
		gprmc[i] = '\0';
                */
		scanf("%s", gprmc);

		if (0 == strncmp("END", gprmc, 3)) {
			flag = 0;
		} else if (0 == strncmp("$GPRMC", gprmc, 6)) {
			//checkgprmc();
			int chkd = chk_end(strchr(gprmc, '*'));
			if (chkd == 2) {
				int len = strlen(gprmc);

				int last_key; //transform the last 2 digits from hex to dec
				char endhex[2] = { gprmc[len - 2],
						   gprmc[len - 1] };
				last_key = hex2dec(endhex);

				int xor_str_len = (int)(strchr(gprmc, '*') -
							strchr(gprmc, '$') - 1);

				int xor_num = myxor(&gprmc[1], xor_str_len);

				if (last_key == xor_num) {
					const char *ptr = NULL;
					ptr = strchr(gprmc, ',');
					ptr = strchr(&ptr[1], ',');
					if ('A' == ptr[1]) {
						ptr = strchr(gprmc, ',');
						// transform time from UTC to Beijing
						// UTC + 8 == Beijing time
						// UTC: hhmmss.sss，10 chars
						// Beijing time: hh:mm:ss, 8 chars
						time_utc2bj(&ptr[1], bj_time);
						bj_time[8] = '\0';
					}
				}
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		printf("%c", bj_time[i]);
	}

	return 0;
}

//check if there are two digits after mark *
int chk_end(const char *e)
{
	int count = 0;
	while (*(++e) != '\0') {
		count++;
	}
	return count;
}

//transform the last 2 digits from hex to dec
int hex2dec(char *h)
{
	int ret = 0;

	if (h[0] >= 'A' && h[0] <= 'F') {
		ret += ((h[0] - 'A') + 10) * 16;
	} else {
		ret += (h[0] - '0') * 16;
	}

	if (h[1] >= 'A' && h[1] <= 'F') {
		ret += (h[1] - 'A') + 10;
	} else {
		ret += h[1] - '0';
	}

	return ret;
}

//XOR all chars between '$' and '*'
int myxor(const char *x, int n)
{
	int ret = 0;
	int i;

	char y[n];
	for (int j = 0; j < n; j++) {
		y[j] = x[j];
	}

	for (i = 0; i < n - 1; i++) {
		y[i + 1] = y[i] ^ y[i + 1];
	}
	ret = y[i] % 65536;

	return ret;
}

// transform time from UTC to Beijing
void time_utc2bj(const char *u, char *b)
{
	int len = 6;
	int h = 0;

	h = (u[0] - '0') * 10 + (u[1] - '0');
	h = (h + 8) % 24;

	if (h < 10) {
		b[0] = '0';
		b[1] = h + '0';
	} else {
		b[0] = h / 10 + '0';
		b[1] = h % 10 + '0';
	}

	for (int i = 2, j = 2; i < len; i++, j++) {
		if (i % 2 == 0) {
			b[j++] = ':';
			b[j] = u[i];

		} else {
			b[j] = u[i];
		}
	}
}

/*
测试数据：
$GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50
$GPRMC,010101.130,A,3606.6834,N,12021.7778,E,0.0,238.3,010807,,,A*6C
$GPRMC,030025.000,A,3130.318461,N,12020.273168,E,0.000,40.8,020914,,,A*58
END
*/

/*
GPS数据处理

题目内容：

NMEA-0183协议是为了在不同的GPS（全球定位系统）导航设备中建立统一的BTCM（海事无线电技术委员会）标准，由美国国家海洋电子协会（NMEA-The National Marine Electronics Associa-tion）制定的一套通讯协议。GPS接收机根据NMEA-0183协议的标准规范，将位置、速度等信息通过串口传送到PC机、PDA等设备。


NMEA-0183协议是GPS接收机应当遵守的标准协议，也是目前GPS接收机上使用最广泛的协议，大多数常见的GPS接收机、GPS数据处理软件、导航软件都遵守或者至少兼容这个协议。


NMEA-0183协议定义的语句非常多，但是常用的或者说兼容性最广的语句只有$GPGGA、$GPGSA、$GPGSV、$GPRMC、$GPVTG、$GPGLL等。


其中$GPRMC语句的格式如下：

    $GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50


这里整条语句是一个文本行，行中以逗号“,”隔开各个字段，每个字段的大小（长度）不一，这里的示例只是一种可能，并不能认为字段的大小就如上述例句一样。

    字段0：$GPRMC，语句ID，表明该语句为Recommended Minimum Specific GPS/TRANSIT Data（RMC）推荐最小定位信息

    字段1：UTC时间，hhmmss.sss格式

    字段2：状态，A=定位，V=未定位

    字段3：纬度ddmm.mmmm，度分格式（前导位数不足则补0）

    字段4：纬度N（北纬）或S（南纬）

    字段5：经度dddmm.mmmm，度分格式（前导位数不足则补0）

    字段6：经度E（东经）或W（西经）

    字段7：速度，节，Knots

    字段8：方位角，度

    字段9：UTC日期，DDMMYY格式

    字段10：磁偏角，（000 - 180）度（前导位数不足则补0）

    字段11：磁偏角方向，E=东W=西

    字段16：校验值

这里，“*”为校验和识别符，其后面的两位数为校验和，代表了“$”和“*”之间所有字符（不包括这两个字符）的异或值的十六进制值。上面这条例句的校验和是十六进制的50，也就是十进制的80。


提示：^运算符的作用是异或。将$和*之间所有的字符做^运算(第一个字符和第二个字符异或，结果再和第三个字符异或，依此类推)之后的值对65536取余后的结果，应该和*后面的两个十六进制数字的值相等，否则的话说明这条语句在传输中发生了错误。注意这个十六进制值中是会出现A-F的大写字母的。


现在，你的程序要读入一系列GPS输出，其中包含$GPRMC，也包含其他语句。在数据的最后，有一行单独的

    END

表示数据的结束。


你的程序要从中找出$GPRMC语句，计算校验和，找出其中校验正确，并且字段2表示已定位的语句，从中计算出时间，换算成北京时间。一次数据中会包含多条$GPRMC语句，以最后一条语句得到的北京时间作为结果输出。

你的程序一定会读到一条有效的$GPRMC语句。


输入格式:

多条GPS语句，每条均以回车换行结束。最后一行是END三个大写字母。


输出格式：

6位数时间，表达为：

    hh:mm:ss

其中，hh是两位数的小时，不足两位时前面补0；mm是两位数的分钟，不足两位时前面补0；ss是两位数的秒，不足两位时前面补0。


输入样例：

$GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50

END


输出样例：

10:48:13
时间限制：500ms内存限制：32000kb
*/