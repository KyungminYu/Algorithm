#include <iostream>
#include <algorithm>
using namespace std;

int in[1000005];
int main() {
	int n; cin >> n;
	for (int i = 0; i < n; i++)
		cin >> in[i];
	sort(in, in + n);
	for (int i = 0; i < n; i++)
		cout << in[i] << "\n";
	return 0; 
}