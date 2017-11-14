#include <stdio.h>
#include <string.h>

char nums[16][51];
int n, k, len[16], multi[51];
long long val[16], dp[1 << 15][100];

long long gcd(long long u, long long v){
	while(v){
		long long tmp = u % v;
		u = v;
		v = tmp;
	}
	return u;
}
long long solve(int used, int r){
	long long &ret = dp[used][r];
	if(ret != -1) return ret;
	if(used == (1 << n) - 1) return ret = !r;
	ret = 0;
	for(int i = 0; i < n; i++){
		if(used & (1 << i)) continue;
		long long tr = (r * multi[len[i]] + val[i]) % k;
		ret += solve(used | (1 << i), tr);
	}
	return ret;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%s", nums[i]);
		len[i] = strlen(nums[i]);
	}
	scanf("%d", &k);

	for(int i = 0; i < n; i++){
		for(int j = 0; j < len[i]; j++)
			val[i] = (val[i] * 10 + (nums[i][j] - '0')) % k;
	}

	multi[0] = 1;
	for(int i = 1; i <= 50; i++)
		multi[i] = (multi[i - 1] * 10) % k;

	memset(dp, -1, sizeof(dp));

	long long cases = solve(0, 0);
	if(cases == 0) {
		printf("0/1\n");
		return 0;
	}

	long long total = 1;
	for(int i = 2; i <= n; i++) total *= i;
	long long GCD = gcd(total, cases);
	printf("%lld/%lld\n", cases / GCD, total / GCD);
	return 0;
}