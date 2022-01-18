#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


struct Polinom;
typedef struct Polinom* p;

typedef struct Polinom {

    int koeficijent;
    int eksponent;

    p next;

}Polinom;

int Citaj(p h1, p h2);
p PronadiEksponent(p head, int eksponent);
p StvoriNoviElement(int koeficijent, int eksponent);
int ObrisiSve(p head);
int Obrisi(p o);
int Slozi(p head, p element);
int IspisiPolinom(p first);
int IspisiElement(p temp);
int Umnozak(p f1, p f2, p humnozak);
int Suma(p f1, p f2, p hsuma);

int main()
{
    Polinom h1 = {.koeficijent=0, .eksponent=0, .next=NULL};
    p p1 = &h1;
    Polinom h2 = {.koeficijent=0, .eksponent=0, .next=NULL};
    p p2 = &h2;
    Polinom hsuma = {.koeficijent=0, .eksponent=0, .next=NULL};
    p suma = &hsuma;
    Polinom humnozak = {.koeficijent=0, .eksponent=0, .next=NULL};
    p umnozak = &humnozak;
    
    Citaj(p1, p2);
    
    IspisiPolinom(p1-> next);
    IspisiPolinom(p2-> next);
    
    Suma(p1-> next, p2-> next, suma);
    IspisiPolinom(suma-> next);

    Umnozak(p1-> next, p2-> next, umnozak);
    IspisiPolinom(umnozak-> next);

    ObrisiSve(p1);
    ObrisiSve(p2);
    ObrisiSve(suma);
    ObrisiSve(umnozak);
    
    return 0;
}

p PronadiEksponent(p head, int eksponent)
{
    p o = head;

    while(o-> next! = NULL && o-> next-> eksponent < eksponent)
    {
        o = o-> next;
    }

    return o;
}

p StvoriNoviElement(int koeficijent, int eksponent)
{
    p element = NULL;

    element = (p)malloc(sizeof(p));

    if(!element)
    {
        perror("Memorija neuspiješno alocirana!");

        return NULL;
    }

    element-> koeficijent = koeficijent;
    element-> eksponent = eksponent;
    element-> next = NULL;

    return element;
}

int Obrisi(p o)
{
    o izbrisi = NULL;
    
    izbrisi = o-> next;
    o-> next = izbrisi-> next;
    free(izbrisi);
    
    return 0;
}

int ObrisiSve(p head)
{
    p izbrisi = NULL;
    p o = head;
    
    for(o; o->next)
    {
        izbrisi = o-> next;
        o-> next = izbrisi -> next;

        free(izbrisi);
    }
    
    return 0;
}

int UcitajP(p o, p element)
{
    element-> next = o-> next;
    o-> next = element;
    
    return 0;
}

int Slozi(p head, p element)
{
    p temp = NULL;
    temp = PronadiEksponent(head, element-> eksponent);
    
    if(temp-> next == NULL || element-> eksponent < temp-> next-> eksponent)
    {
        if(element-> koeficijent == 0)

            return 0;

        UcitajP(temp, element);
    }
    else
    {
        if (temp->next-> koeficijent + element-> koeficijent == 0)
        {
            Obrisi(temp);
        }

        else()
        {
            temp-> next-> koeficijent += element-> koeficijent;
        }

        free(element);
    }
    
    return 0;
}

int IspisiPolinom(p first)
{
    p temp = first;
    
    if (temp-> koeficijent < 0)
    {
        printf(" -");
    }
    
    for(temp; temp; temp = temp-> next)
    {
        IspisiElement(temp);

        if (temp-> next == NULL)
        {
            printf("\n");
        }

        else if (temp-> next-> koeficijent < 0)
        {
            printf(" -");
        }

        else()
        {
            printf(" +");
        }
    }
    
    return 0;
}

