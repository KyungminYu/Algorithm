#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

int mp[21][21], chk[21], start[11], link[11];
int n, res;
int getDiff(){
	int sind = 0, lind = 0;
	for(int i = 0; i < n; i++){
		if(chk[i]) start[sind++] = i;
		else       link[lind++] = i;
	} 
	int sStatus = 0, lStatus = 0;
	for(int i = 0; i < sind; i++){
		for(int j = i + 1; j < sind; j++)
			sStatus += (mp[start[i]][start[j]] + mp[start[j]][start[i]]);
	}
	for(int i = 0; i < lind; i++){
		for(int j = i + 1; j < lind; j++)
			lStatus += (mp[link[i]][link[j]] + mp[link[j]][link[i]]);
	}

	return abs(sStatus - lStatus);
}
void solve(int pos, int len){
	if(len == n / 2){
		res = min(res, getDiff());
		chk[pos] = 0;
		return;
	}
	for(int i = pos + 1; i < n; i++){
		if(chk[i]) continue;
		chk[i] = 1;
		solve(i, len + 1);
	}
	chk[pos] = 0;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &mp[i][j]);
	}
	res = 1e9;
	solve(0, 0);
	printf("%d\n", res);
	return 0;
}