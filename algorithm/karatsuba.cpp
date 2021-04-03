#include <stdio.h>
#include <malloc.h>

#define lld long long
#define MAX_LENGTH 300000
#define BASE 10

template <class T>
class _vector{
private:
    T* _elements;
    int _size, _cap;

    void init(int cap) {
        _size = 0;
        _cap = cap;
        _elements = (T*) malloc(sizeof(T) * _cap);
    }
public:
    _vector(){
        init(32);
    }

    _vector(int cap, int init_value) {
    	init(cap);
    	for (int i = 0; i < cap; ++i) {
    		push_back(init_value);
    	}
    }

    _vector(_vector<T> v, int s, int e) {
    	init(e - s + 1);
    	for (int i = s; i < e; ++i) {
    		push_back(v[i]);
    	}
    }
    
    int size(){
        return _size;
    }
    
    void resize(int ncap){
        T* tmp = (T*) malloc(sizeof(T) * ncap);
        for(int i = 0; i < _size; i++)
            _elements[i] = tmp[i];
        free(_elements);
        _elements = tmp;
        _cap = ncap;
    }
    
    void push_back(T in){
        if(_size == _cap) {
            resize(_cap * 2);
        }
        _elements[_size++] = in;
    }
    
    void pop_back(){
        if(_size == 0) {
        	return;
        }
        --_size;
    }

    T back() {
    	return _elements[_size - 1];
    }

    T& operator [] (int idx){
        return _elements[idx];
    }
};


#define abs(n) ((n < 0) ? -n : n)
#define min(a, b) ((a < b) ? a : b)

void printNum(_vector<lld>& num) {
	for (int i = num.size() - 1; 0 <= i; --i) {
		printf("%lld ", num[i]);
	}
	printf("\n");
}

void normalize(_vector<lld>& num) {
	int size = num.size();
	for (int i = 0; i < size - 1; ++i) {
		if (num[i] > BASE) {
			num[i + 1] += num[i] / BASE;
			num[i] %= BASE;
		} else if (num[i] < 0) {
			int borrow = (abs(num[i]) + (BASE - 1)) / BASE;
			num[i + 1] -= borrow;
			num[i] += borrow * BASE;
		}
	}
	while (num.size() > 1 && num.back() == 0) {
		num.pop_back();		
	}
}

_vector<lld> multiply(_vector<lld>& a, _vector<lld>& b) {
	int aLen = a.size();
	int bLen = b.size();

	_vector<lld> c(aLen + bLen, 0);
	for (int i = 0; i < aLen; ++i) {
		for (int j = 0; j < bLen; ++j) {
			c[i + j] += a[i] * b[j];
		}
	}
	normalize(c);
	return c;
}

void addTo(_vector<lld>& a, _vector<lld>& b, int k) {
	int originalALen = a.size();
	int bSize = b.size();
	if (originalALen < bSize + k) {
		a.resize(bSize + k);
	}
	a.push_back(0);

	int aSize = a.size();
	for (int i = originalALen; i < aSize; ++i) {
		a[i] = 0;
	}

	for (int i = 0; i < bSize; ++i) {
		a[i + k] += b[i];
	}

	normalize(a);
}

void subFrom(_vector<lld>& a, _vector<lld>& b) {
	int bSize = b.size();
	for (int i = 0; i < bSize; ++i) {
		a[i] -= b[i];
	}
	normalize(a);
}

_vector<lld> karatsuba(_vector<lld>& a, _vector<lld>& b) {
	int aLen = a.size(), bLen = b.size();

	if (aLen < bLen) {
		return karatsuba(b, a);
	}
	if (aLen == 0 || bLen == 0) {
		return _vector<lld>();
	}
	if (aLen <= 50) {
		return multiply(a, b);
	}
	int half = aLen / 2;

	_vector<lld> a0(a, 0, half);
	_vector<lld> a1(a, half, aLen);
	_vector<lld> b0(b, 0, min(b.size(), half));
	_vector<lld> b1(b, min(b.size(), half), bLen);
		
	_vector<lld> z2 = karatsuba(a1, b1);
	_vector<lld> z0 = karatsuba(a0, b0);
	
	addTo(a0, a1, 0);
	addTo(b0, b1, 0);
	_vector<lld> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);

	_vector<lld> ret(z2.size() + half * 2, 0);
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half * 2);
	return ret;
}