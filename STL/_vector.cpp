#pragma GCC optimize("O2")
#include <stdio.h>
#include <malloc.h>
template <class T>
class _vector{
private:
    T* arr;
    int n, capacity;
public:
    _vector(){
        n = 0;
        capacity = 32;
        arr = (T*)malloc(sizeof(T) * capacity);
    }
    int size(){
        return n;
    }
    void resize(int nsize){
        T* tmp = (T*) malloc(sizeof(T) * nsize);
        for(int i = 0; i < n; i++)
            arr[i] = tmp[i];
        free(arr);
        arr = tmp;
        capacity = nsize;
    }
    void push_back(T in){
        if(n == capacity) {
            resize(capacity * 2);
        }
        arr[n++] = in;
    }
    T& operator [] (int idx){
        return arr[idx];
    }
};