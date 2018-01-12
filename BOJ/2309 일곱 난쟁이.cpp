#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
	int h[9];
	for (int i = 0; i < 9; i++)
		scanf("%d", h + i);
	sort(h, h + 9);
	do {
		int sum = 0;
		for (int i = 0; i < 7; i++) sum += h[i];
		if (sum == 100) {
			for (int i = 0; i < 7; i++) 
				printf("%d\n", h[i]);
			return 0;
		}
	} while (next_permutation(h, h + 9));

	return 0;
}
