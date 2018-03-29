#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string dp[251];

string sumation(string s1, string s2){
	reverse(s1.begin(), s1.end());
	reverse(s2.begin(), s2.end());
	if(s1.size() < s2.size()) swap(s1, s2);
	int len = s1.size();

	for(int i = 0; i < len; i++){
		int digit = s1[i] + s2[i] - '0' * 2;
		if(digit >= 10){
			s1[i] = digit - 10 + '0';
			if(i == len - 1) s1.push_back('1');
			else s1[i + 1]++;
		} 
		else s1[i] = digit + '0';
	}
	reverse(s1.begin(), s1.end());
	return s1;
}

int main(){
	ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n; dp[0] = dp[1] = "1"; dp[2] = "3";
	for(int i = 3; i <= 250; i++)
		dp[i] = sumation(dp[i - 1], sumation(dp[i - 2], dp[i - 2])); 
	while(cin >> n)	cout << dp[n] << '\n';
	return 0;
}