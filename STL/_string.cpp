#pragma GCC optimize("O2")
#include <stdio.h>
#include <malloc.h>
class _string{
public: 
    char* str;
    int length;
    _string(){
        str = (char*) malloc(sizeof(char));
        str[0] = '\0';
        length = 0;
    }
    void alloc(char s[], int len){
        char* tmp = (char*)malloc(sizeof(char) * (len + 2));
        for(int i = 0; i < len; i++) 
            tmp[i] = s[i];
        tmp[len] = '\0';
        free(str);
        str = tmp;
        length = len;
    }
    char operator [] (int idx){
        return str[idx];
    }
};