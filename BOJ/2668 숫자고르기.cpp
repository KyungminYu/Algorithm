#include <stdio.h>
#include <queue>
using namespace std;
int n, in[101], indeg[101], chk[101];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &in[i]);
		indeg[in[i]]++;
	}
	queue<int> q;
	for(int i = 1; i <= n; i++){
		if(!indeg[i]) 
			q.push(i);
	}
	int cnt = n;
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		chk[cur] = 1; cnt--;
		if(!(--indeg[in[cur]]))	
			q.push(in[cur]);
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++){
		if(!chk[i]) printf("%d\n", i);
	}

	return 0;
}