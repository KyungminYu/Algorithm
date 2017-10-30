#include <stdio.h>
#include <algorithm>
using namespace std;
int schedule[12], cost[4];
int range[] = { 1, 1, 3, 12 };
void solve(int mon, int price, int &ans){
	if(mon >= 12){
		ans = min(ans, price);
		return;
	}
	for(int i = 0; i < 4; i++){
		if(i == 0) solve(mon + range[i], price + cost[i] * schedule[mon], ans);
		else solve(mon + range[i], price + cost[i], ans);
	}
}

int main(){
	int T; scanf("%d", &T);
	for(int t = 1; t <= T; t++){
		for(int i = 0; i < 4; i++)
			scanf("%d", &cost[i]);
		for(int i = 0; i < 12; i++)
			scanf("%d", &schedule[i]);
		int ans = 0x3f3f3f;
		solve(0, 0, ans);
		printf("#%d %d\n", t, ans);
	}

	return 0;
}