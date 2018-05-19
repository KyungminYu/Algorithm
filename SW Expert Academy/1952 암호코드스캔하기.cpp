#include <stdio.h>
const int NMAX = 2055;
const int MMAX = 505;

int decTobin[16][4];
// 7자리 비율을 볼 때 마지막 비트가 항상 1이다
// => 절대 16진수에서 0은 나오지 않음
int values[4][4][4];
char in[NMAX];
int code[NMAX][MMAX * 4];
int n, m; 
int ord = 7, odd = 0, even = 0, valid = 0;

void set_data(){ ord = 8, odd = 0, even = 0, valid = 0;}

int init(){
	values[1][0][0] = 0;	values[1][1][0] = 1;
	values[0][1][1] = 2;	values[3][0][0] = 3;
	values[0][2][1] = 4;	values[1][2][0] = 5;
	values[0][0][3] = 6;	values[2][0][1] = 7;
	values[1][0][2] = 8;	values[0][0][1] = 9;
	for(int i = 0; i < 16; i++){
		int val = i, bit = 3, ind = 0;
		while(val){
			if(val & (1 << ind)){
				val -= (1 << ind);
				decTobin[i][bit] = 1;
			}
			bit--; ind++;
		}
	}
	set_data();
}

int hexTodec(char num){
	int ret = num - '0';
	if('A' <= num && num <= 'F')
		ret = num - 'A' + 10;
	return ret;
}

int decode(int idx){
	for(int i = 0; i < m; i++){
		int dec = hexTodec(in[i]);
		for(int j = 0; j < 4; j++)
			code[idx][i * 4 + j] = decTobin[dec][j];
	}
}

int main(){
	int T; scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++){
		scanf("%d %d", &n, &m);
		init();
		for(int i = 0; i < n; i++) {
			scanf("%s", in);
			decode(i);
		}
		int res = 0;
		for(int i = 1; i < n; i++){
			for(int j = m * 4 - 1; 0 <= j; j--){
				int rate[4] = { 0, }, val[8] = {0, };
				if(code[i][j] && code[i - 1][j] == 0){
					// i, j는 1이고 i - 1, j는 0인 좌표 (i, j)
					int chkVal = 1;
					for(int k = 3; k >= 0; k--, chkVal = chkVal ? 0 : 1){
						for(;code[i][j] == chkVal; j--)	rate[k]++;
					}
					j++;
					int scale = rate[1];
					for(int k = 1; k < 4; k++) scale = scale < rate[k] ? scale : rate[k];
					for(int k = 1; k < 4; k++) rate[k] /= scale;
					for(int k = 0; k < 4; k++) rate[k]--;

					if(ord == 8) valid = values[rate[1]][rate[2]][rate[3]];
					else if(ord % 2) odd += values[rate[1]][rate[2]][rate[3]];
					else even += values[rate[1]][rate[2]][rate[3]];
					ord--;

					if(ord == 0){
						if(!((odd * 3 + even + valid) % 10)) 
							res += (odd + even + valid);
						set_data();
					}
				}
			}
		}
		printf("#%d %d\n", tc, res);
	}


	return 0;
}