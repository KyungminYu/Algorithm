#include <stdio.h>

char in[31];
int cnt[26];
int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%s", in);
		cnt[in[0] - 'a']++;
	}
	int flag = 1;
	for(int i = 0; i < 26; i++){
		if(cnt[i] >= 5) {
			printf("%c", i + 'a');
			flag = 0;
		}
	}
	if(flag) printf("PREDAJA");

	return 0;
}