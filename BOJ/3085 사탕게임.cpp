#include <stdio.h>
#include <algorithm>
using namespace std;

char map[51][51];
int n;
int dr[] = { 0, 1 };
int dc[] = { 1, 0 };
int isCan(int r, int c){ return (0 <= r && r < n && 0 <= c && c < n); }
int maxCandy(){
	int ret = 0, rcnt, ccnt; char rval, rcur, cval, ccur;
	for(int i = 0; i < n; i++){
		rval = map[i][0]; rcnt = 1;
		cval = map[0][i]; ccnt = 1;
		for(int j = 1; j < n; j++){
			rcur = map[i][j];
			ccur = map[j][i];
			if(rval == rcur) rcnt++;
			else {
				ret = max(ret, rcnt);
				rcnt = 1;
				rval = rcur;
			}
			if(cval == ccur) ccnt++;
			else {
				ret = max(ret, ccnt);
				ccnt = 1;
				cval = ccur;
			}
		}
		ret = max(ret, rcnt);
		ret = max(ret, ccnt);
	}
	return ret;
}
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%s", map[i]);
	int res = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < 2; k++){
				int r = i + dr[k], c = j + dc[k];
				if(!isCan(r, c)) continue;
				swap(map[i][j], map[r][c]);
				res = max(res, maxCandy());
				swap(map[i][j], map[r][c]);
			}		
		}
	}
	printf("%d", res);
	return 0;
}