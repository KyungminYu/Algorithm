#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int size, sum;
char num[100005];
int main(){
    scanf("%s", num);
    size = strlen(num);
    for(int i = 0; i < size; i++) 
        sum += (num[i] - '0');
    sort(num, num + size, greater<int>());
    if(num[size - 1] == '0' && sum % 3 == 0) 
        for(int i = 0; i < size; i++) printf("%c", num[i]);
    else printf("-1");
    return 0;
}