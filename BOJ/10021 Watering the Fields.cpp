#include <stdio.h>
#include <algorithm>
using namespace std;

const int NMAX = 2001;
struct fieldInfo{
	int s, e, len;
	bool operator < (fieldInfo field) const{
		return this->len < field.len;
	}
};
fieldInfo fields[NMAX * NMAX];
int parent[NMAX], x[NMAX], y[NMAX];
int n, c;	
int find(int u){
	if(u == parent[u]) return parent[u];
	return parent[u] = find(parent[u]);
}
void Union(int u, int v){
    u = find(u); v = find(v); 
    if (u != v) parent[v] = u;
}
int main(){
	scanf("%d %d", &n, &c);
	for(int i = 0; i <= n; i++) parent[i] = i;
	for(int i = 0; i < n; i++) scanf("%d %d", &x[i], &y[i]);
	int size = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < i; j++){
			int len = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
			if(c <= len) fields[size++] = {i, j, len};
		}
	}
	sort(fields, fields + size);
    int cst = 0, cnt = 0;
    for(int i = 0; i < size; i++){
        int c = fields[i].len;
        int u = fields[i].s;
        int v = fields[i].e;
        if(find(u) != find(v)){
            Union(u, v);
            cst += c;
            cnt++;
        }
    }
    if(cnt != n - 1) cst = -1;
    printf("%d\n", cst);
	return 0;
} 