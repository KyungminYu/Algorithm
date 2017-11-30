#include <iostream>
#include <string>
using namespace std;

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	string a, b;
	int T; cin >> T;
	for(int t = 1; t <= T; t++){
		cin >> a >> b;
		int alen = a.length(), blen = b.length();
		int cnt = 0;
		for(int i = 0; i < alen; i++){
			cnt++;
			if(a[i] == b[0]){
				int find = 1;
				for(int j = 0; j < blen; j++){
					if(a[i + j] != b[j]) {
						find = 0;
						break;
					}
				}
				if(find) i += (blen - 1);
			}
		}		

		cout << "#" << t << " " << cnt << "\n";
	}
	return 0;
}