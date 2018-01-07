#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;

char in[1000005];
int main(){
	int t; scanf("%d", &t);
	while(t--){
		scanf("%s", in);
		int len = strlen(in);
		stack<char> s1, s2;
		for(int i = 0; i < len; i++){
			if(in[i] != '<' && in[i] != '>' && in[i] != '-')
				s1.push(in[i]);
			else if(in[i] == '<' &&!s1.empty()){
				s2.push(s1.top());
				s1.pop();
			}
			else if(in[i] == '>' && !s2.empty()){
				s1.push(s2.top());
				s2.pop();
			}
			else if(in[i] == '-' && !s1.empty())
				s1.pop();
		}
		while(!s1.empty()){
			s2.push(s1.top());
			s1.pop();
		}
		while(!s2.empty()) {
			printf("%c", s2.top());
			s2.pop();
		}
		printf("\n");
	}
	return 0;
}