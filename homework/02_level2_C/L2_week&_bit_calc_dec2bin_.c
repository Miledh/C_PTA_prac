/* Show the binary format of a number. */

#include <stdio.h>

int main(void)
{
	int number;
	printf("Enter an int number (decimal only): ");
	scanf("%d", &number);
	int bytes = sizeof(int);
	unsigned mask = 1u << (bytes * 8 - 1);
	for (; mask; mask >>= 1) {
		printf("%d", number & mask ? 1 : 0);
	}
	printf("\nBinary format of %d (decimal) is shown above.\n", number);
	return 0;
}
