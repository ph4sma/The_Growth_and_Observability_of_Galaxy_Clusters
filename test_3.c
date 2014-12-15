// Complete the program so that when the user exe- cutes it and types in 2, 3, and 7, this is what appears on the screen:
// Input three integers: 2 3 7
// Twice the sum of integers plus 7 is 31 !

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int i, num, sum = 0, answer ;

printf("Input three integers: \n");

for (i = 0 ; i < 3; i++)
    {
        scanf("%d", &num);
        sum = sum + num;
    }

answer = 7 + (2*sum);

printf("Twice the sum of integers plus 7 is %d !\n", answer);


return 0;

}