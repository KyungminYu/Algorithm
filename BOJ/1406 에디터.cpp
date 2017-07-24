#include <stdio.h>
#include <string.h>
#include <list>
#include <iterator>
using namespace std;

char str[100001], query, element;
int n, len;
list<char> l;
list<char>::iterator it;
int main(){
    scanf("%s %d", &str, &n);
    len = strlen(str);
    for(int i = 0; i < len; i++) l.push_back(str[i]);
    it = l.end();
    for(int i = 0; i < n; i++){
        scanf(" %c", &query);
        switch(query){
            case 'L': 
                if(it != l.begin()) it--;
                break;
            case 'D':
                if(it != l.end()) it++; 
                break;
            case 'B': 
                if(it != l.begin()) it = l.erase(--it); 
                break;
            case 'P':
                scanf(" %c", &element); 
                l.insert(it, element);
                break;
        }
    }
    for(it = l.begin(); it != l.end(); it++) printf("%c", *it);
    return 0;
}