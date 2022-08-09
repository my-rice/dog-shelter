# dog-shelter
## Exercise Description
It is required to write an application for the management of a kennel.

The information of interest to each dog is as follows:
- Identification microchip code (A string of 10 characters) (key)
- Race (A string of 15 characters)
- Weight in kg (A real)
- Daily crunchy quantity in grams (One whole)

The program must offer the following features:
- Entering a dog. (Already supplied)
- Search and print the list of breeds in the archive.
- Search for the dog with the lowest weight / quantity ratio.
- Printing of the information list of all dogs in the kennel.

The application allows you to manage the kennel through the binary tree data structure, providing the user with a menu through which the aforementioned operations can be carried out.

## Given files
Candidates are provided with the following files which must not be modified:
- bool.h: contains the declaration of the bool type;

- info.h and info.c: they contain the declarations of the types TKey, TSat and TInfo, as well as the declarations and definitions of the management routines of the aforementioned types

- tree.h and tree.c: contain the TTree type declaration, as well as routine declarations and definitions for common tree operations.

## Tasks
The candidate is required to write the canile.c file with the following functions besides main:

> int create_list_races (TTree tree, char list [] [MAXCHAR]);
The function creates an array of strings that represents the list of all breeds present in the kennel. The breed is not a key therefore in the kennel there will be more dogs of the same breed, however the function must return an array with only one occurrence per breed. The function returns the fill of the array and the list array

> void print_races (char list [] [MAXCHAR], int fill);
The function calculates the number of dogs of a given breed present in the kennel.
A RECURSIVE IMPLEMENTATION IN QUEUE IS REQUIRED ON THE BASIS OF DIVIDE ET IMPERA

> TNode * search_fat_dog (TTree tree);
The function searches for the dog with the lowest weight / quantity ratio, i.e. the dog that eats more than its weight.
A RECURSIVE IMPLEMENTATION IS REQUIRED ON THE BASIS OF DIVIDE ET IMPERA

> void print_list (TTree tree);
Print the information of all the dogs on the list.
A RECURSIVE IMPLEMENTATION IS REQUIRED ON THE BASIS OF DIVIDE ET IMPERA