//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#pragma warning (disable : 4996)
//
//#define MAX_SIZE (1024)
//
//struct Osoba;
//typedef struct Osoba* Pozicija;
//typedef struct Osoba
//{
//    char ime[MAX_SIZE];
//    char prezime[MAX_SIZE];
//    int godinaRodjenja;
//    Pozicija next;
//} Osoba;
//
//Pozicija NovaOsoba(char* ime, char* prezime, int godinaRodjenja)
//{
//    Pozicija osoba = NULL;
//    osoba = (Pozicija)malloc(sizeof(Osoba));
//    if (osoba == NULL)
//    {
//        perror("Greška pri stvaranju osobe.\n");
//        return NULL;
//    }
//    strcpy(osoba->ime, ime);
//    strcpy(osoba->prezime, prezime);
//    osoba->godinaRodjenja = godinaRodjenja;
//    osoba->next = NULL;
//    return osoba;
//}
//
//int UnosSljedeci(Pozicija p, Pozicija osoba)
//{
//    osoba->next = p->next;
//    p->next = osoba;
//    return 0;
//}
//
//int UnosP(Pozicija head, char* ime, char* prezime, int godinaRodjenja)
//{
//    Pozicija osoba = NULL;
//    osoba = NovaOsoba(ime, prezime, godinaRodjenja);
//    if (osoba == NULL)
//    {
//        return -1;
//    }
//    UnosSljedeci(head, osoba);
//    return 0;
//}
//
//int UnosK(Pozicija head, char* ime, char* prezime, int godinaRodjenja)
//{
//    Pozicija osoba = NULL;
//    Pozicija last = NULL;
//    osoba = NovaOsoba(ime, prezime, godinaRodjenja);
//    if (osoba == NULL) 
//    {
//        return -1;
//    }
//    last = head;
//    while (last->next)
//    {
//        last = last->next;
//    }
//    UnosSljedeci(last, osoba);
//    return 0;
//}
//
//int Ispisi(Pozicija first)
//{
//    Pozicija temp = first;
//    printf("TRENUTNA LISTA:\n");
//    if (temp == NULL)
//    {
//        printf("Nema unosa.\n");
//        return -1;
//    }
//    for (temp; temp; temp = temp->next) 
//    {
//        printf("Ime: %s\nPrezime: %s\nGodina rodjenja: %d\n\n", temp->ime, temp->prezime, temp->godinaRodjenja);
//    }
//    return 0;
//}
//
//Pozicija PronadjiPrezime(char* prezime, Pozicija first)
//{
//    Pozicija temp = first;
//    for (temp; temp; temp = temp->next)
//    {
//        if (strcmp(temp->prezime, prezime) == 0)
//        {
//            return temp;
//        }
//    }
//    return temp;
//}
//
//int Obrisi(char* prezime, Pozicija head)
//{
//    Pozicija temp = head;
//    Pozicija toObrisi = NULL;
//    for (temp; temp->next; temp = temp->next) 
//    {
//        if (strcmp(temp->next->prezime, prezime) == 0)
//        {
//            toObrisi = temp->next;
//            temp->next = toObrisi->next;
//            printf("%s %s (%d) je uspjesno obrisan sa liste!\n\n", toObrisi->ime, toObrisi->prezime, toObrisi->godinaRodjenja);
//            free(toObrisi);
//            return 0;
//        }
//    }
//    return -1;
//}
//
//int DodajNakon(Pozicija head, char* ime, char* prezime, int godinaRodjenja, char* after)
//{
//    Pozicija temp = NULL;
//    Pozicija osoba = NULL;
//    temp = PronadjiPrezime(after, head->next);
//    if (!temp) 
//    {
//        return -1;
//    }
//    osoba = NovaOsoba(ime, prezime, godinaRodjenja);
//    if (!osoba)
//    {
//        return -1;
//    }
//    UnosSljedeci(temp, osoba);
//    return 0;
//}
//
//int DodajPrije(Pozicija head, char* ime, char* prezime, int godinaRodjenja, char* before)
//{
//    Pozicija temp = NULL;
//    Pozicija osoba = NULL;
//    temp = PronadjiPrezime(before, head);
//    if (temp == NULL) 
//    {
//        return -1;
//    }
//    if (head == temp) 
//    {
//        UnosP(head, ime, prezime, godinaRodjenja);
//    }
//    else 
//    {
//        Pozicija p = head;
//        Pozicija n = head;
//        for (n, p; n != temp; p = n, n = n->next);
//        osoba = NovaOsoba(ime, prezime, godinaRodjenja);
//        if (osoba == NULL)
//        {
//            return -1;
//        }
//        osoba->next = p->next;
//        p->next = osoba;
//    }
//    return 0;
//}
//
//int IspisiUDatoteku(char* nazivDatoteke, Pozicija first)
//{
//    Pozicija temp = first;
//    FILE* f = NULL;
//    f = fopen(nazivDatoteke, "w");
//    if (f == NULL)
//    {
//        printf("Neuspjesno otvaranje datoteke.");
//        return -1;
//    }
//    fprintf(f, "Ime\tPrezime\tGodina rodjenja");
//    for (temp; temp; temp = temp->next) 
//    {
//        fprintf(f, "\n%-10s %-13s %d", temp->ime, temp->prezime, temp->godinaRodjenja);
//    }
//    printf("\n");
//    fclose(f);
//    return 0;
//}
//
//int ProcitajIzDatoteke(char* nazivDatoteke, Pozicija head)
//{
//    Pozicija temp = head;
//    FILE* f = NULL;
//    char buffer[MAX_SIZE] = { 0 };
//    char ime[20] = { 0 };
//    char prezime[20] = { 0 };
//    int godinaRodjenja = 0;
//    f = fopen(nazivDatoteke, "r");
//    if (f == NULL)
//    {
//        printf("Neuspjesno otvaranje datoteke.");
//        return -1;
//    }
//    while (!feof(f))
//    {
//        fgets(buffer, MAX_SIZE, f);
//        if (sscanf(buffer, "%s %s %d", ime, prezime, &godinaRodjenja) == 3)
//        {
//            UnosK(temp, ime, prezime, godinaRodjenja);
//        }
//    }
//    fclose(f);
//    return 0;
//}
//
//int main()
//{
//    Osoba head = { .ime = {0},.prezime = {0},.godinaRodjenja = 0,.next = NULL };
//    Pozicija p = &head;
//    UnosP(&head, "Pero", "Peric", 1997);
//    UnosP(&head, "Nikola", "Nikolic", 1997);
//    UnosK(&head, "Ivo", "Ivic", 2001);
//    UnosP(&head, "Ivan", "Horvat", 1997);
//    UnosK(&head, "Dino", "Dinic", 2001);
//    Ispisi(p->next);
//    Pozicija pronadjeni = PronadjiPrezime("Dinic", head.next);
//    if (pronadjeni != NULL) 
//    {
//        printf("Pretraga za \"Dinic\" uspjesna.\nIme: %s\tPrezime: %s\tGodina rodjenja: %d\n\n", pronadjeni->ime, pronadjeni->prezime, pronadjeni->godinaRodjenja);
//    }
//    else 
//    {
//        printf("Nije pronadjen niti jedna osoba s prezimenom \"Dinic\"\n\n");
//    }
//    Obrisi("Horvat", &head);
//    DodajNakon(&head, "Valentina", "Ban", 1995, "Ivic");
//    DodajPrije(&head, "Maja", "Fritaja", 2021, "Peric");
//    Ispisi(p->next);
//    IspisiUDatoteku("osobe.txt", &head);
//    Osoba headIzDatoteke = { .ime = {0},.prezime = {0},.godinaRodjenja = 0,.next = NULL };
//    Pozicija p2 = &head;
//    ProcitajIzDatoteke("osobe.txt", &headIzDatoteke);
//    printf("LISTA IZ DATOTEKE\n");
//    Ispisi(p2->next);
//    return 0;
//}
//
//
//
