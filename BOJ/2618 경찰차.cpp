#include <stdio.h>
#include <string.h>
#define abs(a)((a) < 0 ? -(a) : (a))
#define max(a, b)((a) > (b) ? (a) : (b))
#define min(a, b)((a) < (b) ? (a) : (b))
struct point{
	int r, c, d;
	point(){}
	point(int r, int c){
		this->r = r;
		this->c = c;
	}
}p[1003];
int n, w; 
int dp[1003][1003];
int dist(point& p1, point& p2){return abs(p1.r - p2.r) + abs(p1.c - p2.c);}

int solve(int p1, int p2){
	if(p1 == w + 2 || p2 == w + 2) return 0;

	int&ret = dp[p1][p2];
	if(ret != -1) return ret;

	int nxt = max(p1, p2) + 1;
	int fp1 = solve(nxt, p2) + dist(p[nxt], p[p1]);
	int fp2 = solve(p1, nxt) + dist(p[nxt], p[p2]);
	return ret = min(fp1, fp2);
}
void track(int p1, int p2){
	if(p1 == w + 2 || p2 == w + 2) return;

	int nxt = max(p1, p2) + 1;
	int fp1 = dp[nxt][p2] + dist(p[nxt], p[p1]);
	int fp2 = dp[p1][nxt] + dist(p[nxt], p[p2]);
	if(fp1 < fp2){
		printf("1\n");
		track(nxt, p2);
	}
	else{
		printf("2\n");
		track(p1, nxt);
	}
}


int main(){
	scanf("%d %d", &n, &w);
	p[1] = {1, 1};	p[2] = {n, n};
	for(int i = 3; i <= w + 2; i++){
		int r, c; scanf("%d %d", &r, &c);
		p[i] = {r, c};
	}
	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(1, 2)); 
	track(1, 2);
	return 0;
}