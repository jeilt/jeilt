#include<iostream>
#include<time.h>
long long bin(unsigned short x1)
{
	long long b;
	long long  bin = 0;
	for (int i = 0; x1 > 0; i++)
	{
		b = x1 % 2;
		x1 = (x1 - b) / 2;
		bin += b * pow(10, i);
	}
	return bin;
}
unsigned short Crc16(FILE *f)
{
	int crc = 0;
	fseek(f, 0, SEEK_END);
	int length = ftell(f);
	fseek(f, 0, SEEK_SET);
	while (length--)
	{
		crc ^= fgetc(f) << 8;
		for (int j = 0; j < 8; j++)
			crc = crc & 0x8000 ? (crc << 1) ^ 0x8005 : crc << 1;
	}
	return crc;
}
int main()
{
	double t = clock();
	FILE *f = fopen("эталон.txt", "r");
	unsigned short crcdec = Crc16(f);
	fclose(f);
	printf("%d\n", crcdec);
	long long crcbin = bin(crcdec);
	printf("%llu\n", crcbin);
	printf("Time: %lf\n", (clock() - t) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}

