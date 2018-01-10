#include <stdio.h>
#include <malloc.h>

#define ll long long

const int MAXN = 5;
const int mod = 1000;

struct matrix{
	//ll ele[MAXN][MAXN];
	ll** ele;
	int size;
	matrix(int size){
		this->size = size;
		ele = (ll**) malloc(sizeof(ll*) * size);
		for(int i = 0; i < size; i++){
			ele[i] = (ll*) malloc(sizeof(ll) * size);
			for(int j = 0; j < size; j++)
				ele[i][j] = 0;
		}
	}
	~matrix(){
		for(int i = 0; i < size; i++)
			free(ele[i]);
		free(ele);
	}
	void unit(ll val){
		for(int i = 0; i < size; i++)
			ele[i][i] = val;
	}

	ll* operator[](int idx){return ele[idx];}
	matrix operator-(matrix& A) const{
		matrix ret = *this;
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++)
				ret[i][j] -= A[i][j];
		}
		return *this;	
	}
	matrix operator+(matrix& A) const{
		matrix ret = *this;
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++)
				ret[i][j] += A[i][j];
		}
		return *this;	
	}
	matrix operator*(matrix& A) const{
		int size = A.size;
		matrix ret(size);
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				for(int k = 0; k < size; k++)
					ret[i][j] = (ret[i][j] + ele[i][k] * A[k][j]) % mod;
			}
		}
		return ret;	
	}
	matrix operator^(ll p) const{
		matrix ret(size);
		matrix base = *this;
		ret.unit(1);
		long long i = 0;
	    while(p){
	        if(p & (1LL << i)){
	            p -= (1LL << i);
	            ret = ret * base;
	        }
	        i++;
	        base = base * base;
	    }
		return ret;
	}
	void operator*=(matrix& A){*this = *this * A;}
	void operator^=(ll p){     *this = *this ^ p;}
	void operator-=(matrix& A){*this = *this - A;}
	void operator+=(matrix& A){*this = *this + A;}
};

int main(){
	int n; scanf("%d", &n);
	ll p; scanf("%lld", &p);

	matrix in(n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			scanf("%lld", &in[i][j]);
	}

    in ^= p;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) 
        	printf("%lld ", in[i][j]);
        printf("\n");
    }

	return 0;
}