#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
private:
	int savedStart = -1;
	int saverEnd = -1;
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        sort(intervals.begin(), intervals.end());
    	for (vector<int> interval : intervals) {
    		int insertedStart = interval[0];
    		int insertedEnd = interval[1];

    		if (saverEnd < interval[0]) {
    			if (0 <= savedStart && 0 <= saverEnd) {
    				vector<int> range;
    				range.push_back(savedStart);
    				range.push_back(saverEnd);
    				result.push_back(range);
    			}
    			savedStart = interval[0];
    			saverEnd = interval[1];
    		} else {
    			if (saverEnd < insertedEnd) {
    				saverEnd = insertedEnd;
    			}
	    	}
    	}
    	if (0 <= savedStart && 0 <= saverEnd) {
			vector<int> range;
			range.push_back(savedStart);
			range.push_back(saverEnd);
			result.push_back(range);
		}
    	return result;
    }
};

int main() {
	return 0;
}