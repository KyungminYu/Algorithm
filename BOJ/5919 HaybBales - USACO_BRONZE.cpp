#include <stdio.h>
#include <stdlib.h>

int pile[10000];
int main(){
	int n; scanf("%d", &n);
	int sum = 0, avg;	
	for(int i = 0; i < n; i++){
		scanf("%d", &pile[i]);
		sum += pile[i];
	}
	avg = sum / n;

	int ans = 0; 
	for(int i = 0; i < n; i++)
		ans += abs(avg - pile[i]);
	printf("%d\n", ans / 2);
	return 0;
}