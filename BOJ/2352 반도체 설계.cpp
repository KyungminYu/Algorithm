#include <stdio.h>
#define INF 1e9
int res, in[40005], idx = 0;

int _lower_bound(int*A, int s, int e, int x){
    while(s < e){  
        int mid = (s + e) / 2;
        if(A[mid] < x) s = mid + 1;
        else e = mid;
    }
    return e;
}

int main(){
	int n; scanf("%d", &n);
	in[idx++] = -INF;
	while(n--) {
		int t; scanf("%d", &t);
		if(in[idx - 1] < t){
			in[idx++] = t;
			res++;
		}
		else{
			int tidx = _lower_bound(in, 0, idx, t);
			in[tidx] = t;
		}
	}
	printf("%d\n", res);
	return 0;
}