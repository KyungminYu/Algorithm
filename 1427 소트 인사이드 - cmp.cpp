#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int cmp(char c1, char c2) { return c1 > c2;}
int main() {
	char in[11];
	cin >> in;
	int len = strlen(in);
	sort(in, in + len, cmp);
	cout << in;
	return 0; 
}