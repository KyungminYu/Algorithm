#include <stdio.h>
#include <string.h>\

int main(){
	int count[26] = {0, };
	char str[51];
	scanf("%s", str);
	int len = strlen(str);
	for(int i = 0; i < len; i++)	
		count[str[i] - 'A']++;
	int oddCnt = 0, oddInd = -1;
	for(int i = 0; i < 26; i++){
		if(count[i] % 2) {
			oddCnt++;
			oddInd = i;
		}
	}
	if(oddCnt > 1){
		printf("I'm Sorry Hansoo\n");
		return 0;
	} 
	for(int i = 0; i < 26; i++){
		count[i] /= 2;
		for(int j = 0; j < count[i]; j++)
			printf("%c", i + 'A');
	}
	if(oddCnt) printf("%c", oddInd + 'A');
	 
	for(int i = 25; i >= 0; i--){
		for(int j = 0; j < count[i]; j++)
			printf("%c", i + 'A');
	}
	return 0;
}