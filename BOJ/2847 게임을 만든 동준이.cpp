#include <stdio.h>

int in[101];
int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &in[i]);
	int res = 0;
	for(int i = n - 1; i > 0; i--){
		if(in[i] > in[i - 1]) continue;
		res += (in[i - 1] - in[i] + 1);
		in[i - 1] = in[i] - 1;
	}
	printf("%d\n", res);

	return 0;
}