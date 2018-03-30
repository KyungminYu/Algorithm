#include <stdio.h>
#include <string.h>

#define MAX(a, b)((a) > (b) ? (a) : (b))

char letter[51][16];
int l[51];
int know[26];
int n, k, res = 0;
void backTracking(int dep, int pos){
	if(26 < pos) return;
	if(dep == k){
		int cnt = 0;
		for(int i = 0; i < n; i++){
			int match = 0;
			for(int j = 0; j < l[i]; j++){
				if(know[letter[i][j] - 'a']) match++;
			}
			if(match == l[i]) cnt++;

		}
		res = MAX(res, cnt);
		return;
	}
	for(int i = pos; i < 26; i++){
		if(know[i]) continue;
		know[i] = 1;
		backTracking(dep + 1, i + 1);
		know[i] = 0;
	}

}
int main(){
	know[0] = know[2] = know[8] = know[13] = know[19] = 1;
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++){
		scanf("%s", letter[i]);
		int ind = 0; l[i] = strlen(letter[i]);
		for(int j = 4; j < l[i] - 4; j++)
			letter[i][j - 4] = letter[i][j];
		l[i] -= 8; 
	}
	backTracking(5, 0);
	printf("%d", res);
	return 0;
}