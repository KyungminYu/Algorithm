#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

long long n, m;
long long t[200002],d[200002],r[200002],b[200002];
vector<pair<long long, long long> > vec;
struct FenwikTree{
    vector<long long> tree;
    void init(long long size){tree.resize(size);}
    void update(long long pos,long long add){
        for(long long i=pos;i<tree.size();i+=i&-i)
            tree[i]+=add;
    }
    long long sum(long long pos){
        long long ret=0;
        for(long long i=pos;i>0;i-=i&-i)
            ret+=tree[i];
        return ret;
    }
    long long query(long long l,long long r){ return sum(r)-sum(l-1);}
}ptree,ttree;

int main(){
    scanf("%lld %lld", &n, &m);
    ttree.init(4 * m);
    ptree.init(4 * m);
    for(long long i = 1; i <= m; i++){
        scanf("%lld", &t[i]);//여기서 세그먼트 트리 업데이트
        ttree.update(i, t[i]); ptree.update(i, 1);
        vec.push_back({t[i], -i});
    }
    for(long long i = 1; i <= n; i++){
        scanf("%lld %lld", &d[i], &r[i]);
        vec.push_back({d[i], i});
    }
    sort(vec.begin(), vec.end());
    long long L, R;
    for(long long i = 0; i < vec.size(); i++){
        long long date = vec[i].second;
        if(date > 0){
            L = 1; R = m;
            while(L <= R){
                long long mid = (L + R) / 2;
                long long tsum = ttree.query(1, mid); 
                long long psum = ptree.query(1, mid);
                if(r[date] <= tsum - psum * vec[i].first){
                    b[date] = mid;//날짜
                    R = mid - 1;
                }
                else L = mid + 1;
            }
        }
        else if(date < 0){
            //날짜 업데이트
            ttree.update(-date, -vec[i].first);
            ptree.update(-date, -1);
        }
    }
    for(long long i = 1; i <= n; i++) printf("%lld ", b[i]);
    return 0;
}