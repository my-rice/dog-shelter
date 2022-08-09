#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"


bool greater (TKey key1, TKey key2)
{
   if (strcmp(key1.codice, key2.codice)>0)
      return true;
   else
      return false;
}

bool lower (TKey key1, TKey key2)
{
   if (strcmp(key1.codice, key2.codice)<0)
      return true;
   else
      return false;
}

bool equal(TKey key1, TKey key2)
{
   if (strcmp(key1.codice, key2.codice)==0)
      return true;
   else 
      return false;
}

void print_key (TKey key)
{
   printf ("%10s\t", key.codice);          
}

void print_satellite (TSat sat)
{
   printf ("%17s\t", sat.razza);
   printf("%g\t", sat.peso);
   printf ("%d\n", sat.croccantini);
}


void print_info (TInfo info)
{
     print_key(info.key);
     print_satellite(info.satellite);
}


TKey read_key ()
{
    TKey key;
     
    printf("Inserisci il codice del microcip: ");
    scanf("%s", key.codice);

    return key;
}


TSat read_satellite (){
   TSat sat;  
   int tmp;

	printf ("Inserisci la razza del cane: ");
	scanf ("%s", sat.razza);
	printf ("Inserisci il peso del cane: ");
	scanf ("%g", &sat.peso);
	printf ("Inserisci quantita' di croccantini: ");
	scanf ("%d", &sat.croccantini);
	return sat;
}

TInfo read_info()
{
   TInfo info;
   
   info.key = read_key();
   info.satellite = read_satellite();

   return info;
}
