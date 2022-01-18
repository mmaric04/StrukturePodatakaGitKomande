#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (1024)

struct stablo; 
typedef struct stablo* Pozicija;

typedef struct stablo 
{
    Pozicija L;
    Pozicija D; 
    char ime[128]; 
    int pop;

}stablo;

struct lista;
typedef struct lista* Pointer;

typedef struct lista
{
    Pointer next;
    char ime[128]; 
    Pozicija root;

}lista;

Pozicija StvoriNoviGrad(char* ime, int pop);
Pointer StvoriNovuDrzavu(char* ime);
Pozicija UnesiGrad(Pozicija p, Pozicija el);
int UnesiDrzavu(Pointer head, Pointer el);
Pozicija CitajGradoveIzDatoteke(char* imeDat, Pointer p);
int CitajDrzaveIzDatoteke(char* imeDat, Pointer p);
int IspisiGradove(Pozicija p);
int IspisiSve(Pointer first);
Pointer PronadiDrzavu(char* ime, Pointer first);
int IspisiVeciGrad(Pozicija p, int n);
int IspisiVecuDrzavu(Pointer drzava, int n);


int main()
{
    lista head = { .next = NULL, .ime = {0}, .root = NULL };
    Pointer pHead = &head;

    int operacija = 0;

    while (1)
    {
        printf("\n1 -> Citaj iz datoteke\n"
                 "2 -> Ispisi sve\n"
                 "3 -> Ispisi gradove u drzavi s populacijom vecom od n\n"
                 "4 -> Izbrisi sve\n"
                 "5 -> Izadi\n");

        scanf_s(" %d", &operacija);

        switch (operacija)
        {
        case 1:
        {
            char string[20] = "0";
            printf("Unesi ime .txt datoteke iz koje zelis da se cita:\n");
            scanf_s(" %s", string);
            if (strlen(string) > 4 && strcmp(&string[strlen(string) - 4], ".txt"))
                strcat(string, ".txt");
            CitajDrzaveIzDatoteke(string, pHead);
            operacija = 0;
            break;
        }
        case 2:
        {
            IspisiSve(pHead->next);
            operacija = 0;
            break;
        }
        case 3:
        {
            char str[20] = "0";
            int n = 0;
            printf("Unesi ime drzave i broj ljudi n:\n");
            scanf_s(" %s %d", str, &n);
            IspisiVecuDrzavu(PronadiDrzavu(str, pHead->next), n);
            operacija = 0;
            break;
        }
        case 4:
        {
            pHead->next = NULL;
            break;
        }
        case 5:
        {
            pHead->next = NULL;
            return 0;
        }
        default:
        {
            printf("\n");
            printf("Niste unijeli jedan od zadanih brojeva. Pokusajte ponovo.\n");
            operacija = 0;
            break;
        }
        }
    }

    return -1;

}

Pozicija StvoriNoviGrad(char* ime, int pop)
{
    Pozicija noviGrad = NULL;

    noviGrad = (Pozicija)malloc(sizeof(stablo));

    if (!noviGrad)
    {
        printf("Memorija neuspjesno alocirana.\n");
        return NULL;
    }

    strcpy(noviGrad->ime, ime);

    noviGrad->pop = pop;
    noviGrad->D = NULL;
    noviGrad->L = NULL;

    return noviGrad;
}

Pointer StvoriNovuDrzavu(char* ime)
{
    Pointer novaDrzava = NULL;

    novaDrzava = (Pointer)malloc(sizeof(lista));

    if (!novaDrzava)
    {
        printf("Memorija neuspjesno alocirana.\n");
        return NULL;
    }

    strcpy(novaDrzava->ime, ime);

    novaDrzava->next = NULL;
    novaDrzava->root = NULL;

    return novaDrzava;
}

Pozicija UnesiGrad(Pozicija p, Pozicija el)
{
    if (p == NULL)
    {
        return el;
    }
    else if (p->pop > el->pop)
    {
        p->L = UnesiGrad(p->L, el);
    }
    else if (p->pop < el->pop)
    {
        p->D = UnesiGrad(p->D, el);
    }
    else if (strcmp(p->ime, el->ime) > 0)
    {
        p->L = UnesiGrad(p->L, el);
    }
    else if (strcmp(p->ime, el->ime) < 0)
    {
        p->D = UnesiGrad(p->D, el);
    }
    else
    {
        free(el);
    }
    return p;
}