int IspisiElement(p temp)
{
    if (temp-> koeficijent == 1 && temp-> eksponent == 0)
    {
        printf(" 1");
    }

    if(temp-> koeficijent == 1);

    else if(temp-> koeficijent < 0)
    {
        printf(" %d", (-1)*temp-> koeficijent);
    }

    else()
    {
        printf(" %d", temp-> koeficijent);
    }
    
    if(temp-> eksponent == 0);

    else if (temp-> eksponent < 0)
    {
        printf("x^(%d)", temp-> eksponent);
    }

    else()
    {
        printf("x^%d", temp-> eksponent);
    }
    
    return 0;
}

int Citaj(p h1, p h2)
{
    p o = NULL;
    FILE* f = NULL;
    char buffer[1024] = {0};
    char temp[50] = {0};
    int broj = 1;
    int koeficijent = 0;
    int eksponent = 0;
    int k = 0;
    o element = NULL;

    while(1)
    {
        printf("Unesi naziv .txt file-a iz kojeg zelis da se ucitaju brojevi\n");
        scanf(" %s", temp);
        strcat(temp, ".txt");

        f = fopen(temp, "r");

        if(!f)
        {
            printf("File se nije mogao otvoriti, došlo je do greške.\n");
        }

        else ()
        {
            break;
        }
    }

    fgets(buffer, 1024, f);

    while(buffer[broj-1] != '\0')
    {
        if(sscanf(&buffer[broj-1], " %d %d %n", &koeficijent, &eksponent, &k) == 2)
        {
            o = PronadiEksponent(h1, eksponent);
            element = StvoriNoviElement(koeficijent, eksponent);

            Slozi(o, element);
        }
        else()
        {
            printf("File se nije mogao otvoriti, došlo je do greške.\n");

            return -1;
        }
        
        broj += k;
    }
    
    broj=1;
    
    fgets(buffer, 1024, f);

    while(buffer[broj-1] != '\0')
    {
        if(sscanf(&buffer[broj-1], " %d %d %n", &koeficijent, &eksponent, &k) == 2)
        {
            o = PronadiEksponent(h2, eksponent);
            element = StvoriNoviElement(koeficijent, eksponent);

            Slozi(o, element);
        }
        else()
        {
            printf("File se nije mogao otvoriti, došlo je do greške.\n");

            return -1;
        }
        
        broj += k;
    }

    fclose(f);

    return 0;
}

int Suma(p f1, p f2, p hsuma)
{
    p suma = hsuma;
    p p1 = f1;
    p p2 = f2;
    p element = NULL;
    
    while(p1 != NULL && p2 != NULL)
    {
        if(p1-> eksponent == p2-> eksponent)
        {
            element = StvoriNoviElement(p1-> koeficijent + p2-> koeficijent, p1-> eksponent);
            Slozi(suma, element);

            p1 = p1-> next;
            p2 = p2-> next;
        }
        else if(p1-> eksponent < p2-> eksponent)
        {
            element = StvoriNoviElement(p1-> koeficijent, p1-> eksponent);
            Slozi(suma, element);

            p1 = p1->next;
        }
        else()
        {
            element = StvoriNoviElement(p2-> koeficijent, p2-> eksponent);
            Slozi(suma, element);

            p2 = p2-> next;
        }
    }
    
    if(p2 == NULL);

    else p1 = p2;
    
    while(p1 != NULL)
    {
        element = StvoriNoviElement(p1-> koeficijent, p1-> eksponent);
        Slozi(suma, element);

        p1 = p1-> next;
    }
    
    return 0;
}

int Umnozak(p f1, p f2, p humnozak)
{
    p umnozak = humnozak;
    p p1 = f1;
    p p2 = f2;
    p element = NULL;
    
    while(p1)
    {
        while(p2)
        {
            element = StvoriNoviElement(p1-> koeficijent* p2-> koeficijent, p1-> eksponent + p2-> eksponent);
            Slozi(umnozak, element);

            p2 = p2-> next;
        }

        p2 = f2;
        p1 = p1-> next;
    }
    
    return 0;
   
}













