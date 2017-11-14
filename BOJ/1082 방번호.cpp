#include <stdio.h>

int n, budget;
int p[11];
char res[51];
int main(){
	while(scanf("%d", &n) != EOF){
		int m = 50, midx = 0;
		for(int i = 0 ; i < n; i++){
			scanf("%d", &p[i]);
			if(p[i] <= m) {
				m = p[i];
				midx = i;
			}			
		} 
		scanf("%d", &budget);
		int ind = 0;
		while(budget >= m) {
		    res[ind++] = midx + '0';
		    budget -= m;
		}
		int s = 0;
		for(int i = 0; i < ind; i++){
			for(int j = n - 1; 0 <= j; j--){
				if(p[j] <= budget + m){
					res[i] = j + '0';
					budget += m;
					budget -= p[j];
					break;
				}
			}
			if(res[s] == '0'){
				s++;
				budget += m;
			}
		}
		printf("%s\n", s == ind ? "0" : res + s);
	}
	return 0;
}