#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"
#include "tree.h"
#define MAXCHAR 10
#define n 100

int menu();
bool inserisci_cane (TTree *tree, TInfo info);
int crea_elenco_razze (TTree tree, char elenco[][MAXCHAR]); 
void stampa_razze (char elenco[][MAXCHAR], int riemp);
TNode* cerca_cane_grasso (TTree tree);
void stampa_elenco(TTree tree);
int numero_cani_di_razza(TTree tree, char* razza);

TNode* max(TNode *a, TNode *b);
void pulbuf(){
    while(getchar() != '\n');
}

/************************************************************************************
INSERIRE QUI I PROTOTIPI DELLE FUNZIONI
***********************************************************************************/

 int main()
{
    int scelta;
    TTree tree;
    TInfo info;
    TNode* node;
    TKey key;
    bool ret;
    char raz[10];
    int riemp,r;
    char elenco[n][10];
    TNode*caniello;
    /* Inizializzo la lista */
    tree = tree_create();
    /* Scelta della funzione per gestire l'elenco */
    while(scelta=menu()){
        switch(scelta){
            case 1:
            info=read_info ();
            ret=inserisci_cane (&tree,info);
            break;
        case 2:
            printf("matrice riempita\n");
            for(int i=0; i<n;i++){
                elenco[i][0]='\0';
            }
            riemp=crea_elenco_razze(tree, elenco);
            break;
        case 3:
            stampa_razze(elenco, riemp);
            break;
        case 4:
            caniello= cerca_cane_grasso(tree);
            printf("cane con rapporto peso/croccantini minore: ");
            print_info(caniello->info);
            printf("\n");
            break;
        case 5:
            stampa_elenco(tree);
            break;
        case 6:
            printf("inserire nome razza da cercare: ");
            pulbuf();
            scanf("%[^\n]s",raz);
            pulbuf();
            r= numero_cani_di_razza(tree,raz);
            printf("ci sono %d cani di razza %s\n", r,raz);
            break;
        }
    }
    system("PAUSE");
 }

int menu()
{
    int scelta;
    system("CLS");
    printf("-------------------------------------------------\n");
    printf("PROGRAMMA PER GESTIRE UN CANILE \n\n");
    printf("1. Inserimento nuovo cane\n");
    printf("2. Ricerca dell'elenco delle razze\n");
    printf("3. Stampa dell'elenco delle razze\n");
    printf("4. Ricerca del cane con rapporto peso/quantita' croccantini piu' basso\n");
    printf("5. Stampa l'elenco di tutti i cani in archivio\n");
    printf("6. Stampa numero di cani per un razza in archivio\n");
    printf("0. EXIT\n\n");
    printf("-------------------------------------------------\n");
    printf("Selezionare la scelta [0-6]: ");
    scanf("%d", &scelta);
    while((scelta<0)||(scelta>6)){
        printf("ERRORE! valore non consentito\n");
        printf("Selezionare la scelta [0-6]: ");
        scanf("%d", &scelta);
    }
    return scelta;
    system("PAUSE");
}

bool inserisci_cane (TTree *tree, TInfo info){
    TNode *node;
    node = tree_search(*tree, info.key);
    if (node == NULL){
        *tree = tree_insert(*tree, info);
        return true;
    }
        return false;
}

/****************************************************************************
INSERIRE QUI LE FUNZIONI DA SCRIVERE
****************************************************************************/

int crea_elenco_razze (TTree tree, char elenco[][10]){
    if(tree==NULL)
        return 0;
    
    int l=0,r=0,j=0;
    
    l=crea_elenco_razze(tree->left, elenco);
    r=crea_elenco_razze(tree->right, elenco);
    
    for(int i=0; i<(l+r); i++){ //cerca se la razza è già inserita nell'elenco (in caso di foglia non entra nel for)
        if(!strcmp(tree->info.satellite.razza,elenco[i]))
            return (l+r);
    }
    
    for(j=0; j<n && (elenco[j][0]!='\0'); j++); //calcolo l'ultima posizione del registro non vuoto
    
    strcpy(elenco[j],tree->info.satellite.razza); //inserisco la razza nel registro
    
    return (l+r+1); //incremento il contatore di razze
}
void stampa_razze (char elenco[][10], int riemp){
    for(int i=0; i<riemp;i++){
        printf("razza[%d]: %s\n", i,elenco[i]);
    }
}
TNode* cerca_cane_grasso(TTree tree){
    TNode *r;
    TNode *l;
    if(tree==NULL)
        return NULL;
    l=cerca_cane_grasso(tree->left);
    r=cerca_cane_grasso(tree->right);
    return(max(tree,max(l,r)));
}
TNode* max(TNode *a, TNode *b){//diritti riservati ad A.Langella SPA
    if(a==NULL)
        return b;
    if(b==NULL)
        return a;
    if((a->info.satellite.peso/a->info.satellite.croccantini) < (b->info.satellite.peso/b->info.satellite.croccantini))
        return a;
    return b;
}

