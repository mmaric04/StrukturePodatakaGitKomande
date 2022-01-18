#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 128

struct BinarnoStablo; 
typedef struct BinarnoStablo* Pozicija; 

typedef struct BinarnoStablo 
{
    int N;
    Pozicija L;
    Pozicija D; 

}BinarnoStablo;

Pozicija Unesi(Pozicija p, Pozicija noviEl); 
Pozicija StvoriNoviElement(int n); 
int Preorder(Pozicija p); 
int Inorder(Pozicija p); 
int Postorder(Pozicija p); 
int LevelOrder(Pozicija p); 
int IspisiRazinu(Pozicija p, int l, int k);  
int NajvecaRazina(Pozicija p, int l); 
int Pronadi(Pozicija p, int n); 
Pozicija Izbrisi(Pozicija p, int n); 
int IzbrisiSve(Pozicija p); 

int main()
{
    Pozicija pRoot = NULL;

    int operacija = 0;

    while (1)
    {
        printf("\n1 -> Dodaj novi element u stablo\n"
                 "2 -> Ispisi inorder\n"
                 "3 -> Ispisi preorder\n"
                 "4 -> Ispisi postorder\n"
                 "5 -> Ispisi level order\n"
                 "6 -> Pronadi element\n"
                 "7 -> Izbrisi element\n"
                 "8 -> Exit\n");

        scanf_s(" %d", &operacija);

        switch (operacija)
        {

        case 1:
        {
            int n;

            printf("\n");
            printf("Unesi element:\n");
            scanf_s(" %d", &n);
            pRoot = Unesi(pRoot, StvoriNoviElement(n));

            operacija = 0;

            break;
        }

        case 2:
        {
            printf("\n");
            Inorder(pRoot);
            printf("\n");
            operacija = 0;

            break;
        }

        case 3:
        {
            printf("\n");
            Preorder(pRoot);
            printf("\n");
            operacija = 0;

            break;
        }

        case 4:
        {
            printf("\n");
            Postorder(pRoot);
            printf("\n");
            operacija = 0;

            break;
        }

        case 5:
        {
            printf("\n");
            LevelOrder(pRoot);
            printf("\n");
            operacija = 0;

            break;
        }

        case 6:
        {
            int n = 0;
            printf("\n");
            printf("Unesi element koji zelis pronaci:\n");
            scanf_s(" %d", &n);
            if (Pronadi(pRoot, n))
            {
                printf("Element se nalazi u stablu.\n", n);
            }
            else
            {
                printf("Element se ne nalazi u stablu\n", n);
            }

            operacija = 0;

            break;
        }

        case 7:
        {
            int n = 0;
            printf("\n");
            printf("Unesi broj kojeg zelis izbrisati:\n");
            scanf_s(" %d", &n);
            if (!Pronadi(pRoot, n));
            else
            {
                Izbrisi(pRoot, n);
            }
            operacija = 0;

            break;
        }

        case 8:
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

Pozicija Unesi(Pozicija p, Pozicija noviEl)
{
    if (p == NULL)
    {
        return noviEl;
    }

    else if (p->N < noviEl->N)
    {
        p->D = Unesi(p->D, noviEl);
    }

    else if (p->N > noviEl->N)
    {
        p->L = Unesi(p->L, noviEl);
    }

    else
    {
        free(noviEl);

        return p;
    }

    return p;
}

Pozicija StvoriNoviElement(int n)
{
    Pozicija novieEl = NULL;

    novieEl = (Pozicija)malloc(sizeof(BinarnoStablo));

    if (!novieEl)
    {
        printf("Memorija neuspjesno alocirana.\n");
        return NULL;
    }

    novieEl->N = n;
    novieEl->D = NULL;
    novieEl->L = NULL;

    return novieEl;
}

int Preorder(Pozicija p)
{
    if (!p || p->N == INT_MAX)
    {
        return 0;
    }

    printf("%d ", p->N);

    Preorder(p->L);
    Preorder(p->D);

    return 0;
}

int Inorder(Pozicija p)
{
    if (!p || p->N == INT_MAX)
    {
        return 0;
    }

    Inorder(p->L);
    printf("%d ", p->N);
    Inorder(p->D);

    return 0;
}

int Postorder(Pozicija p)
{
    if (!p || p->N == INT_MAX)
    {
        return 0;
    }

    Postorder(p->L);
    Postorder(p->D);

    printf("%d ", p->N);

    return 0;
}

int LevelOrder(Pozicija p)
{
    int l = NajvecaRazina(p, -1);
    int i = 0;

    for (i = 0; i <= l; i++)
    {
        printf("\n");
        IspisiRazinu(p, i, 0);
    }

    return 0;
}

int IspisiRazinu(Pozicija p, int l, int k)
{
    if (!p || p->N == INT_MAX)
    {
        return 0;
    }

    if (l == k)
    {
        printf("%d ", p->N);
    }

    IspisiRazinu(p->L, l, k + 1);
    IspisiRazinu(p->D, l, k + 1);

    return 0;
}

int NajvecaRazina(Pozicija p, int l)
{
    int k = 0;
    l++;

    if (p->L)
    {
        l = NajvecaRazina(p->L, l);
    }

    if (p->D)
    {
        k = NajvecaRazina(p->D, l);

        if (k > l)
        {
            l = k;
        }
    }

    return l;
}


int Pronadi(Pozicija p, int n)
{
    if (!p)
    {
        return 0;
    }

    if (p->N == n)
    {
        return n;
    }

    else if (p->N < n)
    {      
        return Pronadi(p->D, n);
    }

    else if (p->N > n)
    {
        return Pronadi(p->L, n);
    }

    else 
    {
        return 0;
    }
}

Pozicija Izbrisi(Pozicija p, int n)
{
    Pozicija temp = NULL;

    if (!p)
    {
        return NULL;
    }

    if (p->N == n)
    {
        if (p->L)
        {
            temp = p->L;

            while (temp->D)
            {
                temp = temp->D;
            }

            temp->L = p->L;
            temp->D = p->D;
        }

        else if (p->D)
        {
            temp = p->D;

            while (temp->L)
            {
                temp = temp->L;
            }

            temp->L = p->L;
            temp->D = p->D;
        }

        p->D = NULL;
        p->L = NULL;

        free(p);

        return temp;
    }

    else if (p->N < n)
    {
        p->D = Izbrisi(p->D, n);
    }

    else
    {
        p->L = Izbrisi(p->L, n);
    }

    return p;
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

