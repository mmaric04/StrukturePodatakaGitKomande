#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


struct Stog;
typedef struct Stog* p;

typedef struct Stog {

	double br;
	p next;

}Stog;

int ImeDat(char*);
int CitanjeDat(p, char*);
p Stvori(double);
int Pop(p, double*);
int Push(p, p);
int Operacije(char*, p);
int Ispis(p);

int main()
{
	Stog head = { .br = 0, .next = NULL };
	char dat[128] = { 0 };

	ImeDat(&dat);
	CitanjeDat(&head, &dat);
	Ispis(head.next);

	return 0;
}

int ImeDat(char* dat)
{
	printf("Upisite ime datoteke: ");
	scanf(" %s", dat);

	return 0;
}

int CitanjeDat(p head, char* dat)
{
	FILE* f = NULL;
	p q = head;

	char buffer[1024] = { 0 };
	char* q_buffer;
	int status = 0;

	int n = 0;
	double br = 0;
	char operacija[2] = { 0 };

	q_buffer = &buffer;
	f = fopen(dat, "r");

	if (!f)
	{
		perror("Datoteka neuspjesno pronadena!");

		return -1;
	}

	fgets(buffer, 1024, f);

	if (strlen(q_buffer) == 0) 
	{
		printf("Datoteka je prazna!");

		return -1;
	}

	while (strlen(q_buffer) != 0) 
	{
		if ((status = sscanf(q_buffer, "%lf %n", &br, &n)) == 1)
		{
			q element = Stvori(br);
			Push(q, element);
		}
		else if ((status = sscanf(q_buffer, " %s %n", operacija, &n)) == 1) 
		{
			if (Operacije(&operacija, q) == -1)
				return -1;
		}

		q_buffer += n;
	}

	fclose(f);

	return 0;
}

p Stvori(double br)
{
	p element = (p)malloc(sizeof(Stog));

	if (!element) {
		printf("Neuspjesno alocirana memorija!");
		return -1;
	}

	element->br = br;
	element->next = NULL;

	return element;
}

int Pop(p head, double* br)
{
	p temp = NULL;

	if (head->next == NULL) 
	{
		printf("Neispravan postfix u datoteci.\n");

		return -1;
	}

	*br = head->next->br;
	temp = head->next;
	head->next = temp->next;

	free(temp);

	return 0;
}

int Push(p head, p element)
{
	element->next = head->next;
	head->next = element;

	return 0;
}

int Operacije(char* operand, p p)
{
	p rezultat = (p)malloc(sizeof(Stog));
	double br1 = 0;
	double br2 = 0;

	if (Pop(p, &br1) == -1)
		return -1;
	if (Pop(p, &br2) == -1)
		return -1;

	switch (*operand)
	{
	case '+':

		rezultat = Stvori(br2 + br1);
		Push(p, rezultat);
		break;

	case '*':

		rezultat = Stvori(br2 * br1);
		Push(p, rezultat);
		break;

	case '-':
		rezultat = Stvori(br2 - br1);
		break;

	case '/':
		if (br2 == 0)
		{
			printf("Nije moguce dijeliti s nulom!");
			return -1;
		}
		rezultat = Stvori(br2 / br1);
   
	default:

		break;
	}
}

int Ispis(p q)
{
	while (q != NULL)
	{
		printf("%lf ", q->br);

		q = q->next;
	}

	printf("\n");

	return 0;
}















