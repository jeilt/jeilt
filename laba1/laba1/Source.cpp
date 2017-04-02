#include <iostream>
int checksum(FILE *f, int T) {
	while (!feof(f))
	{
		char s = fgetc(f);
		T += (int)s;
	}
	return (T + 1);
}
int main() {
	int T = 0; int M = 255;
	FILE *f = fopen("checksum.txt", "r");
	int z = checksum(f, T) % (M + 1);
	printf("%i\n", z);
	system("pause");
	return 0;
}