void stampa_elenco(TTree tree){
    if(tree==NULL)
        return;
    stampa_elenco(tree->left);
    print_info(tree->info);
    stampa_elenco(tree->right);
    return;
}
int numero_cani_di_razza(TTree tree, char* razza){
    if(tree==NULL)
        return 0;
    if(!strcmp(tree->info.satellite.razza, razza))
        return ( 1 + numero_cani_di_razza(tree->left,razza) + numero_cani_di_razza(tree->right, razza) );
    return (numero_cani_di_razza(tree->left,razza) + numero_cani_di_razza(tree->right, razza) );
}

        
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"
#include "tree.h"

/*
Esame di Algoritmi e Strutture Dati
            13/07/2011
Si richiede di scrivere un’applicazione per la gestione di un canile.
Le informazioni di interesse per ogni cane sono le seguenti:
	Codice microchip identificativo (Una stringa di 10 caratteri) (chiave)
	Razza (Una stringa di 15 caratteri)
	Peso in kg (Un reale)
	Quantità croccantini giornalieri in grammi (Un intero)
Il programma deve offrire le seguenti funzionalità:
	Inserimento di un cane. (Già fornita)
	Ricerca e stampa dell’elenco delle razze presenti in archivio. 
	Ricerca del cane con il rapporto peso/quantità croccantini più basso.
	Stampa dell’elenco delle informazioni di tutti i cani presenti nel canile.
L’applicazione consente di gestire il canile attraverso la struttura dati albero binario, mettendo a disposizione dell’utente un menù attraverso cui è possibile effettuare le suddette operazioni.
Ai candidati sono forniti i seguenti file che non debbono essere modificati:
	bool.h: contiene la dichiarazione del tipo bool;
	info.h e info.c: contengono le dichiarazioni dei tipi TKey, TSat e TInfo, nonché le dichiarazioni e le definizioni delle routine di gestione dei suddetti tipi
	tree.h e tree.c: contengono la dichiarazione del tipo TTree, nonché le dichiarazioni e le definizioni delle routine per le comuni operazioni sugli alberi.
Al candidato si richiede di scrivere il file canile.c con le seguenti funzioni oltre il main:
int crea_elenco_razze (TTree tree, char elenco[][MAXCHAR]); 	La funzione crea un array di stringhe che rappresenta l’elenco di tutte le razze presenti nel canile. La razza non è una chiave quindi nel canile esisteranno più cani della stessa razza, la funzione però deve restituire un array con una sola occorrenza per razza. La funzione restituisce il riempimento dell’array e l’array elenco
void stampa_razze (char elenco[][MAXCHAR], int riemp);	La funzione calcola il numero cani di una data razza presenti nel canile.
E’ RICHIESTA UNA IMPLEMENTAZIONE RICORSIVA IN CODA SULLA BASE DEL DIVIDE ET IMPERA
TNode* cerca_cane_grasso (TTree tree);	La funzione cerca il cane con rapporto Peso/Quantità croccantini più basso e cioè il cane che mangia di più rispetto al suo peso.
E’ RICHIESTA UNA IMPLEMENTAZIONE RICORSIVA SULLA BASE DEL DIVIDE ET IMPERA
void stampa_elenco(TTree tree);	Stampa le informazioni di tutti i cani presenti nell’elenco.
E’ RICHIESTA UNA IMPLEMENTAZIONE RICORSIVA SULLA BASE DEL DIVIDE ET IMPERA


 
 */
/*
#define MAXCHAR 10
#define n 100


int menu();
bool inserisci_cane (TTree *tree, TInfo info);
int crea_elenco_razze (TTree tree, char elenco[][MAXCHAR]); 
void stampa_razze (char elenco[][MAXCHAR], int riemp);
TNode* cerca_cane_grasso (TTree tree);
void stampa_elenco(TTree tree);
int numero_cani_di_razza(TTree tree, char* razza);

*/ 

/************************************************************************************
		INSERIRE QUI I PROTOTIPI DELLE FUNZIONI
 ***********************************************************************************/

/*
void pulbuf(){
    while(getchar() != '\n');
}
int main()
{
          
        int scelta;
        TTree tree;
        TInfo info;
        TNode* node;
        TKey key;
        bool ret;
        char raz[10];
        int riemp,r;
        char elenco[n][10];
        TNode*caniello;
	  
      tree = tree_create();

         while(scelta=menu()){
         switch(scelta){
            case 1:
                info=read_info ();
                ret=inserisci_cane (&tree,info);
                break;
            case 2:
                printf("matrice riempita\n");
                riemp=crea_elenco_razze(tree, elenco);
                break;
            case 3:
                stampa_razze(elenco, riemp);
                break;
            case 4:
                caniello= cerca_cane_grasso(tree);
                printf("cane con rapporto peso/croccantini minore: ");
                print_info(caniello->info);
                printf("\n");
                break;
            case 5:
                stampa_elenco(tree);
                break;
            case 6:
                pulbuf;
                printf("inserire nome razza da cercare: ");
                scanf("%[^\n]s",raz);
                pulbuf;
                r= numero_cani_di_razza(tree,raz);
                printf("ci sono %d cani di razza %s\n", r,raz);
                break;
            }
      }
      //system("PAUSE");  

}   

/*
 

 */

