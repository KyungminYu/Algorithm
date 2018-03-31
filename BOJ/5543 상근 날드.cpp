#include <stdio.h>

#define MIN(a, b)((a) < (b) ? (a) : (b))
int main(){
	int b = 1e9, w = 1e9;
	for(int i = 0; i < 3; i++){
		int t; scanf("%d", &t);
		b = MIN(b, t);
	}
	for(int i = 0; i < 2; i++){
		int t; scanf("%d", &t);
		w = MIN(w, t);
	}	
	printf("%d\n", b + w - 50);
	return 0;
}