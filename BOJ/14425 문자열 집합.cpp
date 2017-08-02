#include <stdio.h>
const int nodes = 26;
const int mmax = 501;
struct Trie{
    Trie* nTrie[nodes];
    int isTerminal;
    Trie(){
        for(int i = 0; i < nodes; i++)
            nTrie[i] = NULL;
        isTerminal = 0;
    }
    ~Trie(){
        for(int i = 0; i < nodes; i++)
            if(nTrie[i] != NULL) delete nTrie[i];
    }
    void insert(char *in){
        if(*(in + 1) == '\0'){
            isTerminal = 1;
            return;
        }
        int nxt = *in - 'a';
        if(nTrie[nxt] == NULL) 
            nTrie[nxt] = new Trie;
        nTrie[nxt]->insert(in + 1);
    }
    int find(char * in){
        if(*(in + 1) == '\0') 
            return isTerminal;
        int nxt = *in - 'a';
        if(nTrie[nxt] == NULL) return 0;
        return nTrie[nxt]->find(in + 1);
    }
};

char in[mmax];
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Trie* root = new Trie;
    for(int i = 0; i < n; i++){
        scanf("%s", in);
        root->insert(in);
    }
    int ans = 0;
    for(int i = 0; i < m; i++){
        scanf("%s", in);
        if(root->find(in)) ans++;
    }
    printf("%d\n", ans);
    return 0;
}