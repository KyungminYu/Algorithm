#include <stdio.h>
#include <algorithm>
using namespace std;
int pos[200005], n, c;

int able(int len){
	int s = pos[0], cnt = 1;
	for(int i = 1; i < n; i++){
		if(pos[i] - s >= len){
			cnt++;
			s = pos[i];
		}
	}
	return cnt >= c;
}
int main(){ 
	scanf("%d %d",  &n, &c);
	for(int i = 0; i < n; i++)
		scanf("%d", &pos[i]);
	sort(pos, pos + n);
	
	int ret = 0, low = 1, high = 1e9;
	while(low <= high){
		int mid = (low + high) / 2;
		if(able(mid)){
			ret = mid;
			low = mid + 1;
		}
		else
			high = mid - 1;
	}
	printf("%d\n", ret);


	return 0;
}