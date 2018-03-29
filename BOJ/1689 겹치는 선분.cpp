#include <stdio.h>
#include <algorithm>
using namespace std;

#define MAX(a, b)((a) > (b) ? (a) : (b))

struct Line{
	int p, o;
	Line(){}
	void read(int o){
		scanf("%d", &p);
		this->o = o;
	}
	int operator < (Line l) const{
		if(p == l.p) return o < l.o;
		return p < l.p;
	}
} line[2000001];

int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		line[i * 2].read(1);
		line[i * 2 + 1].read(-1);
	}
	sort(line, line + 2 * n);
	int stk = 0, res = 0;
	for(int i = 0; i < 2 * n; i++){
		if(line[i].o > 0){
			stk++;
			res = MAX(res, stk);
		}
		else stk--;
	}
	printf("%d\n", res);
	return 0;
}