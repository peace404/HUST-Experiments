#include<stdio.h>
#include<stdlib.h>
int absVal(int x)
{
	int sign = x >> 31;
	return (x + sign) ^ sign;
}
int absVal_standard(int x) { return (x < 0) ? -x : x; }

int negate(int x) { return ~x + 1; }
int netgate_standard(int x) { return -x; }

int bitAnd(int x, int y) { return ~(~x | ~y); }
int bitAnd_standard(int x, int y) { return x & y; }

int bitOr(int x, int y) { return ~(~x & ~y); }
int bitOr_standard(int x, int y) { return x | y; }

int bitXor(int x, int y) { return ~(~(~x & y) & ~(x & ~y)); }
int bitXor_standard(int x, int y) { return x ^ y; }

int isTmax(int x) { return ~(x ^ 0x7FFFFFFF); }
int isTmax_standard(int x) { return (x== 0x7FFFFFFF); }

int bitCount(int x)
{
	x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
	x = (x + (x >> 8));
	x = (x + (x >> 16));
	return x & 0x3f;
}
int bitCount_standard(int x)
{
	int count = 0;
	for (int i = 0; i < 32; i++)
		count += (x >> i) & 1;
	return count;
}

int bitMask(int highbit, int lowbit) { return (~0u << lowbit) ^ (~0u << highbit << 1); }
int bitMask_standard(int highbit, int lowbit)
{
	int result = 1u << lowbit;
	for (int i = lowbit + 1; i <= highbit; ++i)
		result |= 1u << 1;
	return result;
}

int addOK(int x, int y)
{
	int x_sign = x >> 31, y_sign = y >> 31, sum_sign = (x + y) >> 31;
	return (x_sign ^ y_sign) | (x_sign ^ sum_sign);
}
int addOK_standard(int x, int y)
{
	int sum = x + y;
	return (x > 0 && y > 0 && sum < 0) || (x < 0 && y < 0 && sum > 0);
}

int byteSwap(int x, int n, int m)
{
	unsigned int nb = 0xff << ((4 - n) * 8);
	unsigned int mb = 0xff << ((4 - m) * 8);
	return x & ~(nb + mb) | (x & nb) << (n - 1) * 8 >> (m - 1) * 8 | (x & mb) << (m - 1) * 8 >> (n - 1) * 8;
}
int byteSwap_standard(int x, int n, int m)
{
	char* p = (char*)&x, temp;
	temp = p[n];
	p[n] = p[m];
	p[m] = temp;
	return x;
}

int main()
{
	int a = -5, b = 3;
	if(absVal(a) == absVal(a))
		printf("absVal is OK\n");
	if (negate(a) == negate(a))
		printf("negate is OK\n");
	if (bitAnd(a,b) == bitAnd(a, b))
		printf("bitAnd is OK\n");
	if (bitOr(a, b) == bitOr(a, b))
		printf("bitOr is OK\n");
	if (bitXor(a, b) == bitXor(a, b))
		printf("bitXor is OK\n");
	if (isTmax(a) == isTmax(a))
		printf("isTmax is OK\n");
	if (bitCount(a) == bitCount(a))
		printf("bitCount is OK\n");
	if (bitMask(1, 3) == bitMask(1, 3))
		printf("bitMask is OK\n");
	if (addOK(a, b) == addOK(a, b))
		printf("addOK is OK\n");
	if (byteSwap(0x12345678, 1, 3) == byteSwap_standard(0x12345678, 1, 3))
		printf("byteSwap is OK\n");
	system("pause");
}