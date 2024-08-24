///// ***** main.cpp *****
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <math.h>
#include <time.h>


#define lld long long
#define MAX 150000
#define MAX_ALLOC 33000
#define MIN_ALLOC 18000
#define DEFAULT_ALLOC 30000
#define NUM_OF_FACTORY 5
#define WORKER_BASE 1000000

int allocStart[NUM_OF_FACTORY];
int allocEnd[NUM_OF_FACTORY];
double tmpFactory[NUM_OF_FACTORY];
int workerIdx[MAX];
lld workerPos[MAX];
lld posSum[MAX];

void merge(int left, int mid, int right){
    int lIdx = left;
    int rIdx = mid + 1;
    
    int _tempIdx = 0;
    int tempIdx[right - left + 1];
    lld tempPos[right - left + 1];
    while (lIdx <= mid && rIdx <= right) {
        if(workerPos[lIdx] <= workerPos[rIdx]) {
            tempIdx[_tempIdx] = workerIdx[lIdx];
            tempPos[_tempIdx++] = workerPos[lIdx++];
        } else {
            tempIdx[_tempIdx] = workerIdx[rIdx];
            tempPos[_tempIdx++] = workerPos[rIdx++];
        }
    }

    int idx = 0;
    if (lIdx > mid) {
        for (idx = rIdx; idx <= right; ++idx) {
            tempIdx[_tempIdx] = workerIdx[idx];
            tempPos[_tempIdx++] = workerPos[idx];
        }
    } else{
        for (idx = lIdx; idx <= mid; ++idx) {
            tempIdx[_tempIdx] = workerIdx[idx];
            tempPos[_tempIdx++] = workerPos[idx];
        }
    }

    for (idx = left; idx <= right; ++idx){
        workerIdx[idx] = tempIdx[idx - left];
        workerPos[idx] = tempPos[idx - left];
    }
}

void merge_sort(int left, int right) {
    if (right <= left) {
        return;
    }
    int mid = (left + right) / 2;
    merge_sort(left, mid);
    merge_sort(mid + 1, right);
    merge(left, mid, right);
}

int findNearWorkerIdxFromPos(int left, int right, lld pos) {
	if (right < 0) {
		return 0;
	} else if (MAX <= left) {
		return MAX - 1;
	}
	if (right <= left) {
		return left;
	}
	int mid = (left + right) / 2;
	int midPos = workerPos[mid];
	if (midPos == pos) {
		return mid;
	} else if (midPos < pos) {
		return findNearWorkerIdxFromPos(mid + 1, right, pos);
	} else {
		return findNearWorkerIdxFromPos(left, mid - 1, pos);
	}
}

void initWorkerInfo(const double worker[]) {
	for (int i = 0; i < MAX; ++i) {
		workerIdx[i] = i;
		workerPos[i] = (long) (worker[i] * WORKER_BASE);
	}
	merge_sort(0, MAX - 1);
}	

void initPosSum() {
	merge_sort(0, MAX - 1);
	posSum[0] = workerPos[0];
	for (int i = 1; i < MAX; ++i) {
		posSum[i] = posSum[i - 1] + workerPos[i];
	}
}

void initRange() {
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		allocStart[i] = i * DEFAULT_ALLOC;
		allocEnd[i] = allocStart[i] + DEFAULT_ALLOC - 1;
	}
}

double getDistribute(int startIdx, int endIdx, double startPos) {
	return (posSum[endIdx] - posSum[startIdx]) / ((double) (endIdx - startIdx + 1)) / WORKER_BASE - startPos;
}

