#include <stdio.h>
#include <vector>
using namespace std;

/*
포인터 연산이 아니라 전체노드를 구성해 주고
인데스를 포인터처럼 이용하는 방향으로 트리를 구성 할 수도 있다는 것을 보여주기 위함

전, 후위 연산을 위해서 root들 따로 구함
scanf() != EOF는 노드의 입력 개수가 정해져 있지 않기 때문에 사용
root 부터 이진 탐색 시작하고 입력 받은 수를 이용해서
이진 탐색 트리의 규칙대로 트리를 구성해 준다. 
*/

pair<int, int> tree[1000001];
void postorder(int node){
    if (tree[node].first != 0) 
        postorder(tree[node].first);
    if (tree[node].second != 0) 
        postorder(tree[node].second);
    printf("%d\n", node);
}
int main(){
    int in, root;
    scanf("%d", &root);
    while(scanf("%d", &in) != EOF){
        int cur = root; 
        while(1) {
            if (cur < in){
                if (tree[cur].second != 0) 
                    cur = tree[cur].second;
                else {
                    tree[cur].second = in;
                    break;
                }
            }
            else{
                if (tree[cur].first != 0) 
                    cur = tree[cur].first;
                else {
                    tree[cur].first = in;
                    break;
                }
            }
        }
    }
    postorder(root);
    return 0;
}