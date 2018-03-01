#include <stdio.h>
#include <string.h>
int val[] = { 3, 2, 1, 2, 3, 3, 2, 3, 3, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2, 1 };
int vals[4001]; 
char A[2001], B[2001];
int main(){
	scanf(" %s %s", A, B);
	int len = strlen(A);
	for(int i = 0; i < len; i++){
		vals[i * 2] 	= val[A[i] - 'A'];
		vals[i * 2 + 1] = val[B[i] - 'A'];
	}
	int tlen = len *= 2;
	for(int i = 0; i < len - 2; i++, tlen--){
		for(int j = 0; j < tlen - 1; j++)
			vals[j] = (vals[j] + vals[j + 1]) % 10;
	}
	printf("%d%d\n", vals[0], vals[1]);
	return 0;
}