#include <stdio.h>
const int nodes = 11;
const int mmax = 100001;
struct Trie{
    Trie* nTrie[nodes];
    int coinsident;
    Trie(){
        for(int i = 0; i < nodes; i++)
            nTrie[i] = NULL;
        coinsident = 0;
    }
    ~Trie(){
        for(int i = 0; i < nodes; i++)
            if(nTrie[i] != NULL) delete nTrie[i];
    }
    void insert(char *in){
        if(*in == '\0'){
            coinsident = 1;
            return;
        }
        int nxt = *in - '0';
        if(nTrie[nxt] == NULL) 
            nTrie[nxt] = new Trie;
        nTrie[nxt]->insert(in + 1);
    }
    int find(char * in){
        if(*in == '\0') return 0;
        if(coinsident) return 1;
        int nxt= *in - '0';
        return nTrie[nxt]->find(in + 1);
    }
};