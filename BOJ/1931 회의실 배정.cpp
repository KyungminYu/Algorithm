#pragma GCC optimize("O2")
#include <stdio.h>
#include <algorithm>
using namespace std;

struct range{
	int s, e;
	void read(){
		scanf("%d %d", &s, &e);
	}
	bool operator < (range r) const{
		if(this->e == r.e) 
			return this->s < r.s;
		return this->e < r.e;
	}
}r[100001];

int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) r[i].read();
	sort(r, r + n);
	int res = 1, fin = r[0].e;
	for(int i = 1; i < n; i++){
		if(fin <= r[i].s){
			res++;
			fin = r[i].e;
		}
	}
	printf("%d\n", res);
	return 0;
}