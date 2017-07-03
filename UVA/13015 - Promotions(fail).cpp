#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

vector<int> G[5001];
vector<int> R[5001];
int visit[5001];
int dfs(vector<int> P[], int v){
	int ret = 1;
	visit[v] = 1;
	if (P[v].size() == 0)	return ret;
	for (int i = 0; i< P[v].size(); i++){
		if (visit[P[v][i]] == 0){
			ret += dfs(P, P[v][i]);
		}
	}
	return ret;
}
int main(){
	int A, B, E, P, u, v, front, back, aPossible, bPossible, bImpossible;
	scanf("%d %d %d %d", &A, &B, &E, &P);
	for (int i = 0; i < P; i++){
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
		R[v].push_back(u);
	}
	aPossible = bPossible = bImpossible = 0;
	for (int i = 0; i < E; i++){
		memset(visit, 0, sizeof(visit));
		front = dfs(G, i);
		memset(visit, 0, sizeof(visit));
		back = dfs(R, i);

		if (front > E - A) aPossible++;
		if (front > E - B) bPossible++;
		if (back > B) bImpossible++;
	}
	printf("%d\n%d\n%d\n", aPossible, bPossible, bImpossible);
	return 0;
}