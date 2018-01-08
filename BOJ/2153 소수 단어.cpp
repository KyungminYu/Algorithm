#include <stdio.h>
#include <string.h>
int prime[2050];
char in[21];
int main(){
    for(int i = 1; i <= 2050; i++) prime[i] = 1;
    for(int i = 2; i <= 2050; i++){
        if(prime[i]){
            for(int j = i * 2; j <= 2050; j += i)
                prime[j] = 0;
        }
    }
    scanf("%s", in);
    int len = strlen(in);
    int num = 0;
    for(int i = 0; i < len; i++) {
    	char c = in[i];
    	if('A' <= c && c <= 'Z') num += (c - 'A' + 27);
    	if('a' <= c && c <= 'z') num += (c - 'a' + 1);
    }
    if(prime[num])printf("It is a prime word.");
    else printf("It is not a prime word.");
    return 0;
}