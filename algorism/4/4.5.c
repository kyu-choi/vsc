#include <stdio.h>
#include <stdlib.h>

int **ima;
char *inp;
int idx = 0;

void    decompress(int x, int y, int size)
{
    int i;
    int j;
    int val;
    char cur;
    int half;
    
    cur = inp[idx++];

    if (cur =='w')
    {
        val = 0;
        i = x;
        while ( i < x + size)
        {
            j = y;
            while ( j < y + size)
            {
                ima[i][j] = val;
                j++;
            }
            i++;
        }
        return;
    }
    else if (cur =='b')
    {
        val = 1;
        i = x;
        while ( i < x + size)
        {
            j = y;
            while ( j < y +size)
            {
                ima[i][j] = val;
                j++;
            }
            i++;
        }
        return;
    }

    half = size / 2;

    decompress(x,y,half);
    decompress(x,y+half,half);
    decompress(x+half,y,half);
    decompress(x+half,y+half,half);
    
}

int main(void)
{
    int n;
    int i;
    int j;

    scanf("%d",&n);

    inp = (char *)malloc(sizeof(char) * (n*n+1));

    ima = (int **)malloc(sizeof(int *) * n);
    i = 0;
    while ( i < n)
    {
        ima[i] = (int *)malloc(sizeof(int) * n);
        i++;
    }

    scanf("%s",inp);

    decompress(0,0,n);

    printf("%d\n",n);
    i = 0;
    while ( i < n)
    {
        j = 0;
        while ( j < n)
        {
            printf("%d",ima[i][j]);
            if (j != n-1)
                printf(" ");
            else
                printf("\n");
            j++;
        }
        i++;
    }
    return (0);
}