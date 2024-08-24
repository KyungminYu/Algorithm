//#include <iostream>
//
//using namespace std;
//
//#define rint register int
//#define lld long long int
//#define MAX 150000
//#define MAX_ALLOC 33000
//#define MIN_ALLOC 18000
//#define NUM_OF_FACTORY 5
//#define BASE 100000
//
//int ret[6] = { 0, 0, 0, 0, 0, MAX };
//int candidate[6] = {0, 0, 0, 0, 0, MAX};
//lld workerPos[MAX];
//lld sum[MAX];
//int index[MAX];
//int tmp[MAX];
//
//int step = 200;
//int update = 10;
//
//void merge(const double* worker, int l, int m, int r) {
//	rint lInd = l;
//	rint rInd = m + 1;
//	rint tInd = l;
//	while (lInd <= m && rInd <= r) {
//		if (worker[index[lInd]] < worker[index[rInd]]) {
//			tmp[tInd++] = index[lInd++];
//		}
//		else {
//			tmp[tInd++] = index[rInd++];
//		}
//	}
//	while (lInd <= m) {
//		tmp[tInd++] = index[lInd++];
//	}
//	while (rInd <= r) {
//		tmp[tInd++] = index[rInd++];
//	}
//	for (rint i = l; i <= r; ++i) {
//		index[i] = tmp[i];
//	}
//}
//
//void msort(const double* worker, int l, int r) {
//	if (r <= l) {
//		return;
//	}
//	rint m = (l + r) / 2;
//	msort(worker, l, m);
//	msort(worker, m + 1, r - 1);
//	merge(worker, l, m, r);
//}
//
//int binarySearch(lld val, int l, int r) {
//	rint m = (l + r) / 2;
//	while (l <= r) {
//		m = (l + r) / 2;
//		if (workerPos[m] == val) {
//			return m;
//		}
//		else if (workerPos[m] < val) {
//			l = m + 1;
//		}
//		else {
//			r = m - 1;
//		}
//	}
//	return m;
//}
//
////lld getCost(int factoryIdx) {
////}
//
//
//lld getCost(int l, int r) {
//	//	rint l = candidate[factoryIdx];
//	//	rint r = candidate[factoryIdx + 1] - 1;
//	//
//	//	lld average = (sum[r] - sum[l]) / (r - l + 1);
//	//	rint averageIdx = binarySearch(average, l, r);
//	//
//	//	lld lPos = workerPos[l];
//	//	lld rPos = workerPos[r];
//	//	lld lCost = average * (averageIdx - l + 1) - (sum[averageIdx] - sum[l]) - lPos;
//	//	lld rCost = (sum[r] - sum[averageIdx]) - average * (r - averageIdx);
//	//	//return lCost + rCost;
//	//	return average - lPos;
//	lld average = (sum[r] - sum[l]) / (double)(r - l + 1);
//	return (average - workerPos[l]);
//}
//
//lld getCost(int factoryIdx) {
//	return getCost(candidate[factoryIdx], candidate[factoryIdx + 1] - 1);
//}
//
//lld getCost() {
//	lld cost = 0;
//	for (rint i = 0; i < NUM_OF_FACTORY; ++i) {
//		cost += getCost(i);
//	}
//	return cost;
//}
//
//void updateCandidate(int idx) {
//	int delta = 1;
//	for (rint i = idx; i < idx + NUM_OF_FACTORY - 1; ++i) {
//		int t = i % (NUM_OF_FACTORY - 1);
//		rint l1 = ret[t];
//		rint r1 = ret[t + 1] - 1;
//		rint l2 = ret[t + 1];
//		rint r2 = ret[t + 2] - 1;
//		lld factoryPos1 = workerPos[(l1 + r1) / 2];
//		lld factoryPos2 = workerPos[(l2 + r2) / 2];
//		lld factoryMidPos = (factoryPos1, factoryPos2) / 2;
//		rint nearWorkerIdx = binarySearch(factoryMidPos, l1, r2);
//
//		if (nearWorkerIdx < r1) {
//			delta += (r1 - nearWorkerIdx);
//			if (MIN_ALLOC <= r1 - l1 + 1 - delta && r2 - l2 + 1 + delta <= MAX_ALLOC) {
//				ret[t + 1] -= delta;
//			}
//		}
//		else if (l2 < nearWorkerIdx) {
//			delta += (nearWorkerIdx - l2);
//			if (MIN_ALLOC <= r2 - l2 + 1 - delta && r1 - l1 + 1 + delta <= MAX_ALLOC) {
//				ret[t + 1] += delta;
//			}
//		}
//	}
//}
//
//void test(double const worker[], double factory[], unsigned int alloc[]) {
//	for (rint i = 0; i < NUM_OF_FACTORY; ++i) {
//		factory[i] = 0;
//	}
//	for (rint i = 0; i < MAX; ++i) {
//		index[i] = i;
//		alloc[i] = 0;
//	}
//	msort(worker, 0, MAX - 1);
//
//	for (rint i = 0; i < MAX; ++i) {
//		workerPos[i] = worker[index[i]] * BASE;
//	}
//	sum[0] = workerPos[0];
//	for (rint i = 1; i < MAX; ++i) {
//		sum[i] = sum[i - 1] + workerPos[i];
//	}
//
//	lld minCost = 1e9;
//
//	for (rint i = MIN_ALLOC; i <= MAX_ALLOC; i += step) {
//		candidate[1] = i;
//		for (rint j = MAX - MAX_ALLOC * 3; j <= i + MAX_ALLOC; j += step) {
//			candidate[2] = j;
//			for (rint k = MAX - MAX_ALLOC * 2; k <= j + MAX_ALLOC; k += step) {
//				candidate[3] = k;
//				for (rint l = MAX - MAX_ALLOC; l <= k + MAX_ALLOC; l += step) {
//					candidate[4] = l;
//
//					lld cost = getCost();
//					if (cost < minCost) {
//						//cout << minCost << " to " << cost << endl;
//						minCost = cost;
//					
//						for (rint i = 0; i <= NUM_OF_FACTORY; ++i) {
//							ret[i] = candidate[i];
//						}
//					}
//				}
//			}
//		}
//	}
//	
//	for (rint i = 0; i < update; ++i) {
//		updateCandidate(i % 5);
//	}
//
//	for (rint i = 0; i < NUM_OF_FACTORY; ++i) {
//		rint l = ret[i];
//		rint r = ret[i + 1] - 1;
//		factory[i] = (sum[r] - sum[l]) / (double)(r - l + 1) / (double)BASE;
//		for (rint j = l; j <= r; ++j) {
//			alloc[index[j]] = i;
//		}
//	}
//
//	for (rint i = 0; i < NUM_OF_FACTORY; ++i) {
//		rint l = ret[i];
//		rint r = ret[i + 1];
//		cout << r - l << " ";
//	}
//	cout << endl;
//}
//
//idx %= (NUM_OF_FACTORY - 1);
//int delta = 1;
//
//int startIdx1 = allocRange[idx];
//int endIdx1 = allocRange[idx + 1] - 1;
//
//int startIdx2 = allocRange[idx + 1];
//int endIdx2 = allocRange[idx + 2] - 1;
//
//int originalCost = getCost(startIdx1, endIdx1) + getCost(startIdx2, endIdx2);
//int moveLeftCost = getCost(startIdx1, endIdx1 - delta) + getCost(startIdx2 - delta, endIdx2);
//int moveRightCost = getCost(startIdx1, endIdx1 + delta) + getCost(startIdx2 + delta, endIdx2);
//
//if (originalCost < moveLeftCost && originalCost < moveRightCost) {
//	return;
//}
//if (moveLeftCost < moveRightCost) {
//	if (MIN_ALLOC < endIdx1 - startIdx1 + 1 - delta && endIdx2 - startIdx2 + 1 + delta < MAX_ALLOC) {
//		allocRange[idx + 1] -= delta;
//	}
//}
//else {
//	if (MIN_ALLOC < endIdx2 - startIdx2 + 1 - delta && endIdx1 - startIdx1 + 1 + delta < MAX_ALLOC) {
//		allocRange[idx + 1] += delta;
//	}
//}
//
///*lld factoryPos1 = (prefixSum[endIdx1] - prefixSum[startIdx1]) / (double)(endIdx1 - startIdx1 + 1);
//lld factoryPos2 = (prefixSum[endIdx2] - prefixSum[startIdx2]) / (double)(endIdx2 - startIdx2 + 1);
//lld factoryMidPos = (factoryPos1 + factoryPos2) / 2;
//int nearWorkerIdx = findNearWorkerIdxFromPos(0, NUM_OF_WORKER - 1, factoryMidPos);*/
//
////if (nearWorkerIdx < endIdx1) {
////	//delta += (endIdx1 - nearWorkerIdx);
////}
////else if (startIdx2 < nearWorkerIdx) {
////	//delta += (nearWorkerIdx - startIdx2);
////}
//}

