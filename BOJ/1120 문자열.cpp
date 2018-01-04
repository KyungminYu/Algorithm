#include <stdio.h>
#include <string.h>

int main(){
	char a[51], b[51];
	scanf("%s %s", a, b);
	int alen = strlen(a);
	int blen = strlen(b);
	int diff = blen - alen;

	int res = 1e9;
	for(int i = 0; i <= diff; i++){
		int val = 0;
		for(int j = i; j < i + alen; j++)
			val += (a[j - i] != b[j]);
		res = val < res ? val : res;
	}
	printf("%d\n", res);

	return 0;
}