void updateRangeFromMidValueStep(double factory[]) {
	int delta = 1;
	for (int i = 0; i < NUM_OF_FACTORY - 1; ++i) {
		posSum[allocEnd[i]] - posSum[allocStart[i]]
		// lld factoryMidPos = (factory[i] * WORKER_BASE + factory[i + 1] * WORKER_BASE ) / 2;
		// int nearWorkerIdx = findNearWorkerIdxFromPos(0, MAX - 1, factoryMidPos);
		// int allocCount1 = allocEnd[i] - allocStart[i] + 1;
		// int allocCount2 = allocEnd[i + 1] - allocStart[i + 1] + 1;
		// if (nearWorkerIdx < allocEnd[i]) {
		// 	if (MIN_ALLOC < allocCount1 - delta && allocCount2 + delta < MAX_ALLOC) {
		// 		allocEnd[i] -= delta;
		// 		allocStart[i + 1] -= delta;
		// 	}
		// } else if (allocStart[i + 1] < nearWorkerIdx) {
		// 	if (MIN_ALLOC < allocCount2 - delta && allocCount1 + delta < MAX_ALLOC) {
		// 		allocEnd[i] += delta;
		// 		allocStart[i + 1] += delta;
		// 	}
		// }
	}
}

void updateRangeFromMidValue(double factory[]) {
	int delta = 1;
	for (int i = 0; i < NUM_OF_FACTORY - 1; ++i) {
		lld factoryMidPos = (factory[i] * WORKER_BASE + factory[i + 1] * WORKER_BASE ) / 2;
		int nearWorkerIdx = findNearWorkerIdxFromPos(0, MAX - 1, factoryMidPos);
		int allocCount1 = allocEnd[i] - allocStart[i] + 1;
		int allocCount2 = allocEnd[i + 1] - allocStart[i + 1] + 1;
		if (nearWorkerIdx < allocEnd[i]) {
			delta += (allocEnd[i] - nearWorkerIdx) / 2;
			if (MIN_ALLOC < allocCount1 - delta && allocCount2 + delta < MAX_ALLOC) {
				allocEnd[i] -= delta;
				allocStart[i + 1] -= delta;
			}
		} else if (allocStart[i + 1] < nearWorkerIdx) {
			delta += (nearWorkerIdx - allocStart[i + 1]) / 2;
			if (MIN_ALLOC < allocCount2 - delta && allocCount1 + delta < MAX_ALLOC) {
				allocEnd[i] += delta;
				allocStart[i + 1] += delta;
			}
		}
	}
}


void updateRangeFromDistribute(double factory[]) {
	int delta = 1;

	for (int i = 0; i < NUM_OF_FACTORY - 1; ++i) {
		double leftOriginDistribute = getDistribute(allocStart[i], allocEnd[i], workerPos[allocStart[i]]);
		double rightOriginDistribute = getDistribute(allocStart[i + 1], allocEnd[i + 1], workerPos[allocStart[i + 1]]);
		double leftMoveDiff = getDistribute(allocStart[i], allocEnd[i] - delta, workerPos[allocStart[i]]) - leftOriginDistribute + getDistribute(allocStart[i + 1] - delta, allocEnd[i + 1], workerPos[allocStart[i + 1] - delta]) - rightOriginDistribute;
		double rightMoveDiff = getDistribute(allocStart[i], allocEnd[i] + delta, workerPos[allocStart[i]]) - leftOriginDistribute + getDistribute(allocStart[i + 1] + delta, allocEnd[i + 1], workerPos[allocStart[i + 1] + delta]) - rightOriginDistribute;

		int allocCount1 = allocEnd[i] - allocStart[i] + 1;
		int allocCount2 = allocEnd[i + 1] - allocStart[i + 1] + 1;


		if (leftMoveDiff < rightMoveDiff) {
			if (leftMoveDiff < 0) {
				if (MIN_ALLOC < allocCount1 - delta && allocCount2 + delta < MAX_ALLOC) { // left
					allocEnd[i] -= delta;
					allocStart[i + 1] -= delta;
				} else if (rightMoveDiff < 0) {
					if (MIN_ALLOC < allocCount2 - delta && allocCount1 + delta < MAX_ALLOC) { // right
						allocEnd[i] += delta;
						allocStart[i + 1] += delta;
					}
				}
			}
		} else {
			if (rightMoveDiff < 0) {
				if (MIN_ALLOC < allocCount2 - delta && allocCount1 + delta < MAX_ALLOC) { // right
					allocEnd[i] += delta;
					allocStart[i + 1] += delta;
				} else if (leftMoveDiff < 0) {
					if (MIN_ALLOC < allocCount1 - delta && allocCount2 + delta < MAX_ALLOC) { // left
						allocEnd[i] -= delta;
						allocStart[i + 1] -= delta;
					}
				}
			}
		} 
	}
}