/*
int menu()
{
    int scelta;
    
    //system("CLS");
    printf("-------------------------------------------------\n");
    printf("PROGRAMMA PER GESTIRE UN CANILE \n\n");
    printf("1. Inserimento nuovo cane\n");
    printf("2. Ricerca e stampa dell'elenco delle razze\n");
    printf("3. Ricerca del cane con rapporto peso/quantita' croccantini piu' basso\n");
    printf("4. Stampa l'elenco di tutti i cani in archivio\n");
    printf("0. EXIT\n\n");
    printf("-------------------------------------------------\n");
    printf("Selezionare la scelta [0-4]: ");
    scanf("%d", &scelta);
    while((scelta<0)||(scelta>4)){
		printf("ERRORE! valore non consentito\n");                        
		printf("Selezionare la scelta [0-4]: ");
		scanf("%d", &scelta);
    }
    return scelta;
	
//	system("PAUSE");
}


bool inserisci_cane (TTree *tree, TInfo info)
{
	TNode *node;
	
	node = tree_search(*tree, info.key);
	if (node == NULL)
	{
		*tree = tree_insert(*tree, info);
		return true;
	}
	return false;
}

*/
/****************************************************************************
 INSERIRE QUI LE FUNZIONI DA SCRIVERE
 ****************************************************************************/
/*
int crea_elenco_razze (TTree tree, char elenco[][MAXCHAR]){
    
    if(tree == NULL){
        return 0;
    }
    elenco = realloc(elenco,1*sizeof(char)*MAXCHAR);
    strcpy(elenco[0],tree->info.satellite.razza);    
    
    char *
    elenco_razze()
    
    TNode* m = tree;
    while(m != NULL){
         if(m->right == NULL && m->left == NULL){
             
         }   
    }
    
    
    
    
    
}
*/

/*
int crea_elenco_razze (TTree tree, char elenco[][10]){
    
    //La funzione crea un array di stringhe che rappresenta l’elenco di tutte le razze presenti nel canile. 
    //La razza non è una chiave quindi nel canile esisteranno più cani della stessa razza, 
    //la funzione però deve restituire un array con una sola occorrenza per razza. 
    //La funzione restituisce il riempimento dell’array e l’array elenco
    
    if(tree==NULL)
        return 0;
    int l=0,r=0,j=0;
    l=crea_elenco_razze(tree->left, elenco);
    r=crea_elenco_razze(tree->right, elenco);
    for(int i=0; i<(l+r); i++){
        if(!strcmp(tree->info.satellite.razza,elenco[i]))
            return (l+r);
    }
    for(j=0; j<n && (elenco[j][0]=='\0'); j++);
    strcpy(elenco[j],tree->info.satellite.razza);
    return (l+r+1);
}

void stampa_razze (char elenco[][MAXCHAR], int riemp){
    printf("Elenco razze: \n");
    for(int i=0;i<riemp;i++){
        printf("Razza: %s\n",elenco[i]);
    }
}

TNode* cerca_cane_grasso (TTree tree){
    
    //La funzione cerca il cane con rapporto Peso/Quantità croccantini più basso e cioè il cane che mangia di più rispetto al suo peso.
    //E’ RICHIESTA UNA IMPLEMENTAZIONE RICORSIVA SULLA BASE DEL DIVIDE ET IMPERA
    
    
    if(tree == NULL){
        return NULL;
    }
    
    TNode* rigth = cerca_cane_grasso (tree->right);
    TNode* left = cerca_cane_grasso (tree->left);
    
    TNode* obeso;
    if(rigth == NULL && left==NULL) 
        obeso = NULL;
    else if(rigth == NULL)
        obeso = left;
    else if(left == NULL)
        obeso = rigth;
    else if((float)rigth->info.satellite.peso/rigth->info.satellite.croccantini >= (float)left->info.satellite.peso/left->info.satellite.croccantini){
        obeso = rigth;
    }else
        obeso = left;
    
    
    if(tree == NULL && obeso == NULL){
        return tree;
    }else if(tree == NULL )
    if((float)tree->info.satellite.peso/tree->info.satellite.croccantini >= (float)obeso->info.satellite.peso/obeso->info.satellite.croccantini){
        return tree;
    }else
        return rigth;
}

int numero_cani_di_razza(TTree tree, char* razza){
    
    //La funzione calcola il numero cani di una data razza presenti nel canile.
    //E’ RICHIESTA UNA IMPLEMENTAZIONE RICORSIVA IN CODA SULLA BASE DEL DIVIDE ET IMPERA
    
    if(tree == NULL){
        return 0;
    }
    int sum;
    if(strcmp(tree->info.satellite.razza,razza)==0){
        return 1+numero_cani_di_razza(tree->right, razza) + numero_cani_di_razza(tree->left, razza);
    }
    return numero_cani_di_razza(tree->right, razza) + numero_cani_di_razza(tree->left, razza);
}

void stampa_elenco(TTree tree){
    tree_print(tree);
}
*/