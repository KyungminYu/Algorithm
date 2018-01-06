#include <stdio.h>

char s[6];
int isHansu(int num){
	int idx = 0;
	while(num){
		s[idx++] = num % 10;
		num /= 10;
	}
	for(int i = 0; i < idx - 2; i++){
		if(s[i] - s[i + 1] != s[i + 1] - s[i + 2])
			return 0;
	}
	return 1;
}
int main(){
	int n; scanf("%d", &n);
	int res = 0;
	for(int i = 1; i <= n; i++)
		if(isHansu(i)) res++;
	printf("%d\n", res);
	return 0;
}