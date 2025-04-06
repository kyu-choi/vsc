#include <stdio.h>
#include <string.h>

int palindrome(char *str, int left, int right)
{
    if (str[left]!=str[right])
        return (0);
    if (left >= right)
        return (1);
    left +=1;
    right -=1;
    return (palindrome(str, left, right));
    
}

int main(void)
{
    char    string[30];
    int size;
    int palindromev;

    printf("문자열을 입력하세요: ");
    scanf("%s",string);

    size = strlen(string);

    palindromev = palindrome(string, 0, size - 1);

    if (palindromev == 0)
        printf("NOT palindrome!");
    else
        printf("Palindrome!");
    
    return (0);

}