#include <stdio.h>
#include <strings.h>
#define NUMPEOPLE 6
struct key {
   char *name;
int age; };
typedef struct key Key;
int FindAge(char *name, Key *l, int n);
int main(void)
{
   int i, j;
   Key a[NUMPEOPLE] = {
         {"Ackerby", 21},
         {"Bloggs",  25},
         {"Chumley", 26},
         {"Dalton",  25},
         {"Eggson",  22},
         {"Fulton",  41}  };
   i = FindAge("Eggson",   a, NUMPEOPLE));
   j = FindAge("Campbell", a, NUMPEOPLE));
   printf("%d %d\n", i, j);
return 0; }