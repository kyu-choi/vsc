#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a;

    int x;
    int y;

    int i;
    int j;
    scanf("%d",&a);

    int **p;
    p = (int **)malloc(sizeof(int *)*a);

    i = 0;
    
    while (i<a)
    {
        p[i] = (int *)malloc(sizeof(int)*a);
        i++;
    }
    i = 0;
    while (i < a)
    {
        j = 0;
        while (j < a)
        {
            p[i][j] = 1;
            j++;
        }
        i++;
    }
    scanf("%d %d",&x,&y);
    p[x][y]= 0;
    


}