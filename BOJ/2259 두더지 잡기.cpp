#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

const int NMAX = 6667;
struct mole{
	int x, y, t;
	mole(){x = y = t = 0;};
	void read(){ scanf("%d %d %d", &x, &y, &t);	}
	int operator < (mole m) const{
 		if(t == m.t) {
			if(x == m.x) return y < m.y;
			return x < m.x;
		}
		return t < m.t;
	}
} M[NMAX];
int n, s;
// dp[i] = i 번째 두더지 이후로 잡을 수 있는 최대의 두더지 수
int dp[NMAX];
inline int pow(int n){return n * n;}
inline int isCan(int from, int to){
	int dx = pow(M[from].x - M[to].x);
	int dy = pow(M[from].y - M[to].y);
	int dt = M[to].t - M[from].t;
	return (sqrt(dx + dy) <= s * dt);
}
int solve(int p){
	int& ret = dp[p];
	if(ret != -1) return ret;
	ret = 0;
	for(int i = p + 1; i <= n; i++){
		if(isCan(p, i)) ret = max(ret, solve(i) + 1);	
	}
	return ret;
}

int main(){
	scanf("%d %d", &n, &s);
	for(int i = 1; i <= n; i++) M[i].read();
	sort(M, M + n + 1);
	for(int i = 0; i <= n; i++) dp[i] = -1;
	printf("%d", solve(0));
	return 0;
}