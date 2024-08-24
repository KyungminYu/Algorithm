#include <iostream>

using namespace std;

#define lld long long
#define NUM_OF_WORKER 150000
#define MAX_ALLOC 33000
#define MIN_ALLOC 18000
#define DEFAULT_ALLOC 30000
#define NUM_OF_FACTORY 5
#define WORKER_BASE 1000000

int tmpPosition[NUM_OF_WORKER];
int tmpIndex[NUM_OF_WORKER];
int position[NUM_OF_WORKER];
lld index[NUM_OF_WORKER];
lld prefixSum[NUM_OF_WORKER];

int allocRange[NUM_OF_FACTORY + 1] = { 0, 0, 0, 0, 0, NUM_OF_WORKER };
int tmpAllocRange[NUM_OF_FACTORY + 1] = { 0, 0, 0, 0, 0, NUM_OF_WORKER };

void merge(int left, int mid, int right) {
	int lIdx = left;
	int rIdx = mid + 1;

	int tmpIdx = left;

	while (lIdx <= mid && rIdx <= right) {
		if (position[lIdx] <= position[rIdx]) {
			tmpIndex[tmpIdx] = index[lIdx];
			tmpPosition[tmpIdx++] = position[lIdx++];
		}
		else {
			tmpIndex[tmpIdx] = index[rIdx];
			tmpPosition[tmpIdx++] = position[rIdx++];
		}
	}

	while (lIdx <= mid) {
		tmpIndex[tmpIdx] = index[lIdx];
		tmpPosition[tmpIdx++] = position[lIdx++];
	}

	while (rIdx <= right) {
		tmpIndex[tmpIdx] = index[rIdx];
		tmpPosition[tmpIdx++] = position[rIdx++];
	}

	for (int idx = left; idx <= right; ++idx) {
		index[idx] = tmpIndex[idx];
		position[idx] = tmpPosition[idx];
	}
}

void mergeSort(int left, int right) {
	if (right <= left) {
		return;
	}
	int mid = (left + right) / 2;
	mergeSort(left, mid);
	mergeSort(mid + 1, right);
	merge(left, mid, right);
}

int binarySearch(int left, int right, lld pos) {
	lld mid = (left + right) / 2;
	while (left <= right) {
		mid = (left + right) / 2;
		if (position[mid] == pos) {
			return mid;
		}
		else if (position[mid] < pos) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return mid;
}

lld getCost(int startIdx, int endIdx) {
	lld average = (prefixSum[endIdx] - prefixSum[startIdx]) / (double)(endIdx - startIdx + 1);
	lld averageIdx = binarySearch(startIdx, endIdx, average);
	lld lCost = average * (averageIdx - startIdx + 1) - (prefixSum[averageIdx] - prefixSum[startIdx]) - position[startIdx];
	lld rCost = (prefixSum[endIdx] - prefixSum[averageIdx]) - average * (endIdx - averageIdx);
	return lCost + rCost;
}

lld getCost(int sourceAllocRange[]) {
	double cost = 0;
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		cost += getCost(sourceAllocRange[i], sourceAllocRange[i + 1] - 1);
	}
	return cost;
}

void copyAllocRange(int sourceAllocRange[], int distAllocRange[]) {
	for (int i = 0; i <= NUM_OF_FACTORY; ++i) {
		distAllocRange[i] = sourceAllocRange[i];
	}
}

bool compareAlloc(int allocRange1[], int allocRange2[]) {
	for (int i = 0; i <= NUM_OF_FACTORY; ++i) {
		if (allocRange1[i] != allocRange2[i]) {
			return false;
		}
	}
	return true;
}

void printAlloc(const char* caller) {
	cout << "[" << caller << "]\t";
	for (int c = 0; c < 5; c++) {
		cout << allocRange[c + 1] - allocRange[c] << " ";
	}
	cout << endl;
}