int UnesiDrzavu(Pointer head, Pointer el)
{
    Pointer temp = NULL;

    temp = head;
    while (1)
    {
        if (temp->next != NULL && strcmp(temp->next->ime, el->ime) < 0)
            temp = temp->next;
        else
            break;
    }


    if (temp->next == NULL)
    {
        temp->next = el;
    }
    else if (strcmp(el->ime, temp->next->ime) == 0)
    {
        free(el);
        return -1;
    }
    else
    {
        el->next = temp->next;
        temp->next = el;
    }

    return 0;
}

Pozicija CitajGradoveIzDatoteke(char* imeDat, Pointer p)
{
    FILE* f = NULL;
    char buffer[MAX_SIZE] = { 0 };
    char ime[128] = { 0 };
    int pop = 0;


    f = fopen(imeDat, "r");
    if (f == NULL)
    {
        printf("Neuspjesno otvaranje datoteke.");
        return NULL;
    }

    while (!feof(f))
    {
        fgets(buffer, MAX_SIZE, f);
        if (sscanf(buffer, " %s %d", ime, &pop) == 2)
        {
            Pozicija noviGrad = NULL;

            noviGrad = StvoriNoviGrad(ime, pop);
            p->root = UnesiGrad(p->root, noviGrad);
        }
    }

    fclose(f);

    return p->root;
}


int CitajDrzaveIzDatoteke(char* imeDat, Pointer p)
{
    Pointer temp = NULL;
    FILE* f = NULL;
    char buffer[MAX_SIZE] = { 0 };
    char ime[128] = { 0 };
    char f_ime[128] = { 0 };
    lista dat = { .next = NULL, .ime = {0}, .root = NULL };
    Pointer pDat = &dat;

    f = fopen(imeDat, "r");
    if (f == NULL)
    {
        printf("Neuspjesno otvaranje datoteke.");
        return -1;
    }

    while (!feof(f))
    {
        fgets(buffer, MAX_SIZE, f);

        if (sscanf(buffer, " %s %s", ime, f_ime) == 2)
        {
            UnesiDrzavu(pDat, StvoriNovuDrzavu(f_ime));
            UnesiDrzavu(p, StvoriNovuDrzavu(ime));
        }
    }

    fclose(f);

    temp = p->next;
    pDat = pDat->next;
    while (pDat)
    {
        CitajGradoveIzDatoteke(pDat->ime, temp);
        pDat = pDat->next;
        temp = temp->next;
    }

 

    return 0;
}


int IspisiGradove(Pozicija p)
{
    if (!p)
    {
        return 0;
    }

    IspisiGradove(p->L);
    printf("\t%-12s - %d\n", p->ime, p->pop);
    IspisiGradove(p->D);

    return 0;
}

int IspisiSve(Pointer first)
{
    Pointer temp = first;

    while (temp)
    {
        printf("%s:\n", temp->ime);
        IspisiGradove(temp->root);
        temp = temp->next;
    }
    return 0;
}

Pointer PronadiDrzavu(char* ime, Pointer first)
{
    Pointer temp = first;

    while (temp != NULL && strcmp(temp->ime, ime) != 0)
    {
        temp = temp->next;
    }
    return temp;
}


int IspisiVeciGrad(Pozicija p, int n)
{
    if (!p)
    {
        return 0;
    }

    IspisiVeciGrad(p->D, n);

    if (p->pop >= n)
    {
        printf("\t%-12s - %d\n", p->ime, p->pop);
        IspisiVeciGrad(p->L, n);
    }

    return 0;
}

int IspisiVecuDrzavu(Pointer drzava, int n)
{
    if (!drzava)
    {
        printf("Ne postoji takva drzava u listi.\n");
        return -1;
    }

    IspisiVeciGrad(drzava->root, n);

    return 0;
}
