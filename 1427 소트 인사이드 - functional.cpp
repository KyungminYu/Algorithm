#include <iostream>
#include <string.h>
#include <functional>
#include <algorithm>
using namespace std;

int main() {
	char in[11];
	cin >> in;
	int len = strlen(in);
	sort(in, in + len, greater<char>());
	cout << in;
	return 0; 
}