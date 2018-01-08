#include <stdio.h>

char cur[6][3][3];
char defalut[6][3][3] = {
	{{'w','w','w'},{'w','w','w'},{'w','w','w'}},
	{{'r','r','r'},{'r','r','r'},{'r','r','r'}},
	{{'y','y','y'},{'y','y','y'},{'y','y','y'}},
	{{'o','o','o'},{'o','o','o'},{'o','o','o'}},
	{{'g','g','g'},{'g','g','g'},{'g','g','g'}},
	{{'b','b','b'},{'b','b','b'},{'b','b','b'}}};
void init(){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < 3; k++)
				cur[i][j][k] = defalut[i][j][k];
		}
	}
}
void print(){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++)
			printf("%c", cur[0][i][j]);
		printf("\n");
	}
}
void CRotate(char face[3][3]){
	char tmp[2] = {face[0][0], face[0][1]};
	face[0][0] = face[2][0]; face[0][1] = face[1][0];
	face[2][0] = face[2][2]; face[1][0] = face[2][1];
	face[2][2] = face[0][2]; face[2][1] = face[1][2];
	face[0][2] = tmp[0];     face[1][2] = tmp[1];
}
void CCRotate(char face[3][3]){
	char tmp[2] = {face[0][0], face[0][1]};
	face[0][0] = face[0][2]; face[0][1] = face[1][2];
	face[0][2] = face[2][2]; face[1][2] = face[2][1];
	face[2][2] = face[2][0]; face[2][1] = face[1][0];
	face[2][0] = tmp[0];     face[1][0] = tmp[1];
}
void Cforward(){
	int tmp[3] = {cur[0][2][0], cur[0][2][1], cur[0][2][2]};
	for(int i = 0; i < 3; i++)
		cur[0][2][i] = cur[4][2][i];
	for(int i = 0; i < 3; i++)
		cur[4][2][i] = cur[2][2][2 - i];
	for(int i = 0; i < 3; i++)
		cur[2][2][i] = cur[5][2][2 - i];
	for(int i = 0; i < 3; i++)
		cur[5][2][i] = tmp[i];
	CRotate(cur[1]);
}
void CCforward(){
	int tmp[3] = {cur[0][2][0], cur[0][2][1], cur[0][2][2]};
	for(int i = 0; i < 3; i++)
		cur[0][2][i] = cur[5][2][i];
	for(int i = 0; i < 3; i++)
		cur[5][2][i] = cur[2][2][2 - i];
	for(int i = 0; i < 3; i++)
		cur[2][2][i] = cur[4][2][2 - i];
	for(int i = 0; i < 3; i++)
		cur[4][2][i] = tmp[i];
	CCRotate(cur[1]);
}
void Cbackward(){
	int tmp[3] = {cur[0][0][0], cur[0][0][1], cur[0][0][2]};
	for(int i = 0; i < 3; i++)
		cur[0][0][i] = cur[5][0][i];
	for(int i = 0; i < 3; i++)
		cur[5][0][i] = cur[2][0][2 - i];
	for(int i = 0; i < 3; i++)
		cur[2][0][i] = cur[4][0][2 - i];
	for(int i = 0; i < 3; i++)
		cur[4][0][i] = tmp[i];
	CRotate(cur[3]);
}
void CCbackward(){
	int tmp[3] = {cur[0][0][0], cur[0][0][1], cur[0][0][2]};
	for(int i = 0; i < 3; i++)
		cur[0][0][i] = cur[4][0][i];
	for(int i = 0; i < 3; i++)
		cur[4][0][i] = cur[2][0][2 - i];
	for(int i = 0; i < 3; i++)
		cur[2][0][i] = cur[5][0][2 - i];
	for(int i = 0; i < 3; i++)
		cur[5][0][i] = tmp[i];
	CCRotate(cur[3]);
}
void CLeft(){
	int tmp[3] = {cur[0][0][0], cur[0][1][0], cur[0][2][0]};
	for(int i = 0; i < 3; i++)
		cur[0][i][0] = cur[3][i][0];
	for(int i = 0; i < 3; i++)
		cur[3][i][0] = cur[2][2 - i][0];
	for(int i = 0; i < 3; i++)
		cur[2][i][0] = cur[1][2 - i][0];
	for(int i = 0; i < 3; i++)
		cur[1][i][0] = tmp[i];
	CRotate(cur[4]);
}
void CCLeft(){
	int tmp[3] = {cur[0][0][0], cur[0][1][0], cur[0][2][0]};
	for(int i = 0; i < 3; i++)
		cur[0][i][0] = cur[1][i][0];
	for(int i = 0; i < 3; i++)
		cur[1][i][0] = cur[2][2 - i][0];
	for(int i = 0; i < 3; i++)
		cur[2][i][0] = cur[3][2 - i][0];
	for(int i = 0; i < 3; i++)
		cur[3][i][0] = tmp[i];
	CCRotate(cur[4]);
}
void CRight(){
	int tmp[3] = {cur[0][0][2], cur[0][1][2], cur[0][2][2]};
	for(int i = 0; i < 3; i++)
		cur[0][i][2] = cur[1][i][2];
	for(int i = 0; i < 3; i++)
		cur[1][i][2] = cur[2][2 - i][2];
	for(int i = 0; i < 3; i++)
		cur[2][i][2] = cur[3][2 - i][2];
	for(int i = 0; i < 3; i++)
		cur[3][i][2] = tmp[i];
	CRotate(cur[5]);
}
void CCRight(){
	int tmp[3] = {cur[0][0][2], cur[0][1][2], cur[0][2][2]};
	for(int i = 0; i < 3; i++)
		cur[0][i][2] = cur[3][i][2];
	for(int i = 0; i < 3; i++)
		cur[3][i][2] = cur[2][2 - i][2];
	for(int i = 0; i < 3; i++)
		cur[2][i][2] = cur[1][2 - i][2];
	for(int i = 0; i < 3; i++)
		cur[1][i][2] = tmp[i];
	CCRotate(cur[5]);
}
void CUp(){
	int tmp[3] = {cur[1][0][0], cur[1][0][1], cur[1][0][2]};
	for(int i = 0; i < 3; i++)
		cur[1][0][i] = cur[5][2 - i][0];
	for(int i = 0; i < 3; i++)
		cur[5][i][0] = cur[3][2][i];
	for(int i = 0; i < 3; i++)
		cur[3][2][i] = cur[4][2 - i][2];
	for(int i = 0; i < 3; i++)
		cur[4][i][2] = tmp[i];
	CRotate(cur[0]);
}
void CCUp(){
	int tmp[3] = {cur[1][0][0], cur[1][0][1], cur[1][0][2]};
	for(int i = 0; i < 3; i++)
		cur[1][0][i] = cur[4][i][2];
	for(int i = 0; i < 3; i++)
		cur[4][i][2] = cur[3][2][2 - i];
	for(int i = 0; i < 3; i++)
		cur[3][2][i] = cur[5][i][0];
	for(int i = 0; i < 3; i++)
		cur[5][i][0] = tmp[2 - i];
	CCRotate(cur[0]);
}
void CDown(){
	int tmp[3] = {cur[1][2][0], cur[1][2][1], cur[1][2][2]};
	for(int i = 0; i < 3; i++)
		cur[1][2][i] = cur[4][i][0];
	for(int i = 0; i < 3; i++)
		cur[4][i][0] = cur[3][0][2 - i];
	for(int i = 0; i < 3; i++)
		cur[3][0][i] = cur[5][i][2];
	for(int i = 0; i < 3; i++)
		cur[5][i][2] = tmp[2 - i];
	CCRotate(cur[2]);
}
void CCDown(){
	int tmp[3] = {cur[1][2][0], cur[1][2][1], cur[1][2][2]};
	for(int i = 0; i < 3; i++)
		cur[1][2][i] = cur[5][2 - i][2];
	for(int i = 0; i < 3; i++)
		cur[5][i][2] = cur[3][0][i];
	for(int i = 0; i < 3; i++)
		cur[3][0][i] = cur[4][2 - i][0];
	for(int i = 0; i < 3; i++)
		cur[4][i][0] = tmp[i];
	CRotate(cur[2]);
}
int main(){
	int t; scanf("%d", &t);
	while(t--){
		init();
		int n; scanf("%d", &n);
		char in[3];
		while(n--){
			scanf("%s", in);
			if(in[0] == 'F'){
				if(in[1] == '+') Cforward();
				else CCforward();
			}
			else if(in[0] == 'B'){
				if(in[1] == '+') Cbackward();
				else CCbackward();
			}
			else if(in[0] == 'L'){
				if(in[1] == '+') CLeft();
				else CCLeft();
			}
			else if(in[0] == 'R'){
				if(in[1] == '+') CRight();
				else CCRight();
			}
			else if(in[0] == 'U'){
				if(in[1] == '+') CUp();
				else CCUp();
			}
			else{
				if(in[1] == '+') CDown();
				else CCDown();
			}
		}
		print();
	}
	return 0;
}