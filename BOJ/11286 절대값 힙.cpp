#include <stdio.h>
#include <queue>
#include <stdlib.h>
using namespace std;
int main(){
    int N, x;
    priority_queue<pair<int, int> > pq;
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &x);
        if(x){
            pq.push(make_pair(-abs(x), -x));
        }
        else{
            if(pq.empty()) printf("0\n");
            else{
                printf("%d\n", -pq.top().second);
                pq.pop();
            }
        }
    }
    return 0;
}