void updateFactoryNAlloc(double factory[], unsigned int alloc[]) {
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		int startIdx = allocRange[i];
		int endIdx = allocRange[i + 1] - 1;
		factory[i] = (prefixSum[endIdx] - prefixSum[startIdx]) / (double)(endIdx - startIdx + 1) / WORKER_BASE;
		for (int j = startIdx; j <= endIdx; ++j) {
			alloc[index[j]] = i;
		}
	}
}

void initialize(double const worker[]) {
	for (int i = 0; i < NUM_OF_WORKER; ++i) {
		index[i] = i;
		position[i] = (lld)(worker[i] * WORKER_BASE);
	}
	mergeSort(0, NUM_OF_WORKER - 1);
	prefixSum[0] = position[0];
	for (int i = 1; i < NUM_OF_WORKER; ++i) {
		prefixSum[i] = prefixSum[i - 1] + position[i];
	}
}

void initAllocRange() {
	int step = 400;
	lld minCost = 1e15;
	for (int i = MIN_ALLOC; i <= MAX_ALLOC; i += step) {
		tmpAllocRange[1] = i;
		for (int j = NUM_OF_WORKER - MAX_ALLOC * 3; j <= i + MAX_ALLOC; j += step) {
			tmpAllocRange[2] = j;
			for (int k = NUM_OF_WORKER - MAX_ALLOC * 2; k <= j + MAX_ALLOC; k += step) {
				tmpAllocRange[3] = k;
				for (int l = NUM_OF_WORKER - MAX_ALLOC; l <= k + MAX_ALLOC; l += step) {
					tmpAllocRange[4] = l;
					lld cost = getCost(tmpAllocRange);
					if (cost < minCost) {
						minCost = cost;
						copyAllocRange(tmpAllocRange, allocRange);
					}
				}
			}
		}
	}
}

void updateAllocRange(int delta) {
	int moveIdx = -1;
	lld minCost = 1e15;

	for (int idx = 0; idx < NUM_OF_FACTORY - 1; ++idx) {
		int startIdx1 = allocRange[idx];
		int endIdx1 = allocRange[idx + 1] - 1;

		int startIdx2 = allocRange[idx + 1];
		int endIdx2 = allocRange[idx + 2] - 1;

		lld originCost = getCost(startIdx1, endIdx1) + getCost(startIdx2, endIdx2);
		lld leftCost = 1e15;
		lld rightCost = 1e15;
		if (MIN_ALLOC < endIdx1 - startIdx1 + 1 - delta && endIdx2 - startIdx2 + 1 + delta < MAX_ALLOC) {
			leftCost = getCost(startIdx1, endIdx1 - delta) + getCost(startIdx2 - delta, endIdx2);
		}
		if (MIN_ALLOC < endIdx2 - startIdx2 + 1 - delta && endIdx1 - startIdx1 + 1 + delta < MAX_ALLOC) {
			rightCost = getCost(startIdx1, endIdx1 + delta) + getCost(startIdx2 + delta, endIdx2);
		}
		if (originCost < leftCost && originCost < rightCost) {
			continue;
		}
		if (leftCost < rightCost) {
			if (leftCost < minCost) {
				minCost = leftCost;
				moveIdx = (idx + 1);
			}
		}
		else {
			if (rightCost < minCost) {
				minCost = rightCost;
				moveIdx = (idx + 1) + NUM_OF_FACTORY;
			}
		}
	}
	if (moveIdx < 0) {
		return;
	}
	if (moveIdx < NUM_OF_FACTORY) {
		allocRange[moveIdx] -= delta;
	}
	else {
		allocRange[moveIdx - NUM_OF_FACTORY] += delta;
	}

}

void test(double const worker[], double factory[], unsigned int alloc[]) {
	initialize(worker);
	initAllocRange();
	for (int idx = 0; idx < 1000; ++idx) {
		copyAllocRange(allocRange, tmpAllocRange);
		updateAllocRange(1);
		if (compareAlloc(allocRange, tmpAllocRange)) {
			break;
		}
	}
	//printAlloc("after jitter3");
	updateFactoryNAlloc(factory, alloc);
}