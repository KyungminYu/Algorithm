#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
struct result{
	int n1, n2, n3;
	int s, b;
	result() {}
	void read(){
		scanf("%1d %1d %1d %d %d", 
			  &n1, &n2, &n3, &s, &b);
	}
}r[100];
int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++)
		r[i].read();

	int res = 0;
	for (int n1 = 1; n1 <= 9; n1++) {
		for (int n2 = 1; n2 <= 9; n2++) {
			for (int n3 = 1; n3 <= 9; n3++) {
				if (n1 == n2 || n2 == n3 || n1 == n3) continue;
				int chk = 1;
				for (int i = 0; i < n; i++) {
					int s = 0, b = 0;

					if (n1 == r[i].n1) s++;
					else if (n1 == r[i].n2 || n1 == r[i].n3) b++;
					if (n2 == r[i].n2) s++;
					else if (n2 == r[i].n1 || n2 == r[i].n3) b++;
					if (n3 == r[i].n3) s++;
					else if (n3 == r[i].n1 || n3 == r[i].n2) b++;

					if (s != r[i].s || b != r[i].b) {
						chk = 0;
						break;
					}
				}
				if (chk) res++;
			}
		}
	}
	printf("%d", res);

	return 0;
}