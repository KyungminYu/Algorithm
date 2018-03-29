#include <stdio.h>
#include <deque>
using namespace std;
deque<int> dq;
deque<int>::iterator it;
int ans;
int main(){
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) dq.push_back(i);
	while(m--){
		int ele; scanf("%d", &ele);
		int ind = 0;
		for(it = dq.begin(); it != dq.end(); it++){
			if(*it == ele) break;
			ind++; 
		}
		int lind = ind;
		int rind = n - ind;
		if(lind < rind){
			for(int i = 0; i < lind; i++){
				dq.push_back(dq.front());
				dq.pop_front();
				ans++;
			}
			dq.pop_front();
		}
		else{

			for(int i = 0; i < rind; i++){
				dq.push_front(dq.back());
				dq.pop_back();
				ans++;
			}
			dq.pop_front();
		}
		n--;
	}
	printf("%d\n", ans);
	return 0;
}