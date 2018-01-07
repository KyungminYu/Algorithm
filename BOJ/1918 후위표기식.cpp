#include <iostream>
#include <string>
#include <stack>
using namespace std;
int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	string in; cin >> in;
	stack<char> s;
	for(char c : in){
		if('A' <= c && c <= 'Z') cout << c;
		else if(c == '(') s.push(c);
		else if(c == ')'){
			while(s.top() != '('){
				cout << s.top();
				s.pop();
			}
			s.pop();
		}
		else if(c == '*' || c == '/'){
			while(!s.empty() && (s.top() == '*' || s.top() == '/')){
				cout << s.top();
				s.pop();
			}
			s.push(c);
		}
		else{
			while(!s.empty() && s.top() != '('){
				cout << s.top();
				s.pop();
			}
			s.push(c);
		}
	}
	while(!s.empty()){
		cout << s.top();
		s.pop();
	}

	return 0;
}