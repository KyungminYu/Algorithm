#include <stdio.h>
int M[65][65];
void func(int n, int ix, int iy) {
	int flag = 0;
	int base = M[ix][iy];
	for (int i = ix; i < ix + n; i++) {
		for (int j = iy; j < iy + n; j++) {
			if (base != M[i][j])
				flag = 1;
		}
	}
	if (!flag)
		printf("%d", base);
	else {
		printf("(");
		func(n / 2, ix, iy);
		func(n / 2, ix, iy + n / 2);
		func(n / 2, ix + n / 2, iy);
		func(n / 2, ix + n / 2, iy +n / 2);
		printf(")");
	}
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)scanf("%1d", &M[i][j]);
	
	func(n, 1, 1);
	return 0;
}