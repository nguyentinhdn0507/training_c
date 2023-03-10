#include <stdio.h>
#include <ctype.h>

void reverse(char* begin, char* end)
{
    char temp;
    while (begin < end) {
        temp = *begin;
        *begin++ = *end;
        *end-- = temp;
    }
}
void reverseWords(char* s)
{
    char* word_begin = s;
    char* temp = s;
    while (*temp) {
        temp++;
        if (*temp == ' ') {
            reverse(word_begin, temp - 1);
            word_begin = temp + 1;
        }
    }
    reverse(s, temp - 1);
}
int main()
{
    char s[1000] ;
    printf("Nhap chuoi: ");
    fgets(s, 100, stdin);
    char* temp = s;
    reverseWords(s);
    printf("%s", s);
    return 0;
}