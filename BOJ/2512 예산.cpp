#include <stdio.h>

int n, in[10005];
int budget, max, tot;

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &in[i]);
		tot += in[i];
		max = in[i] > max ? in[i] : max;
	}
	scanf("%d", &budget);
	if(tot <= budget) {
		printf("%d\n", max);
		return 0;
	}
	int s = 0, e = max, m;
	while(s <= e){
		m = (s + e) / 2;

		int sum = 0;
		for(int i = 0; i < n; i++)
			sum += (in[i] <= m ? in[i] : m);
		if(sum <=  budget) s = m + 1;
		else e = m - 1;
	}
	printf("%d\n", e);
	return 0;
}