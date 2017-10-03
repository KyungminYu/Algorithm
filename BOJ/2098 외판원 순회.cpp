#include <stdio.h>
int N;
int D[16][1 << 16];
int W[16][16];

int dsp(int u, int v){
	if (v == (1 << N) - 1) return W[u][0];
	if (D[u][v] != 0) return D[u][v];
	D[u][v] = 20000020;
	for (int i = 0; i < N; i++){
		if (v & (1 << i) || W[u][i] == 0)continue;
		D[u][v] = (D[u][v]< dsp(i, v | (1 << i)) + W[u][i]) ? D[u][v]: dsp(i, v | (1 << i)) + W[u][i];
	}
	return D[u][v];
}

int main(){
	scanf("%d", &N);
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++)
			scanf("%d", &W[i][j]);
	}
	printf("%d\n", dsp(0, 1));
	return 0;
}