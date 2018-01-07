#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;
double val[26];
char in[105];
int main(){
	int n; scanf("%d %s", &n, in);
	for(int i = 0; i < n; i++) 
		scanf("%lf", &val[i]);
	int len = strlen(in);
	stack<double> s;
	for(int i = 0; i < len; i++){
		if('A' <= in[i] && in[i] <= 'Z') 
			s.push(val[in[i] - 'A']);
		else{
			double b = s.top(); s.pop();
			double a = s.top(); s.pop();
			if(in[i] == '+') s.push(a + b);
			if(in[i] == '-') s.push(a - b);
			if(in[i] == '*') s.push(a * b);
			if(in[i] == '/') s.push(a / b);
		}
	}
	printf("%.2lf\n", s.top());
	return 0;
}