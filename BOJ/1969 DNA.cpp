#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

struct info{
	char val;
	int cnt;
	info(){}
	info(char val){	this->val = val; cnt = 0; }
	int operator < (info i) const{
		if(cnt == i.cnt) return val < i.val;
		return cnt > i.cnt;
	}
};
struct DNA{
	info infos[4] = {{'A'}, {'C'}, {'G'}, {'T'}};
}DNA[51];
char in[1001][51];
int main(){
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%s", in[i]);

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			switch(in[i][j]){
				case 'A': DNA[j].infos[0].cnt++; break;
				case 'C': DNA[j].infos[1].cnt++; break;
				case 'G': DNA[j].infos[2].cnt++; break;
				case 'T': DNA[j].infos[3].cnt++; break;
			}
		}
	}
	int diff = 0;
	for(int i = 0; i < m; i++) {
		sort(DNA[i].infos, DNA[i].infos + 4);
		printf("%c", DNA[i].infos[0].val);
		for(int j = 0; j < n; j++)
			diff += (DNA[i].infos[0].val != in[j][i]);
	}
	printf("\n%d", diff);
	return 0;
}