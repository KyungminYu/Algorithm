#include <vector>
using namespace std;
vector<int> tree;
void init(int size){
	tree.resize(size);
}
void update(int pos,int add){
    for(int i = pos; i < tree.size(); i += i&-i){
        tree[i] += add;
}
int sum(int pos){
    int ret = 0;
    for(int i = pos; i > 0; i -= i&-i){
        ret += tree[i];
    return ret;
}
int query(int l, int r){
    return sum(r) - sum(l - 1);
}