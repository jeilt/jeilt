#include< stdio.h>
#include< conio.h>
#include< string.h>
#include<stdlib.h>
struct node
{
	char sym;
	double pro;
	int arr[20];
	int top;
}s[20];

typedef struct node node;






/*void prints(int l, int h, node s[])
{
	int i;
	for (i = l; i<= h; i++)
	{
		printf("\n%s\t%f", s[i].sym, s[i].pro);
	}
}*/

void shannon(int l, int h, node s[])
{
	float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
	int i, d, k, j;
	if ((l + 1) == h || l == h || l>h)
	{
		if (l == h || l>h)
			return;
		s[h].arr[++(s[h].top)] = 0;
		s[l].arr[++(s[l].top)] = 1;
		return;
	}
	else
	{
		for (i = l; i<= h - 1; i++)
			pack1 = pack1 + s[i].pro;
		pack2 = pack2 + s[h].pro;
		diff1 = pack1 - pack2;
		if (diff1< 0)
			diff1 = diff1*-1;
		j = 2;
		while (j != h - l + 1)
		{
			k = h - j;
			pack1 = pack2 = 0;
			for (i = l; i<= k; i++)
				pack1 = pack1 + s[i].pro;
			for (i = h; i>k; i--)
				pack2 = pack2 + s[i].pro;
			diff2 = pack1 - pack2;
			if (diff2< 0)
				diff2 = diff2*-1;
			if (diff2 >= diff1)
				break;
			diff1 = diff2;
			j++;
		}
		k++;
		for (i = l; i<= k; i++)
			s[i].arr[++(s[i].top)] = 1;
		for (i = k + 1; i<= h; i++)
			s[i].arr[++(s[i].top)] = 0;
		shannon(l, k, s);
		shannon(k + 1, h, s);
	}
}

unsigned char GetByte(const char data[])
{
	unsigned char byte = 0;
	const char* end = data + 8;

	for (; *data && (data < end); ++data)
	{
		byte <<= 1;

		byte |= (*data == '1') ? 1 : 0;
	}

	return byte;
}

void compressing(long long int e)
{
	char k;
	long long int t,i,n,j,u=0;
	char y;
	n = e;
	FILE*f = fopen("input.txt", "r");
	FILE*h = fopen("output.txt", "w");
	t = 0;

	while(feof(f)!=1)
	{
		y = fgetc(f);
		for (i = n - 1; i >= 0; i--)
		{
			if (s[i].sym == y)
			{
				
				for (j = 0; j <= s[i].top; j++)
				{
					
					fprintf(h, "%d", s[i].arr[j]);

				}
				break;
			}

		}



	}
	fclose(f);
	fclose(h);
	FILE*o = fopen("output.txt", "r");
	FILE*l = fopen("output.bin", "wb");
	while (feof(o) != 1)
	{
		char Buffer[8];
		const size_t nData = sizeof(Buffer) - 1;
		for (n = 0; n < 8; n++)
		{
			Buffer[n] = fgetc(o);
		}
		const char*array = Buffer;
		while (array - Buffer < nData)
		{
			unsigned char byte = GetByte(array);
			fwrite(&byte, 1, 1, l);
			array += 8;
		}
	}
	fclose(o);
	fclose(l);
}


char *decToBin(int x)
/*{
	char a;
	char *t = (char *)malloc(100);
	int i = 0;
	do
	{
		a = x % 2;
		if(a==-1)
		{
			a = 1;
		}
		t[i++] =a +'0';
		x = x / 2;
	} while (x != 0);
	t[i] = '\0';
	// инвертируем t
	int k = strlen(t) - 2;
	int m = k / 2;
	for (int i = 0; i <= m; i++)
	{
		char tmp = t[i];
		t[i] = t[k - i + 1];
		t[k - i + 1] = tmp;
	}
	return t;
}*/
{
	int r, a, i, w[8],n=0;
	char *t = (char *)malloc(sizeof(char));
	
	memset(w, 0, sizeof(w));
	for (i = 0; i<8; i++) w[i] = ((x >> i) & 1);

	for (i = 7, r = 0; i >= 0; i--)
	{
		t[n] = w[i] + '0';
		n++;
		
	}

	
	return t;
}

