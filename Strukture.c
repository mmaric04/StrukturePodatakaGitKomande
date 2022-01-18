#pragma warning (disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct invertar
{
	char ime[16];
	int kolicina;
	int cijena;
	int godina;

}invertar;

int zaduzenje(invertar*, int);

int main()
{
	int a;
	invertar* p;
	FILE* f;

	
	f = fopen("invertar.txt", "r");
	scanf(f, "%d", &a);

	return 0;
}

