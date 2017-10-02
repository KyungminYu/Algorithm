#pragma GCC optimize("O2")
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
string num[20];
int main(){
	std::cin.tie(0);
	std::ios::sync_with_stdio(0);
	int n; cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> num[i];
		reverse(num[i].begin(), num[i].end());
	}

	int res = 0;
	for(int i = 0; i < (1 << n); i++){
		int sum[10] = {0, };
		int cnt = 0;
		for(int j = 0; j < n; j++){
			if(i & (1 << j)){
				for(int k = 0; k < num[j].length(); k++){
					sum[k] += (num[j][k] - '0');
				}
				cnt++;
			}
		}
		for(int j = 0; j < 10; j++){
			if(sum[j] >= 10) cnt = 0;
		}
		res = max(res, cnt);	
	}
	cout << res << "\n";
	return 0;
}