#include <iostream>

using namespace std;


#define lld long long
#define NUM_OF_WORKER 150000
#define MAX_ALLOC 33000
#define MIN_ALLOC 18000
#define DEFAULT_ALLOC 30000
#define NUM_OF_FACTORY 5
#define WORKER_BASE 1000000

#define lld long long

int tmpPosition[NUM_OF_WORKER];
int tmpIndex[NUM_OF_WORKER];
int position[NUM_OF_WORKER];
lld index[NUM_OF_WORKER];
lld prefixSum[NUM_OF_WORKER];

int allocRange[NUM_OF_FACTORY + 1];
int tmpAllocRange[NUM_OF_FACTORY + 1];

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

int findNearWorkerIdxFromPos(int left, int right, lld pos) {
	if (right < 0) {
		return 0;
	}
	else if (NUM_OF_WORKER <= left) {
		return NUM_OF_WORKER - 1;
	}
	if (right <= left) {
		return left;
	}
	int mid = (left + right) / 2;
	int midPos = position[mid];
	if (midPos == pos) {
		return mid;
	}
	else if (midPos < pos) {
		return findNearWorkerIdxFromPos(mid + 1, right, pos);
	}
	else {
		return findNearWorkerIdxFromPos(left, mid - 1, pos);
	}
}

