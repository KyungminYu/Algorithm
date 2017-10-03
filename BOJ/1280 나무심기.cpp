#include <stdio.h>
#include <vector>
using namespace std;
const long long MOD = 1e9 + 7;
const long long NMAX = 200005;
struct Fenwik{
	vector<long long> tree;
	void init(int size){
		tree.resize(size);
	}
	void update(int pos,int add){
	    for(int i = pos; i < tree.size(); i += i&-i) 
	        tree[i] += add;
	}
	long long sum(int pos){
	    long long ret = 0;
	    for(long long i = pos; i > 0; i -= i&-i)
	        ret += tree[i];
	    return ret;
	}
	long long query(int l, int r){
    	return sum(r) - sum(l - 1);
	}
}pos, cnt;
int main(){
	int n; scanf("%d", &n);
	pos.init(NMAX);
	cnt.init(NMAX);
	long long ans = 1;
	for(int i = 0; i < n; i++){
		int p; scanf("%d", &p);
		p++;
		if(i != 0) {
			ans *= (((cnt.query(0, p - 1) * p - pos.query(0, p - 1))
				+ (pos.query(p + 1, NMAX) - cnt.query(p + 1, NMAX) * p)) % MOD);
			ans %= MOD;
		}
		pos.update(p, p);
		cnt.update(p, 1);

	}
	printf("%lld\n", ans);
	return 0;
}