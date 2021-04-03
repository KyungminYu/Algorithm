#pragma GCC optimize("O2")
#include <stdio.h>
#include <malloc.h>template <class T>
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