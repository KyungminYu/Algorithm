#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <set>
using namespace std;

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	string in; cin >> in;
	int k;     cin >> k;
	queue<string> q; q.push(in);
	while(k--){
		int size = q.size();
		set<string> chk;
		while(size--){
			string cur = q.front();
			q.pop();
			if(chk.find(cur) != chk.end())
				continue;
			chk.insert(cur);
			int len = cur.size();
			for(int i = 0; i < len - 1; i++){
				for(int j = i + 1; j < len; j++){
					if(i == 0 && cur[j] == '0') continue;
					swap(cur[i], cur[j]);
					q.push(cur);
					swap(cur[i], cur[j]);
				}
			}
		}
	}
	string res = "0";
	while(!q.empty()){
		res = max(res, q.front());
		q.pop();
	}
	cout << (res == "0" ? "-1" : res) << "\n";

	return 0;
}