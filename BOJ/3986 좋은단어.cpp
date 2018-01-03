#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;

int main(){
	int n; scanf("%d", &n);
	int res = 0;
	while(n--){
		char in[100001];
		scanf("%s", in);
		int len = strlen(in);
		stack<char> s;
		for(int i = 0; i < len; i++){
			if(s.empty()) s.push(in[i]);
			else{
				if(s.top() == in[i]) s.pop();
				else s.push(in[i]);
			}
		}
		if(s.empty()) res++;
	}
	printf("%d\n", res);
	return 0;
}