void updateFactoryPosition(double factory[], int factoryIdx) {
	int startIdx = allocStart[factoryIdx];
	int endIdx = allocEnd[factoryIdx];
	factory[factoryIdx] = (posSum[endIdx] - posSum[startIdx]) / ((double) (endIdx - startIdx + 1)) / WORKER_BASE;
}

void updateFactoryPosition(double factory[]) {
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		updateFactoryPosition(factory, i);
	}
}

void updateWorkerAllocation(unsigned int alloc[], int factoryIdx) {
	int startIdx = allocStart[factoryIdx];
	int endIdx = allocEnd[factoryIdx];
	for (int i = startIdx; i <= endIdx; ++i) {
		alloc[workerIdx[i]] = factoryIdx;
	}
}

void updateWorkerAllocation(unsigned int alloc[]) {
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		updateWorkerAllocation(alloc, i);
	}
}

void init(double const worker[], double factory[], unsigned int alloc[]) {
	initWorkerInfo(worker);
	initPosSum();
	initRange();
	updateFactoryPosition(factory);
	updateWorkerAllocation(alloc);
}

void savePrevFactory(double factory[]) {
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		tmpFactory[i] = factory[i];
	}
}

bool isUpdateNeed(double factory[]) {
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		double posDiff = tmpFactory[i] - factory[i];
		if (0.000001 < posDiff || posDiff < -0.000001) {
			return true;
		}
	}
	return false;
}

void test(double const worker[], double factory[], unsigned int alloc[]) {
	init(worker, factory, alloc);

	for (int retry = 0; retry < 3000; ++retry) {
		savePrevFactory(factory);
		updateRangeFromMidValue(factory);
		// updateRangeFromMidValue(factory);
		// updateRangeFromDistribute(factory);
		updateFactoryPosition(factory);
		updateWorkerAllocation(alloc);
		if (!isUpdateNeed(factory)) {
			break;
		}
	}
}

static unsigned long long seed;

static unsigned short myrand(void) {
    return ((unsigned short)((seed = seed * 25214903917ULL + 11ULL) >> 16));
}

double worker[MAX]; // DO NOT MODIFY THIS
double factory[5];
unsigned int alloc[MAX];


static void build(void) {
    register int loop = 0;

    int alpha = myrand() % 100;
    int beta = myrand() % 100;

    while (loop < MAX)
    {
        int tmp = 0;

        for (int c = 0; c < 3; c++) {
            tmp += (myrand() % 100);
        }

        worker[loop++] = (double)((tmp / 3 + alpha) % 100) + (myrand() % 1000000) / 1000000.0;
        worker[loop++] = (double)((tmp / 3 + beta ) % 100) + (myrand() % 1000000) / 1000000.0;
    }
}


int main()
{
    //freopen("input.txt", "r", stdin);

    double total_score = 0, cut = 28807978;
    double total_time = 0;
    int sd = 3;

    scanf("%d", &sd);

    seed = sd;

    for (int tc = 1; tc <= 44; ++tc) {

        build();

        time_t TIME = clock();
        test(worker, factory, alloc);
        TIME = clock() - TIME;
        double score = 0;
        total_time += (double)TIME;

        for (register int c = 0; c < MAX; c++) {
            alloc[c] %= 5;
            score += fabs(factory[alloc[c]] - worker[c]);
        }

        int check[5] = { 0 };

        for (register int c = 0; c < MAX; c++) {
            check[alloc[c]]++;
        }

        for (int c = 0; c < 5; c++)
        {
            if (check[c] > 33000) {
                score += 100000000;
            }
        }

        //printf("score : %lf\n", score);

        total_score += score;
    }
    scanf("%lf", &cut);

    printf("\ncut : %lf\n", cut);

    printf("\ntotal score : %lf\n", total_score);
    printf("\ntotal time : %lf\n", total_time);

    if (total_score < cut) puts("PASS");
    else puts("FAIL");

    return 0;
}