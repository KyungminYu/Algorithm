#include <stdio.h>
#include <stack>
using namespace std;
int main(){
	int n; scanf("%d", &n);
	stack<pair<int, int> > s;
	for(int i = 1; i <= n; i++){
		int tmp; scanf("%d", &tmp);
		while(!s.empty()){
			if(s.top().first > tmp){
				printf("%d ", s.top().second);
				break;
			}
			s.pop();
		}
		if(s.empty()) printf("0 ");
		s.push({tmp, i});
	}
	return 0;
}