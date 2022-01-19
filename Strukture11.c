#pragma warning(disable: 4996)
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
Pointer CitajDrzaveIzDatoteke(char* imeDat, Pointer head);
int IspisiGradove(Pozicija p);
int IspisiSve(Pointer first);
Pointer PronadiDrzavu(char* ime, Pointer first);
int IspisiVeciGrad(Pozicija p, int n);
int IspisiVecuDrzavu(Pointer drzava, int n);
int HashPozicija(char* drzava);
int IzbrisiSve(Pointer first);

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

        scanf("%d", &operacija);

        switch (operacija)
        {

        case 1:
        {
            char string[20] = "0";

            printf("Unesi ime .txt datoteke iz koje zelis da se cita:\n");

            scanf("%s", string);
            if (strlen(string) > 4 && strcmp(&string[strlen(string) - 4], ".txt"))
            {
                strcat(string, ".txt");
            }

            pHead = CitajDrzaveIzDatoteke(string, pHead);

            if (!pHead)
            {
                return -1;
            }

            operacija = 0;

            break;
        }
        case 2:
        {
            int i = 0;

            for (i = 0; i < 11; i++)
            {
                IspisiSve(&pHead[i]);
            }

            operacija = 0;

            break;
        }
        case 3:
        {
            char str[20] = "0";
            int n = 0;
            int i = 0;
            int t = 0;

            printf("Unesi ime drzave i minimalni broj stanovnika:\n");

            scanf(" %s %d", str, &n);

            for (i = 0; i < 11; i++)
            {
                t += IspisiVecuDrzavu(PronadiDrzavu(str, &pHead[i]), n);
            }

            if (t == -11)
            {
                printf("Ne postoji takva drzava.");
            }

            operacija = 0;

            break;
        }

        case 4:
        {
            int i = 0;

            for (i = 0; i < 11; i++)
            {
                IzbrisiSve(pHead[i].next);
                pHead[i].next = NULL;
            }

            operacija = 0;

            break;
        }
        case 5:
        {
            int i = 0;

            for (i = 0; i < 11; i++)
            {
                IzbrisiSve(pHead[i].next);
                pHead[i].next = NULL;
            }
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
        {
            temp = temp->next;
        }

        else
        {
            break;
        }

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

lista* CitajDrzaveIzDatoteke(char* imeDat, Pointer head)
{
    Pointer temp = NULL;
    Pointer tempp = NULL;
    FILE* f = NULL;
    char buffer[MAX_SIZE] = { 0 };
    char ime[128] = { 0 };
    char f_ime[128] = { 0 };
    lista Dat[11];
    int i = 0;

    f = fopen(imeDat, "r");
    if (f == NULL)
    {
        printf("Neuspjesno otvaranje datoteke.");
        return NULL;
    }

    while (!feof(f))
    {
        fgets(buffer, MAX_SIZE, f);
        if (sscanf(buffer, " %s %s", ime, f_ime) == 2)
        {
            i = HashPozicija(ime);
            UnesiDrzavu(&head[i], StvoriNovuDrzavu(ime));
            CitajGradoveIzDatoteke(f_ime, head[i].next);
        }
    }

    fclose(f);

    return head;
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
        if (strcmp(temp->ime, "0") != 0)
        {
            printf("%s:\n", temp->ime);
            IspisiGradove(temp->root);
        }
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

int HashPozicija(char* drzava)
{
    int i = 0;
    int key = 0;

    for (i = 0; i < strlen(drzava) && i < 5; i++)
        key += (int)drzava[i];

    key = key % 11;

    return key;
}

int IzbrisiSve(Pointer first)
{
    if (!first)
    {
        return 0;
    }

    IzbrisiSve(first->next);
    free(first);

    return 0;
}

