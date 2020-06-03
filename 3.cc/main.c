#include<stdio.h>
#include<string.h>
int main() {
    char str1[10000][80];
    char str2[10000][80], *str3;
    scanf("%s %s", str1, str2);
    str3 = str1[0];
    for(int i = 0; i < 10; i++) {
        if(strstr(str2, str1)) {
            strcpy(str1,str3);
        }
        printf("%d", i);
    }
    return 0;
}
