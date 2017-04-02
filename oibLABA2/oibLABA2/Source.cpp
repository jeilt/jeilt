
#include<iostream>
#include <time.h>
long long  bin(unsigned short x1)
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

int CRC16(FILE *f)
{
	int y; int crc; int curcrc = 0;
	fseek(f, 0, SEEK_END);
	int length = ftell(f);
	fseek(f, 0, SEEK_SET);
	int polynom = 98309;
	while (length--)
	{
		crc = fgetc(f) << 8;
		crc ^= curcrc;
		y = 8;
		while (y)
		{
			if (crc <= 65535)
			{
				crc = crc << 1; y--;
			}
			else { crc ^= polynom; }
		}
		if (crc >= 65535) { crc = crc^polynom; }
		curcrc = crc;
	}
	return crc;
}
int main()
{
	double t = clock();
	FILE *f = fopen("эталон.txt", "r");
	unsigned short crcdec = CRC16(f);
	printf("%d\n", crcdec);
	long long crcbin = bin(crcdec);
	printf("%llu\n", crcbin);
	fclose(f);
	printf("Time: %lf\n", (clock() - t) / CLOCKS_PER_SEC);
	system("pause");
	return(0);
}
