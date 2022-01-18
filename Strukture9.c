#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

struct BinarnoStablo;
typedef struct BinarnoStablo* Pozicija;

typedef struct BinarnoStablo
{
    int N;

    Pozicija L;
    Pozicija D;

}BinarnoStablo;

struct stog;
typedef struct stog* Pointer;

typedef struct stog
{
    int n;
    Pointer next;

}stog;

Pozicija noviElement(int n);
Pozicija Insert(Pozicija p, Pozicija noviEl);
int Replace(Pozicija p);
Pozicija novoStablo(Pozicija pRoot);
int IzbrisiSve(Pozicija p);
int InorderStog(Pozicija p, Pointer h);
int IspisiInorder(Pozicija p);
int IspisiListu(char* imeDat, Pointer prvi);
Pointer noviElementStog(int n);
int IzbrisiStog(Pointer head);
int UnesiNaKraj(Pointer p, Pointer noviEl);
Pointer PoronadiZadnjeg(Pointer head);
int DodajNaKraj(Pointer head, int n);

int main()
{
    Pozicija pRoot = NULL;

    pRoot = novoStablo(pRoot);

    int operacija = 0;

    while (1)
    {
        printf("\n1 -> Dodaj novi element.\n"
                 "2 -> Ispisi inorder\n"
                 "3 -> Zamijeni sve elemente sa sumom njihovih grana.\n"
                 "4 -> Ispisi inorder u datoteku\n"
                 "5 -> Stvori novo stablo.\n"
                 "6 -> Exit\n");

        scanf_s(" %d", &operacija);

        switch (operacija)
        {
        case 1:
        {
            int n;

            printf("\n");
            printf("Unesi element:\n");
            scanf_s(" %d", &n);

            pRoot = Insert(pRoot, noviElement(n));
            operacija = 0;

            break;
        }
        case 2:
        {
            printf("\n");
            IspisiInorder(pRoot);
            printf("\n");

            operacija = 0;

            break;
        }
        case 3:
        {
            printf("\n");
            Replace(pRoot);
            printf("\n");

            operacija = 0;

            break;
        }
        case 4:
        {
            stog head = { .n = 0, .next = NULL };
            Pointer h = &head;
            char str[20] = "0";

            printf("Unesi ime .txt datoteke: \n");
            scanf_s(" %s", str);
            strcat(str, ".txt");
            InorderStog(pRoot, h);
            IspisiListu(str, h->next);
            printf("\n");

            operacija = 0;

            break;
        }
        case 5:
        {
            printf("\n");
            IzbrisiSve(pRoot);
            pRoot = NULL;
            pRoot = novoStablo(pRoot);
            printf("\n");

            operacija = 0;

            break;
        }
        case 6:
        {
            IzbrisiSve(pRoot);
            return 0;
        }
        default:
        {
            printf("\n");
            printf("Krivi unos.\n");

            operacija = 0;

            break;
        }
        }
    }

    return 0;
}

Pozicija noviElement(int n)
{
    Pozicija noviEl = NULL;

    noviEl = (Pozicija)malloc(sizeof(BinarnoStablo));

    if (!noviEl)
    {
        printf("Memorija neuspjesno alocirana.\n");
        return NULL;
    }

    noviEl->N = n;
    noviEl->D = NULL;
    noviEl->L = NULL;

    return noviEl;
}

Pozicija Insert(Pozicija p, Pozicija noviEl)
{

    if (p == NULL)
    {
        return noviEl;
    }

    else if (p->N < noviEl->N)
    {
        p->L = Insert(p->L, noviEl);
    }

    else
    {
        p->D = Insert(p->D, noviEl);
    }

    return p;
}

int Replace(Pozicija p)
{
    int temp = 0;

    if (p == NULL)
    {
        return 0;
    }
    else
    {
        temp = p->N;
        p->N = Replace(p->D) + Replace(p->L);

        return p->N + temp;
    }
}

Pozicija novoStablo(Pozicija pRoot)
{
    int i = 0;

    Pozicija temp = NULL;

    srand(time(0));

    for (i = 0; i < 10; i++)
    {
        temp = noviElement(rand() % 79 + 11);

        if (!temp)
        {
            return NULL;
        }

        pRoot = Insert(pRoot, temp);
    }

    return pRoot;
}

int IzbrisiSve(Pozicija p)
{
    if (!p)
    {
        return 0;

    }

    if (!p->L && !p->D)
    {
        free(p);
    }

    else
    {
        if (p->L)
        {
            IzbrisiSve(p->L);
        }
        if (p->D)
        {
            IzbrisiSve(p->D);
        }

        free(p);
    }

    return 0;
}

int InorderStog(Pozicija p, Pointer h)
{
    if (!p)
    {
        return 0;
    }

    InorderStog(p->L, h);
    DodajNaKraj(h, p->N);
    InorderStog(p->D, h);

    return 0;
}

int IspisiInorder(Pozicija p)
{
    if (!p)
    {
        return 0;

    }

    IspisiInorder(p->L);
    printf("%d ", p->N);
    IspisiInorder(p->D);

    return 0;
}

int IspisiListu(char* imeDat, Pointer prvi)
{
    Pointer temp = prvi;
    FILE* f = NULL;

    f = fopen(imeDat, "w");

    if (f == NULL)
    {
        printf("Neuspjesno otvaranje datoteke.");

        return -1;
    }

    for (temp; temp; temp = temp->next)
    {
        fprintf(f, "%d ", temp->n);
    }

    fclose(f);

    return 0;
}

Pointer noviElementStog(int n)
{
    Pointer noviEl = NULL;

    noviEl = (Pointer)malloc(sizeof(stog));

    if (!noviEl)
    {
        perror("Memorija neuspjesno alocirana.\n");

        return NULL;
    }

    noviEl->n = n;
    noviEl->next = NULL;

    return noviEl;
}

int IzbrisiStog(Pointer head)
{
    Pointer temp = NULL;

    while (head->next != NULL)
    {
        temp = head->next;
        head->next = temp->next;

        free(temp);
    }

    return 0;
}

int UnesiNaKraj(Pointer p, Pointer noviEl)
{
    noviEl->next = p->next;
    p->next = noviEl;

    return 0;
}

int DodajNaKraj(Pointer head, int n)
{
    Pointer noviEl = NULL;

    noviEl = noviElementStog(n);

    if (!noviEl)
    {
        return -1;
    }

    UnesiNaKraj(PoronadiZadnjeg(head), noviEl);

    return 0;
}

Pointer PoronadiZadnjeg(Pointer head)
{
    Pointer zadnji = head;

    while (zadnji->next)
    {
        zadnji = zadnji->next;
    }

    return zadnji;
}