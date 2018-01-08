#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int in[101];
int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &in[i]);
	sort(in, in + n);
	vector<int> divides;
	int val = in[n - 1] - in[0];
	divides.push_back(val);
	for(int i = 2; i * i <= val; i++){
		if(val % i == 0){
			divides.push_back(i);
			if(val / i != i)
				divides.push_back(val / i);
		}
	}
	sort(divides.begin(), divides.end());
	for(int d : divides){
		int mod = in[0] % d;
		int fin = 1;
		for(int i = 1; i < n; i++){
			if(in[i] % d != mod){
				fin = 0;
				break;
			}
		}
		if(fin) printf("%d ", d);
	}
	return 0;
}