#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> G[123457];
vector<int> x_candi, y_candi;
int check[123457];
void del_dfs(int v, int post, int &edges){
	for(int i = 0; i < G[v].size(); i++){
		if(G[v][i] == post) continue;
		del_dfs(G[v][i], v, edges);
		if(!check[v] && check[G[v][i]]) {
			edges++;
			check[v] = 1;
		}
	}
}
void diamet_dfs(int v, int &ind, int post, int cnt, int& D){
	cnt++;
	for(int i = 0; i < G[v].size(); i++){
		if(!check[G[v][i]] || G[v][i] == post) continue;
		diamet_dfs(G[v][i], ind, v, cnt, D);
	}
	if(check[v] && D < cnt){
		ind = v;
		D = cnt;
	}
	cnt--;
}
void cani_dfs(int v, int flag, int post, int cnt, int D){
	cnt++;
	for(int i = 0; i < G[v].size(); i++){
		if(!check[G[v][i]] || G[v][i] == post) continue;
		cani_dfs(G[v][i], flag, v, cnt, D);
	}
	if(cnt == D) {
		if(flag) x_candi.push_back(v);
		else y_candi.push_back(v);
	}
	cnt--;
}
int main(){
	int N, M, u, v;
	int x, y, diameter, start, edges;
	scanf("%d %d", &N, &M);
	for(int i = 0; i < N - 1; i++){
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i = 0; i < M; i++){
		scanf("%d", &u);
		check[u] = 1;
	}
	edges = M - 1;
	del_dfs(u, -1, edges);
	diameter = -1;
	diamet_dfs(u, x, -1, -1, diameter);
	diameter = -1;
	diamet_dfs(x, y, -1, -1, diameter);
	cani_dfs(x, 1, -1, -1, diameter);
	cani_dfs(y, 0, -1, -1, diameter);
	sort(x_candi.begin(), x_candi.end());
	sort(y_candi.begin(), y_candi.end());
	start = min(N, min(x_candi[0], y_candi[0]));
	printf("%d\n%d\n", start, edges * 2 - diameter);
	return 0;
}
