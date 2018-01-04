#include <stdio.h>
#include <algorithm>
using namespace std;
int main(){
	int n, m, k, p;
	double lv, lvSet[101] = {0,};
	scanf("%d %d %d", &n, &m, &k);
	while(m--){
		for(int i = 0; i < n; i++){
			scanf("%d %lf", &p, &lv);
			lvSet[p] = max(lvSet[p], lv);
		}
	}
	sort(lvSet + 1, lvSet + n + 1);
	double res = 0.0;
	for(int i = n; i > n - k; i--) 
		res += lvSet[i];
	printf("%.1lf", res);
	return 0;
}