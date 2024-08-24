#include <iostream>

using namespace std;


#define lld long long
#define NUM_OF_WORKER 150000
#define MAX_ALLOC 33000
#define MIN_ALLOC 18000
#define NUM_OF_FACTORY 5
#define WORKER_BASE 1000000

#define lld long long
const double* workerPos;
int index[NUM_OF_WORKER];
int tmp[NUM_OF_WORKER];
int sum[NUM_OF_WORKER];
int allocRange[NUM_OF_FACTORY + 1] = { 0, 0, 0, 0, 0, NUM_OF_WORKER };
int tmpAllocRange[NUM_OF_FACTORY + 1] = { 0, 0, 0, 0, 0, NUM_OF_WORKER };
double minCostSum = 1e9;

void merge(int s, int m, int e) {
	int sIdx = s;
	int eIdx = m + 1;

	int tIdx = sIdx;
	while (sIdx <= m && eIdx <= e) {
		if (workerPos[index[sIdx]] <= workerPos[index[eIdx]]) {
			tmp[tIdx++] = index[sIdx++];
		}
		else {
			tmp[tIdx++] = index[eIdx++];
		}
	}
	while (sIdx <= m) {
		tmp[tIdx++] = index[sIdx++];
	}
	while (eIdx <= e) {
		tmp[tIdx++] = index[eIdx++];
	}
	for (int i = s; i <= e; ++i) {
		index[i] = tmp[i];
	}
}

void mergeSort(int s, int e) {
	if (e <= s) {
		return;
	}
	int m = (s + e) / 2;
	mergeSort(s, m);
	mergeSort(m + 1, e);
	merge(s, m, e);
}

double getCost(int factoryIdx) {
	// 구간합을 구해놓는 경우 합을 빠르게 구할 수 있다.
	int s = index[tmpAllocRange[factoryIdx]];
	int e = index[tmpAllocRange[factoryIdx + 1] - 1];
	int m = (s + e) / 2;
	int midPos = workerPos[index[m]]; // 중앙값을 factory 위치로 할 것이기 때문에 마지막 로직과 이부분을 통일해야한다.

	double leftCost = midPos * (m - s + 1) - (sum[m] - sum[s] - workerPos[s]);
	double rightCost = (sum[e] - sum[m + 1] - workerPos[m + 1]) - midPos * (e - m);
	return leftCost + rightCost;
}

void process() {
	double costSum = 0;
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		costSum += getCost(i);
	}

	if (costSum < minCostSum) {
		minCostSum = costSum;
		for (int i = 0; i < NUM_OF_FACTORY; ++i) {
			allocRange[i] = tmpAllocRange[i];
		}
	}
}

void test(double const worker[], double factory[], unsigned int alloc[]) {
	minCostSum = 1e9;
	workerPos = worker;
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		factory[i] = 0;
	}
	for (int i = 0; i < NUM_OF_WORKER; ++i) {
		index[i] = i;
		alloc[i] = 0;
	}
	mergeSort(0, NUM_OF_WORKER - 1);
	sum[0] = workerPos[index[0]];

	for (int i = 1; i < NUM_OF_WORKER; ++i) {
		sum[i] = sum[i - 1] + workerPos[index[i]];
	}
	int step = 200;

	for (int i = MIN_ALLOC; i <= MAX_ALLOC; i += step) { // dp 일단 할당하고, process로 확인하기
		tmpAllocRange[1] = i;
		for (int j = NUM_OF_WORKER - MAX_ALLOC * 3; j <= i + MAX_ALLOC; j += step) {
			tmpAllocRange[2] = j;
			for (int k = NUM_OF_WORKER - MAX_ALLOC * 2; k <= j + MAX_ALLOC; k += step) {
				tmpAllocRange[3] = k;
				for (int l = NUM_OF_WORKER - MAX_ALLOC; l <= k + MAX_ALLOC; l += step) {
					tmpAllocRange[4] = l;
					process();
				}
			}
		}
	}
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		int s = allocRange[i];
		int e = allocRange[i + 1] - 1;
		int m = (s + e) / 2;
		factory[i] = workerPos[index[m]]; // 중앙값
		for (int j = s; j <= e; ++j) {
			alloc[index[j]] = i;
		}
	}
}
