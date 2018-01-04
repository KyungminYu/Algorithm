#include <stdio.h>
int schedule[100], tab[100];
int main(){
	int n, k; 
	scanf("%d %d", &n, &k);
	for(int i = 0; i < k; i++) 
		scanf("%d", schedule + i);

	int res = 0;
	for(int i = 0; i < k; i++){
		int isUse = 0;
		for(int j = 0; j < n; j++){
			if(tab[j] != schedule[i]) continue;
			isUse = 1;
			break;
		}
		if(isUse) continue;
		for(int j = 0; j < n; j++){
			if(tab[j]) continue;
			isUse = 1;
			tab[j] = schedule[i];
			break;
		}
		if(isUse) continue;
		int swap = 0, mx = -1;	
		for(int j = 0; j < n; j++){
			int future = 0;
            for(int m = i + 1; m < k; m++){
               	if(tab[j] == schedule[m]) break;
               	future++;
            }
			if(mx < future){
				swap = j;
				mx = future;
			}
		}
		res++;
		tab[swap] = schedule[i];
	}
	printf("%d\n", res);
	return 0;
}