#include <stdio.h>
#include <algorithm>
using namespace std;
int main(){
	int n, l; 
	scanf("%d %d", &n, &l);
	int leak[1001];
	for(int i = 0; i < n; i++)
		scanf("%d", leak + i);
	sort(leak, leak + n);
	int cnt = 0, s = -1005;
	for(int i = 0; i < n; i++){
		if(leak[i] - s < l) continue;
		s = leak[i];
		cnt++;
	}
	printf("%d\n", cnt);
	return 0;
}