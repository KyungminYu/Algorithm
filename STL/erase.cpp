int _erase(int* A, int s, int e){
    int len = 0;
    A[len++] = A[s];
    for(int i = s + 1; i < e; i++){
        if(A[len - 1] == A[i]) continue;
        A[len++] = A[i]; 
    }
    return len;
}