#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128

struct Dir;
typedef struct Dir* Pozicija;

typedef struct Dir
{
    char ime[MAX];
    Pozicija brat;
    Pozicija dijete;

}Dir;


Pozicija Unesi(Pozicija k, Pozicija noviDir);
Pozicija StvoriDir(char ime[MAX]);
int IspisiSvakiDir(Pozicija p, int i);
int PronadiRoditelja(Pozicija* k, Pozicija roditelj, Pozicija p, char ime[MAX]);
int PretraziPoImenu(Pozicija* k, Pozicija p, char ime[MAX]);
int Izbrisi(Pozicija p);

int main()
{
    Dir Root = { .ime = "..", .brat = NULL, .dijete = NULL };
    Pozicija pRoot = &Root;

    int operacija = 0;
    Pozicija k = pRoot;

    char ime[MAX];


    while (1)
    {
        printf("\n1 - md\n"
            "2 - cd dir\n"
            "3 - cd..\n"
            "4 - dir\n"
            "5 - exit\n");
        scanf_s(" %d", &operacija);

        switch (operacija)
        {
        case 1:
        {
            printf("Unesi ime direktorija kojeg zelis stvorit:\n");
            scanf_s(" %s", ime);
            k->dijete = Unesi(k->dijete, StvoriDir(ime));
            break;
        }
        case 2:
        {
            Pozicija p = pRoot;
            printf("Unesi ime direktorija u kojeg zelis uc:\n");
            scanf_s(" %s", ime);
            PretraziPoImenu(&k, p, ime);
            break;
        }
        case 3:
        {
            Pozicija roditelj = pRoot;
            Pozicija p = pRoot;
            PronadiRoditelja(&k, roditelj, p, ime);
            break;
        }
        case 4:
        {
            IspisiSvakiDir(pRoot, 0);
            break;
        }
        case 5:
        {
            Izbrisi(pRoot->dijete);
            return 0;
        }
        default:
        {
            printf("Krivi unos.\n");
            break;
        }
        }
    }

    return 0;
}

Pozicija Unesi(Pozicija k, Pozicija noviDir)
{
    if (k == NULL)
    {
        return noviDir;
    }
    else if (strcmp(k->ime, noviDir->ime) > 0)
    {
        noviDir->brat = k;
        return noviDir;
    }
    else if (strcmp(k->ime, noviDir->ime) < 0)
    {
        k->brat = Unesi(k->brat, noviDir);
        return k;
    }
    else
    {
        printf("Vec postoji datoteka ili direktorij s takvim imenom.\n");
        free(noviDir);
        return k;
    }
}

Pozicija StvoriDir(char ime[MAX])
{
    Pozicija noviDir = NULL;

    noviDir = (Pozicija)malloc(sizeof(Dir));
    if (!noviDir)
    {
        printf("Memorija nesupjesno alocirana.\n");
        return NULL;
    }

    strcpy(noviDir->ime, ime);
    noviDir->dijete = NULL;
    noviDir->brat = NULL;

    return noviDir;
}

int IspisiSvakiDir(Pozicija p, int i)
{
    int j = 0;

    printf("\n");

    for (j = 0; j < i; j++)
    {
        printf("  ");
    }
    printf(" %s", p->ime);

    if (p->dijete)
    {
        IspisiSvakiDir(p->dijete, i + 1);
    }
    if (p->brat)
    {
        IspisiSvakiDir(p->brat, i);
    }

    return 0;
}

int PronadiRoditelja(Pozicija* k, Pozicija roditelj, Pozicija p, char ime[MAX])
{
    if (strcmp(p->ime, ime) == 0)
    {
        *k = roditelj;
    }
    if (p->dijete)
    {
        PronadiRoditelja(k, p, p->dijete, ime);
    }
    if (p->brat)
    {
        PronadiRoditelja(k, roditelj, p->brat, ime);
    }

    return 0;
}

int PretraziPoImenu(Pozicija* k, Pozicija p, char ime[MAX])
{
    if (strcmp(p->ime, ime) == 0)
    {
        *k = p;
    }
    if (p->dijete)
    {
        PretraziPoImenu(k, p->dijete, ime);
    }
    if (p->brat)
    {
        PretraziPoImenu(k, p->brat, ime);
    }

    return 0;
}

int Izbrisi(Pozicija p)
{
    if (!p)
    {
        return 0;
    }
    else if (!p->brat && !p->dijete)
    {
        free(p);
        return 0;
    }
    else
    {
        if (p->dijete)
        {
            Izbrisi(p->dijete);
            p->dijete = NULL;
        }
        if (p->brat)
        {
            Izbrisi(p->brat);
            p->brat = NULL;
        }

        free(p);
    }
    return 0;
}
