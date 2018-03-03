#include <stdio.h>

int tri[1001], able[1501501], cnt;
int main(){
	for(cnt = 1; cnt * (cnt + 1) / 2 <= 1000; cnt++)
		tri[cnt] = cnt * (cnt + 1) / 2;
	for(int i = 1; i < cnt; i++){
		for(int j = i; j < cnt; j++){
			for(int k = j; k < cnt; k++)
				able[tri[i] + tri[j] + tri[k]] = 1;
		}
	}
	int t; scanf("%d", &t);
	while(t--){
		int k; scanf("%d", &k);
		printf("%d\n", able[k]);
	}
	return 0;
}