double getCost(int startIdx, int endIdx) {


	lld sPos = position[startIdx];
	lld ePos = position[endIdx];

	/*int m = (startIdx + endIdx) / 2;
	lld mPos = position[m];
	lld lCost = mPos * (m - startIdx + 1) - (prefixSum[m] - prefixSum[startIdx]) - sPos;
	lld rCost = (prefixSum[endIdx] - prefixSum[m]) - mPos * (endIdx - m);*/

	lld average = (prefixSum[endIdx] - prefixSum[startIdx]) / (double)(endIdx - startIdx + 1);
	lld averageIdx = findNearWorkerIdxFromPos(startIdx, endIdx, average);
	lld lCost = average * (averageIdx - startIdx + 1) - (prefixSum[averageIdx] - prefixSum[startIdx]) - sPos;
	lld rCost = (prefixSum[endIdx] - prefixSum[averageIdx]) - average * (endIdx - averageIdx);


	return lCost + rCost;
}

double getCost(int sourceAllocRange[], int factoryIdx) {
	int startIdx = sourceAllocRange[factoryIdx];
	int endIdx = sourceAllocRange[factoryIdx + 1] - 1;
	return getCost(startIdx, endIdx);
}

double getCost(int sourceAllocRange[]) {
	double cost = 0;
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		cost += getCost(sourceAllocRange, i);
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
	tmpAllocRange[0] = 0;
	tmpAllocRange[5] = NUM_OF_WORKER;
	for (int i = MIN_ALLOC; i <= MAX_ALLOC; i += step) {
		tmpAllocRange[1] = i;
		for (int j = NUM_OF_WORKER - MAX_ALLOC * 3; j <= i + MAX_ALLOC; j += step) {
			tmpAllocRange[2] = j;
			for (int k = NUM_OF_WORKER - MAX_ALLOC * 2; k <= j + MAX_ALLOC; k += step) {
				tmpAllocRange[3] = k;
				for (int l = NUM_OF_WORKER - MAX_ALLOC; l <= k + MAX_ALLOC; l += step) {
					tmpAllocRange[4] = l;

					double cost = getCost(tmpAllocRange);
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

	/*for (int idx = 0; idx < 2000; ++idx) {
		for (int delta = 50; 1 <= delta; --delta) {
			copyAllocRange(allocRange, tmpAllocRange);
			updateAllocRange(idx, );
			if (compareAlloc(allocRange, tmpAllocRange)) {

				printAlloc("after jitter1");
				break;
			}
		}
	}*/


	for (int idx = 0; idx < 1000; ++idx) {
		copyAllocRange(allocRange, tmpAllocRange);
		updateAllocRange(idx, idx % 10 + 1);
		updateAllocRange(idx % 10 + 1);
		if (compareAlloc(allocRange, tmpAllocRange)) {

			//printAlloc("after jitter2");
			break;
		}
	}

	//printAlloc("after jitter3");
	updateFactoryNAlloc(factory, alloc);
}