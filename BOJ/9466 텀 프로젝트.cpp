#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
using namespace std;

int G[100001];
int visit[100001];
int post[100001];
int cycle[100001];
stack<int> st;
int find;
void dfs(int v){
	if(find) return;
	visit[v] = 1;
	st.push(v);
	if(!visit[G[v]])
		dfs(G[v]);
	else{
		if(!post[G[v]]){
			cycle[G[v]] = 1;
			while(st.top() != G[v]){
				cycle[st.top()] = 1;
				st.pop();
				find = 1;			
			}	
		}
	}
	post[v] = 1;
}
int main(){
	int T;
	scanf("%d", &T);
	while(T-- > 0){
		int N, u, cnt = 0;
		scanf("%d", &N);
		for(int i = 1; i <= N; i++){
			scanf("%d", &G[i]);
			visit[i] = 0;
			post[i] = 0;
			cycle[i] = 0;
		}	

		for(int i = 1; i <= N; i++){
			if(!visit[i]) {
				find = 0;
				dfs(i);
				while(!st.empty()) st.pop();
			}
		}
		for (int i = 1; i <= N; i++)
			if(!cycle[i]) cnt++;
		printf("%d\n", cnt);
	}
	return 0;
}