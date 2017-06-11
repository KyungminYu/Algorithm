#include <stdio.h>

int func(int l, int r, int c){
	if(l == 0)
		return 0;
	int pivot = l - 1;
	int len = 1<<pivot;
	int cnt = len * len;
	if(r < len && c < len)
		return func(pivot, r, c);
	else if(r < len && len <= c)
		return cnt + func(pivot, r, c - len);
	else if(len <= r && c < len)
		return 2*cnt  + func(pivot, r - len, c);
	else 
		return 3*cnt  + func(pivot, r - len, c - len); 

}
int main(){
	int n, r, c;
	while(scanf("%d %d %d", &n, &r, &c) != EOF){
		printf("%d\n", func(n, r, c));
	}
	
	return 0;
}
