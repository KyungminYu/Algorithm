#include <iostream>
using namespace std;
int go(int n, int *arr){
	int *D = new int[n+1];
	int max = 0;
	int m = 0;
	D[1] = 1;
	for (int i = 2; i <= n; i++){
		for (int j = 1; j < i; j++)
		{
			if (arr[j] < arr[i]){
				if (max < D[j])
					max = D[j];
			}
		}
		D[i] = max + 1;
		max = 0;
	}
	for (int i = 1; i <= n; i++){
		if (m < D[i])
			m = D[i];
	}
	return m;
}

int main(){
	int N, *arr;
	cin >> N;
	arr = new int[N + 1];
	for (int i = 1; i <= N; i++)
		cin >> arr[i];
	cout << go(N, arr) << endl;
	return 0;
}