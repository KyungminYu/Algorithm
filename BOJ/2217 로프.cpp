#include <stdio.h>
#include <algorithm>
using namespace std;
int main(){
	int n, res = 0, lope[100000];
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", lope + i);
	sort(lope, lope + n);
	for(int k = 1; k <= n; k++)
		res = lope[n - k] * k > res ? 
		      lope[n - k] * k : res; 
	printf("%d\n", res);
	return 0;
}