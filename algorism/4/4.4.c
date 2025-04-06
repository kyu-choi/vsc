#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int **ima;
char res[1000000];
int idx = 0;

int issame(int x,int y, int size)
{
    int val;
    int i;
    int j;

    val = ima[x][y];
    
    i = x;
    while ( i < x + size)
    {
        j = y;
        while ( j < y + size)
        {
            if (ima[i][j] != val)
                return (0);
            j++;
        }
        i++;
    }

    return (1);

}

void    compress(int x, int y, int size)
{

    int half;

    if (issame(x,y,size))
    {
        if (ima[x][y] == 0)
            res[idx++] = 'w';
        else
            res[idx++] = 'b';
        return;
    }

    res[idx++] = 'x';

    half = size / 2;

    compress(x,y,half);
    compress(x,y+half,half);
    compress(x+half,y,half);
    compress(x+half,y+half,half);

}

int main(void)
{
    int n;
    int i;
    int j;


    scanf("%d",&n);

    ima = (int **)malloc(sizeof(int *)*n);
    i = 0;
    while ( i < n)
    {
        ima[i] = (int *)malloc(sizeof(int)*n);
        i++;
    }
    i = 0;
    while ( i < n)
    {
        j = 0;
        while ( j < n)
        {
            scanf("%d",&ima[i][j]);
            j++;
        }
        i++;
    }


    compress(0,0,n);

    res[idx] = '\0';

    printf("%s",res);
    return (0);


}