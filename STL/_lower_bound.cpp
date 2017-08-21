int _lower_bound(int*A, int s, int e, int x){
    while(s < e){  
        int mid = (s + e) / 2;
        if(A[mid] < x) s = mid + 1;
        else e = mid;
    }
    return e;
}