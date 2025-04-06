    #include <stdio.h>
    #include <math.h>
    #include <stdlib.h>

    int funcount = 0;

    void matmul(int size, int **res, int **a, int **b)
    {
        int i;
        int j;
        int k;
        i = 0;
        while ( i < size)
        {
            j = 0;
            while(j < size)
            {
                res[i][j] = 0;
                k = 0;
                while ( k < size)
                {
                   
                    res[i][j] += (a[i][k]*b[k][j]);
                    k++;
                }
                j++;
            }
            i++;
        }
    }

    void matadd(int size, int **res, int **a, int **b)
    {
        int i;
        int j;
        i = 0;
        while ( i < size)
        {
            j = 0;
            while ( j < size)
            {
                res[i][j] = a[i][j] + b[i][j];
                j++;
            }
            i++;
        }
    }

    void matsub(int size, int **res, int **a, int **b)
    {
        int i;
        int j;

        i = 0;
        while ( i < size)
        {
            j = 0;
            while ( j < size)
            {
                res[i][j] = a[i][j] - b[i][j];
                j++;
            }
            i++;
        }

    }

    void matmerge(int size, int **res, int **c00, int **c01, int **c10, int **c11)
    {
        int i;
        int j;
        i = 0;
        while ( i < size)
        {
            j = 0;
            while ( j < size)
            {
                res[i][j] = c00[i][j];
                res[i][j + size] = c01[i][j];
                res[i + size][j] = c10[i][j];
                res[i + size][j + size] = c11[i][j];
                j++;
            }
            i++;
        }

    }

    void    strassen(int size, int **res, int **a, int **b, int k)
    {
        funcount++;
        
        int newsize;
        int i;
        int j;

        newsize = size / 2;

        if (size <= k)
        {
            matmul(size, res, a, b);
            return;
        }

        int **a00, **a01, **a10, **a11, **b00, **b01, **b10, **b11;
        int **M1, **M2, **M3, **M4, **M5, **M6, **M7;
        int **c00, **c01, **c10, **c11;
        int **temp1, **temp2;

        a00 = (int **)malloc(sizeof(int *) * newsize);
        a01 = (int **)malloc(sizeof(int *) * newsize);
        a10 = (int **)malloc(sizeof(int *) * newsize);
        a11 = (int **)malloc(sizeof(int *) * newsize);
        b00 = (int **)malloc(sizeof(int *) * newsize);
        b01 = (int **)malloc(sizeof(int *) * newsize);
        b10 = (int **)malloc(sizeof(int *) * newsize);
        b11 = (int **)malloc(sizeof(int *) * newsize);
        c00 = (int **)malloc(sizeof(int *) * newsize);
        c01 = (int **)malloc(sizeof(int *) * newsize);
        c10 = (int **)malloc(sizeof(int *) * newsize);
        c11 = (int **)malloc(sizeof(int *) * newsize);
        M1 = (int **)malloc(sizeof(int *) * newsize);
        M2 = (int **)malloc(sizeof(int *) * newsize);
        M3 = (int **)malloc(sizeof(int *) * newsize);
        M4 = (int **)malloc(sizeof(int *) * newsize);
        M5 = (int **)malloc(sizeof(int *) * newsize);
        M6 = (int **)malloc(sizeof(int *) * newsize);
        M7 = (int **)malloc(sizeof(int *) * newsize);
        temp1 = (int **)malloc(sizeof(int *) * newsize);
        temp2 = (int **)malloc(sizeof(int *) * newsize);

        i = 0;
        while ( i < newsize)
        {
            a00[i] = (int *)malloc(sizeof(int ) * newsize);
            a01[i] = (int *)malloc(sizeof(int ) * newsize);
            a10[i] = (int *)malloc(sizeof(int ) * newsize);
            a11[i] = (int *)malloc(sizeof(int ) * newsize);
            b00[i] = (int *)malloc(sizeof(int ) * newsize);
            b01[i] = (int *)malloc(sizeof(int ) * newsize);
            b10[i] = (int *)malloc(sizeof(int ) * newsize);
            b11[i] = (int *)malloc(sizeof(int ) * newsize);
            c00[i] = (int *)malloc(sizeof(int ) * newsize);
            c01[i] = (int *)malloc(sizeof(int ) * newsize);
            c10[i] = (int *)malloc(sizeof(int ) * newsize);
            c11[i] = (int *)malloc(sizeof(int ) * newsize);
            M1[i] = (int *)malloc(sizeof(int ) * newsize);
            M2[i] = (int *)malloc(sizeof(int ) * newsize);
            M3[i] = (int *)malloc(sizeof(int ) * newsize);
            M4[i] = (int *)malloc(sizeof(int ) * newsize);
            M5[i] = (int *)malloc(sizeof(int ) * newsize);
            M6[i] = (int *)malloc(sizeof(int ) * newsize);
            M7[i] = (int *)malloc(sizeof(int ) * newsize);
            temp1[i] = (int *)malloc(sizeof(int ) * newsize);
            temp2[i] = (int *)malloc(sizeof(int ) * newsize);
            i++;
        }

        i = 0;
        while ( i < newsize)
        {
            j = 0;
            while ( j < newsize)
            {
                a00[i][j] = a[i][j];
                a01[i][j] = a[i][j + newsize];
                a10[i][j] = a[i + newsize][j];
                a11[i][j] = a[i + newsize][j + newsize];
                b00[i][j] = b[i][j];
                b01[i][j] = b[i][j + newsize];
                b10[i][j] = b[i + newsize][j];
                b11[i][j] = b[i + newsize][j + newsize];
                j++;
            }
            i++;
        }
        //M1
        matadd(newsize,temp1,a00,a11);
        matadd(newsize,temp2,b00,b11);
        strassen(newsize,M1,temp1,temp2,k);
        //M2
        matadd(newsize,temp1,a10,a11);
        strassen(newsize, M2, temp1, b00,k);
        //M3
        matsub(newsize, temp1, b01,b11);
        strassen(newsize, M3, a00, temp1,k);
        //M4
        matsub(newsize, temp1, b10, b00);
        strassen(newsize, M4, a11, temp1,k);
        //M5
        matadd(newsize, temp1, a00, a01);
        strassen(newsize, M5, temp1, b11,k);
        //M6
        matsub(newsize, temp1, a10, a00);
        matadd(newsize, temp2, b00, b01);
        strassen(newsize, M6, temp1, temp2,k);
        //M7
        matsub(newsize, temp1, a01, a11);
        matadd(newsize, temp2, b10, b11);
        strassen(newsize, M7, temp1, temp2,k);

        matadd(newsize, temp1, M1, M4);
        matsub(newsize, temp2, M7, M5);
        matadd(newsize, c00, temp1, temp2);

        matadd(newsize, c01, M3, M5);

        matadd(newsize, c10, M2, M4);

        matsub(newsize, temp1, M1, M2);
        matadd(newsize, temp2, M3, M6);
        matadd(newsize, c11, temp1, temp2);

        matmerge(newsize, res,c00,c01,c10,c11);


    }

    void printarr(int **arr,int size)
    {
        int i;
        int j;

        i = 0;
        while ( i < size)
        {
            j = 0;
            while ( j < size)
            {
                printf("%d",arr[i][j]);
                if ( j != size-1)
                    printf(" ");
                else
                    printf("\n");
                j++;
            }
            i++;
        }
        printf("\n");
    }

    int nextpowtwo(int n)
    {
        int count;

        count = 0;

        while ( 1 )
        {
            n = n/2;
            count++;
            if ( n==1)
                break;
        }

        count ++;

        return (pow(2,count));

    }

    int ispowtwo(int n)
    {
        if ( (n & (n-1)) == 0)
            return (1);
        return (0);
    }

    int main(void)
    {
        int n;
        int size;
        int k;
        int i;
        int j;

        int **a;
        int **b;
        int **res;

        scanf("%d %d",&n,&k);

        if ( ispowtwo(n) == 0)
            size = nextpowtwo(n);
        else
            size = n;

        a = (int **)malloc(sizeof(int *) * size);
        b = (int **)malloc(sizeof(int *) * size);
        res = (int **)malloc(sizeof(int *) * size);


        i = 0;

        while ( i < size)
        {
            a[i] = (int *)malloc(sizeof(int)*size);
            b[i] = (int *)malloc(sizeof(int)*size);
            res[i] = (int *)malloc(sizeof(int)*size);

            j = 0;
            while ( j < size)
            {
                a[i][j] = 0;
                b[i][j] = 0;
                res[i][j] = 0;
                j++;
            }
            i++;
        }

        i = 0;
        while ( i < n )
        {
            j = 0;
            while ( j < n )
            {
                scanf("%d",&a[i][j]);
                j++;
            }
            i++;
        }

        i = 0;
        while ( i < n )
        {
            j = 0;
            while ( j < n )
            {
                scanf("%d",&b[i][j]);
                j++;
            }
            i++;
        }

        strassen(size, res, a, b, k);

        printf("%d\n",funcount);
        printarr(res,n);

    
        return (0);

    }