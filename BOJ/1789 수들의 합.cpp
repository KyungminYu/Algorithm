#include <stdio.h>

int main(){
	unsigned int s, n;
	scanf("%u", &s);
	for(n = 1; n <= s; n++)	s -= n;
	printf("%u", n - 1);
	return 0;
}