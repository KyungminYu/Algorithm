#include <stdio.h>
#include <stack>
using namespace std;


int main(){
	int n;
	long long w, h, res, in[100001];
	stack<long long> s;
	while(scanf("%d", &n)){
		if(n == 0) break;
		for(int i = 0; i < n; i++)
			scanf("%lld", &in[i]);

		res = 0;
		for(int i = 0; i < n; i++){
			while(!s.empty() && in[i] < in[s.top()]) {
				h = in[s.top()];
				s.pop();
				w = i;
				if(!s.empty()) 
					w = (i - s.top() - 1);
				res = res > w * h ? res : w * h;				
			}
			s.push(i);
		}
		while(!s.empty()){
			h = in[s.top()];
			s.pop();
			w = n;
			if(!s.empty()) 
				w = (n - s.top() - 1);
			res = res > w * h ? res : w * h;				
		}
		printf("%lld\n", res);
	}

	return 0;
}