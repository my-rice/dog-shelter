#ifndef INFO_H
#define INFO_H

#include "bool.h"


struct SKey{
   char codice[11];
};   
typedef struct SKey TKey;

struct SSat {
   char razza[16];
   float peso;
   int croccantini;
};
typedef struct SSat TSat;

struct SInfo{
      TKey key;
      TSat satellite;
};

typedef struct SInfo TInfo;

bool greater (TKey key1, TKey key2);
bool lower (TKey key1, TKey key2);
bool equal (TKey key1, TKey key2);

void print_key (TKey key);
void print_satellite (TSat sat);
void print_info (TInfo info);

TKey read_key ();
TSat read_satellite ();
TInfo read_info ();

#endif
