#include <iostream>
using namespace std;
void hanoi(int n, int from, int to){
	if(n == 1) printf("%d -> %d\n",from, to);
	else{
		int mid = 6 - from - to;			
		hanoi(n - 1, from, mid);		
		printf("%d -> %d\n", from, to);			
		hanoi(n - 1, mid, to);
	}
}
int main(int argc, char** argv){
	int T, test_case, N;
	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		cout << "Case #" << test_case+1 << endl;
		scanf("%d", &N);
		hanoi(N, 1, 3);
	}
	return 0;
}