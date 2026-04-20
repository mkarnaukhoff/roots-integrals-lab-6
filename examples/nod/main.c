#include <stdio.h>
#include <stdlib.h>
extern int nod(int a, int b);

int main()
{
    static int a,b = 5;
    printf("Input  2 numbers:  ");
    scanf("%d%d",&a,&b);
    printf("Nod = %d\n", nod(a,b));
    return 0;
}
