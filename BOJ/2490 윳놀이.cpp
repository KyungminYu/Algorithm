#include <stdio.h>
char d[5] = {'D', 'C', 'B', 'A', 'E'};
int main(){
	for(int i = 0; i < 3; i++){
		int s = 0;
		for(int j = 0; j < 4; j++){
			int t; scanf("%d", &t);
			s += t;
		}
		printf("%c\n", d[s]);
	}
	return 0;
}