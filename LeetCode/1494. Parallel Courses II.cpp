#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define MAX_NODE 15

class Solution {
public:
    vector<int> graph[MAX_NODE];
    vector<int> dp;
    int solve(int mask, int n, int k) {
        if (mask == ((1 << n) - 1)) {
            return 0;
        } else if(dp[mask] != -1)   {
            return dp[mask];
        }
        int indeg[1 << n] = { 0 };
        for(int i = 0; i < n; ++i) {
            if(mask & (1 << i)) {
                continue;
            }
            for(auto vertex: graph[i]) {
                indeg[vertex]++;
            }
        }
        int temp = 0; 
        for(int i = 0; i < n; i++) {
            if(indeg[i] == 0 && !(mask & (1 << i))) {
                temp |= (1 << i);
            }
        }
        int j = temp;
        int cnt = countOpenBits(j); 

        int ans = n + 1; 
        if (cnt > k) {
            for(; j; j = (j - 1) & temp) {
                cnt = countOpenBits(j);  
                if(cnt != k) {
                    continue;
                }
                ans = min(ans, 1 + solve(mask|j, n, k));                   
            }
        } else {
            ans = min(ans, 1 + solve(mask|j, n, k));
        }
        return dp[mask] = ans;
    }

    int countOpenBits(int mask) {
        int cnt = 0;
        for (int i = 0; i < MAX_NODE; ++i) {
            if (mask & (1 << i)) {
                ++cnt;
            }
        }
        return cnt;
    }
    
    public:

    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        dp.assign(1 << n, -1);
        for (int i = 0; i < n; ++i) {
            graph[i].clear();
        }
        for(int i = 0; i < relations.size(); i++) {
            graph[relations[i][0] - 1].push_back(relations[i][1] - 1);
        }
        return solve(0, n, k);
    }
};

int main() {
    Solution s;

    std::vector<vector<int>> relations;
    relations.push_back({ 2, 1 });
    relations.push_back({ 3, 1 });
    relations.push_back({ 1, 4 });

    int res = s.minNumberOfSemesters(4, relations, 2);

    cout << res << endl;

    relations.clear();

    relations.push_back({ 2, 1 });
    relations.push_back({ 3, 1 });
    relations.push_back({ 4, 1 });
    relations.push_back({ 1, 5 });

    res = s.minNumberOfSemesters(5, relations, 2);

    cout << res << endl;

    return 0;
}