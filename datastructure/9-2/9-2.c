#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[50];
    int sc1;
    int sc2;
    int total;
}Student;

int main(void)
{
    int num;
    int i;
    int max;
    int min;

    FILE *fp;
    fp = fopen("in.txt","r");
    if (fp==NULL)
    {
        printf("파일이 열리지않았습니다");
        return (1);
    }

    fscanf(fp,"%d", &num);

    Student *student;

    student = (Student *)malloc(sizeof(Student)*num);
    if (student ==NULL)
    {
        printf("메모리할당에 실패했습니다");
        return (1);
    }

    i = 0;
    while ( i < num)
    {
        fscanf(fp,"%s %d %d",student[i].name,&student[i].sc1,&student[i].sc2);
        i++;
    }

    i = 0;
    while ( i < num)
    {
        student[i].total = student[i].sc1 + student[i].sc2;
        i++; 
    }

    i = 0;
    max = student[0].total;
    min = student[0].total;

    while ( i < num)
    {
        if (max < student[i].total)
            max = student[i].total;
        if (min > student[i].total)
            min = student[i].total;
        i++;
    }

    i = 0;
    printf("최고점 : ");
    while ( i < num )
    {
        
        if (student[i].total == max)
            printf("%s %d   ",student[i].name,max);
        i++;
    }
    printf("\n");

    i = 0;
    printf("최저점 : ");
    while ( i < num )
    {
        
        if (student[i].total == min)
            printf("%s %d   ",student[i].name,min);
        i++;
    }
    printf("\n");



    free(student);
    fclose(fp);

    return (0);
}