#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

const long long base = 31;
const long long MOD = 1e9 + 9;

long long getHashValue(string p) {
	long long val = 0;
	for (int idx = 0; idx < p.size(); ++idx) {
		val *= base;
		val %= MOD;
		val += p[idx];
		val %= MOD;
	}
	return val;
}

string solution(vector<string> participant, vector<string> completion) {
	map<long long, string> pMap, cMap;
	long long hashValue;
	for (int idx = 0; idx < participant.size(); ++idx) {
		hashValue = getHashValue(participant[idx]);
		while(pMap.count(hashValue) > 0) {
			hashValue *= 2;
			hashValue %= MOD;
 		}
		pMap.insert(make_pair(hashValue, participant[idx]));
	}
	for (int idx = 0; idx < completion.size(); ++idx) {
		hashValue = getHashValue(completion[idx]);
		while(cMap.count(hashValue) > 0) {
			hashValue *= 2;
			hashValue %= MOD;
		}
		cMap.insert(make_pair(hashValue, completion[idx]));
	}

	map<long long, string>::iterator iter;
	for (iter = cMap.begin(); iter != cMap.end(); ++iter) {
		pMap.erase(iter -> first);
	}

	return pMap.begin()->second;
}

string solution2(vector<string> participant, vector<string> completion) {
	sort(participant.begin(), participant.end());
	sort(completion.begin(), completion.end());

	int size = completion.size();
	for (int idx = 0; idx < size; ++idx) {
		if (participant[idx] != completion[idx]) {
			return participant[idx];
		}
	}

	return participant[participant.size() - 1];
}

int main() {
	int T; cin >> T;
	while(T--) {
		vector<string> participant, completion;
		string p;
		int pCnt, cCnt; cin >> pCnt >> cCnt;
		for (int idx = 0; idx < pCnt; ++idx) {
			cin >> p;
			participant.push_back(p);
		}

		for (int idx = 0; idx < cCnt; ++idx) {
			cin >> p;
			completion.push_back(p);
		}

		cout << solution(participant, completion) << "\n";
	}

	return 0;
}