void decompressing(long long h)
{
	int d,n,temp,i;
	char a;
	int Bin[8] ;
	FILE*l = fopen("output.bin", "rb");
	FILE*f= fopen("output1.txt", "w");
	while (feof(l) != 1)
	{
		a = fgetc(l);
		d = a;
		char *t = decToBin(d);
		
		for (n = 0; n < 8; n++)
		{
			fputc(t[n], f);
		}
		
	}
	fclose(l);
	fclose(f);
	int j=0;
	n = 0;
	long long count=0;
	FILE*r = fopen("input1.txt", "w");
	FILE*b = fopen("output1.txt", "r");
	while (feof(b) != 1)
	{
		
		
		for (i = h - 1; i >= 0; i--)
		{
			loop: 
			while (n <= s[i].top && i>=0)
			{
				Bin[n] = fgetc(b);
				count++;
				Bin[n] -= 48;
				n++;
		
			}
			if (Bin[0] == 0 && Bin[1] == 0)
			{
				Bin[2] = fgetc(b);
				Bin[2] -= 48;
				Bin[3]= fgetc(b);
				Bin[3] -= 48;
				if (Bin[2] == 0&&Bin[3]==0)
				{
					goto end;
				}
				if (Bin[2] != 0&&Bin[3]!=0)
				{
					fseek(b, count, SEEK_SET);
				}
			}
			
			for (j = 0 && i >= 0; j <= s[i].top; j++)
			{
				if(Bin[j]!=s[i].arr[j])
				{
					i--;
					goto loop;
				}
				if (Bin[j] == s[i].arr[j] && j == s[i].top)
				{
					fputc(s[i].sym, r);
					
					i = -1;
					break;
				}
				
			}
			
			
		}
		n = 0;








		


	}
	end:
	fclose(r);
	fclose(b);
}




void main()
{
	char y;
	long long int n, i=0, j=0,t=0;
	float x, total = 0;
	char ch[10];
	long long int prob[10] = { 0 };
	node temp;
	system("cls"); 
	/*printf("Enter How Many Symbols Do You Want To Enter\t: ");
	scanf("%d", &n);*/
	FILE*f = fopen("input.txt", "r");
	for (n = 0; n < 100000; n++)
	{
		y = fgetc(f);
		
		for (i = 0; i < 10; i++)
		{

			if (y == s[i].sym)
			{
				prob[i]++;
				break;
			}
			if (i == 9 && s[9].sym != y)
			{
				
				s[t].sym=y;
				prob[t]++;
				t++;
				
			}
			
		}

	}
	
	
	n = t;
	double R;
	for (t=0; t < n; t++)
	{
		
		R = prob[t];
		R/= 100000;
		s[t].pro = R;
	}


	/*for (i = 0; i< n; i++)
	{
		printf("Enter symbol %d ---> ", i + 1);
		scanf("%s", ch);
		strcpy(s[i].sym, ch);
	}*/
	/*for (i = 0; i< n; i++)
	{
		printf("\n\tEnter probability for %s ---> ", s[i].sym);
		scanf("%f", &x);
		s[i].pro = x;
		total = total + s[i].pro;
		if (total>1)
		{
			printf("\t\tThis probability is not possible.Enter new probability");
			total = total - s[i].pro;
			i--;
		}
	}
	s[i].pro = 1 - total;*/
	for (j = 1; j <= n-1; j++)
	{
		for (i = 0; i< n-1; i++)
		{
			if ((s[i].pro)>(s[i + 1].pro))
			{
				temp.pro = s[i].pro;
				temp.sym= s[i].sym;
				s[i].pro = s[i + 1].pro;
				s[i].sym=s[i + 1].sym;
				s[i + 1].pro = temp.pro;
				s[i + 1].sym=temp.sym;
			}
		}
	}
	for (i = 0; i< n; i++)
		s[i].top = -1;

	shannon(0, n - 1, s);
	printf("---------------------------------------------------------------");
	printf("\n\n\n\tSymbol\tProbability\tCode");
	for (i = n - 1; i >= 0; i--)
	{
		printf("\n\t%c\t%f\t", s[i].sym, s[i].pro);
		for (j = 0; j <= s[i].top; j++)
			printf("%d", s[i].arr[j]);
	}
	printf("\n---------------------------------------------------------------");
	getch();
	
	fclose(f);
	//compressing(n);
	decompressing(n);

}