#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 40 

struct _Person;
typedef struct _Person *Position;
typedef struct _Person
{
  char ime[MAX_SIZE];
  char prezime[MAX_SIZE];
  int godiste;
  Position next;
} Person;

Position StvoriNovuOsobu (char* ime, char* prezime, int godiste)
{
  Position novaOsoba=NULL;
  
  novaOsoba = (Position) malloc (sizeof (Person));
  if(!novaOsoba)
  {
      perror("Couldn't allocate memmory.\n");
      return NULL;
  }
  
  strcpy(novaOsoba->ime,ime);
  strcpy(novaOsoba->prezime,prezime);
  novaOsoba->godiste = godiste;
  novaOsoba->next=NULL;
  return novaOsoba;
}

int InsertAfter (Position p, Position novaOsoba)
{
  novaOsoba->next = p->next;
  p->next = novaOsoba;

  return 0;
}

Position FindLast (Position head)
{
  Position last = head;

  while (last->next)
    {
      last = last->next;
    }

  return last;
}

int AddStart (Position head, char* ime, char* prezime, int godiste)
{
  Position novaOsoba = NULL;

  novaOsoba = StvoriNovuOsobu (ime, prezime, godiste);
  if (!novaOsoba)
    return -1;

  InsertAfter (head, novaOsoba);

  return 0;
}

int AddEnd (Position head, char* ime, char* prezime, int godiste)
{
  Position newPerson = NULL;
  Position last=NULL;

  newPerson = CreateNewPerson (ime, prezime, godiste);
  if (!novaOsoba)
    return -1;
  
  last=FindLast(head);
  InsertAfter (last, novaOsoba);

  return 0;
}

int PrintList (Position first)
{
  Position temp = first;
  
  if(!temp)
    printf("The list is empty. :(\n\n");
  for (temp; temp; temp = temp->next)
    printf ("Ime: %s\tPrezime: %s\tGodiste: %d\n",
	    temp->ime, temp->prezime, temp->godiste);

  return 0;
}

Position FindBySurname(char* prezime, Position first)
{
    Position temp=first;
    
    for(temp;temp;temp=temp->next)
        if(strcmp(temp->prezime,prezime)==0)
            return temp;
    
    if(!temp)
        printf("Prezime %s!\n\n", surname);
    return temp;
}

int Delete(char* prezime, Position head)
{
    Position temp=head;
    Position toDelete=NULL;
    
    for(temp;temp->next;temp=temp->next)
        if(strcmp(temp->next->prezime,prezime)==0)
            break;
    toDelete=temp->next;
    temp->next=toDelete->next;
    free(toDelete);
    
    return 0;
}

int main ()
{
    Person head = {0}.ime = { 0 }, .prezime = { 0 }, .godiste = 0, .next = NULL
};
  Position p = &head;
  
  AddStart(&head, "Pero", "Peric", 1997);
  AddEnd(&head, "Dino", "Dinic", 2001);
  AddStart(&head, "Lovro", "Lovric", 1999);
  
  PrintList(p->next);
  printf("\n");
  
  Delete("Peric", &head);
  Delete("Dinic", &head);
  Delete("Lovric", &head);
  
  PrintList(p->next);
  
  FindBySurname("Dinic", head.next);
  
  AddEnd(&head, "Pero", "Peric", 2001);
  AddStart(&head, "Dino", "Dinic", 1997);
  AddEnd(&head, "Lovro", "Lovric", 1999);
  
  PrintList(p->next);
  
  return 0;
}

