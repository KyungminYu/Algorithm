#include <stdio.h>
#include <string.h>

int main(){	
	int n, set = 1 << 20, x; 
	scanf("%d", &n);
	char order[7];
	for(int i = 0; i < n; i++){
		scanf("%s", order);
		if(order[0] == 'a' 
			&& order[1] == 'd'){
			scanf("%d", &x);
			set |= (1 << x);
		}
		else if(order[0] == 'r'){
			scanf("%d", &x);
			set &= ~(1 << x);
		}
		else if(order[0] == 'c'){
			scanf("%d", &x);
			printf("%d\n", (set & (1 << x)) ? 1 : 0);
		}
		else if(order[0] == 't'){
			scanf("%d", &x);
			set ^= (1 << x);
		}
		else if(order[0] == 'a'){
			set |= ~0;
		}
		else{
			set = 1 << 20;
		}
	}
	return 0;
}