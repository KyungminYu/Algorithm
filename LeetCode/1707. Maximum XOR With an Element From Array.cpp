#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


#define MAX_BIT 31
class Solution {
public:


    struct node {
        node *open;
        node *close;
    };

    node *root = new node();
    int pows[MAX_BIT] = {1};

    void insert(int num) {
        node *current = root;
        for (int i = MAX_BIT; 0 <= i; --i) {
            if ((num >> i) & 1 == 1) {
                if (current->open == nullptr) {
                    current->open = new node();
                }
                current = current->open;
            } else {
                if (current->close == nullptr) {
                    current->close = new node();
                }
                current = current->close;
            }
        }
    }

    int query(int x, int m) {
        node *current = root;
        if (current == nullptr || (current->open == nullptr && current->close == nullptr)) {
            return -1;
        }
        int result = 0;
        for (int i = MAX_BIT; 0 <= i; --i) {
            if ((x >> i) & 1 == 1) {
                if (current->close != nullptr) {
                    current = current->close;
                    result += pows[i];
                } else {
                    current = current->open;
                }
            } else {
                if (current->open != nullptr) {
                    current = current->open;
                    result += pows[i];
                } else {
                    current = current->close;
                }
            }
        }
        return result;
    }

    std::vector<int> maximizeXor(std::vector<int>& nums, std::vector<vector<int>>& queries) {
        for (int i = 1; i < MAX_BIT; ++i) {
            pows[i] = pows[i - 1] * 2;
        }

        int querySize = queries.size();
        std::vector<std::vector<int>> q;
        for (int i = 0; i < querySize; ++i) {
            q.push_back({queries[i][1], queries[i][0], i});
        }
        sort(nums.begin(), nums.end());
        sort(q.begin(), q.end());


        std::vector<int> ret(querySize, -1);

        int numIdx = 0;
        for (std::vector<int> p : q) {
            int x = p[1];
            int m = p[0];
            int idx = p[2];
            for (; numIdx < nums.size() && nums[numIdx] <= m; ++numIdx) {
                insert(nums[numIdx]);
            }
            ret[idx] = query(x, m);
        }
        return ret;
    }
};

int main() {
    Solution s;

    std::vector<int> nums;
    nums.push_back(0);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);

    std::vector<vector<int>> queries;
    queries.push_back({3, 1});
    queries.push_back({1, 3});
    queries.push_back({5, 6});

    std::vector<int> res = s.maximizeXor(nums, queries);

    for (int i = 0; i < res.size(); ++i) {
        if (i == 0) {
            cout << "[";
        }       
        cout << res[i];
        if (i < res.size() - 1) {
            cout << ", ";
        } else {
            cout << "]" << endl;
        }
    }
    return 0;
}