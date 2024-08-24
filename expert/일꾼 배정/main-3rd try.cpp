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

int position[NUM_OF_WORKER];
lld index[NUM_OF_WORKER];
lld prefixSum[NUM_OF_WORKER];

int allocRange[NUM_OF_FACTORY + 1];

void merge(int left, int mid, int right) {
	int lIdx = left;
	int rIdx = mid + 1;

	int tmpIdx = 0;
	int tmpPosition[right - left + 1];
	int tmpIndex[right - left + 1];

	while(lIdx <= mid && rIdx <= right) {
		if (position[lIdx] <= position[rIdx]) {
			tmpIndex[tmpIdx] = index[lIdx];
			tmpPosition[tmpIdx++] = position[lIdx++];
		} else {
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
		index[idx] = tmpIndex[idx - left];
		position[idx] = tmpPosition[idx - left];
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

double getCost(int startIdx, int endIdx) {
	double average = (prefixSum[endIdx] - prefixSum[startIdx]) / (double) (endIdx - startIdx + 1);
	return (average - position[startIdx]);
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

void copyAllocRange(int sourceAllocRange[]) {
	for (int i = 0; i <= NUM_OF_FACTORY; ++i) {
		allocRange[i] = sourceAllocRange[i];
	}
}

void updateFactoryNAlloc(double factory[], unsigned int alloc[]) {
	for (int i = 0; i < NUM_OF_FACTORY; ++i) {
		int startIdx = allocRange[i];
		int endIdx = allocRange[i + 1] - 1;
		factory[i] = (prefixSum[endIdx] - prefixSum[startIdx]) / (double) (endIdx - startIdx + 1) / WORKER_BASE;
		for (int j = startIdx; j <= endIdx; ++j) {
			alloc[index[j]] = i;
		}
	}
}

void initialize(double const worker[]) {
	for (int i = 0; i < NUM_OF_WORKER; ++i) {
		index[i] = i;
		position[i] = (lld) (worker[i] * WORKER_BASE);
	}
	mergeSort(0, NUM_OF_WORKER - 1);
	prefixSum[0] = position[0];
	for (int i = 1; i < NUM_OF_WORKER; ++i) {
		prefixSum[i] = prefixSum[i - 1] + position[i];
	}
}

void initAllocRange(double factory[], unsigned int alloc[]) {
	int count = 0;
	int step = 100;

	int tmpAllocRange[6];		
	double minCost = 1e9;
	int remainAlloc = NUM_OF_WORKER - MAX_ALLOC * 4;
	tmpAllocRange[0] = 0;	
	tmpAllocRange[5] = NUM_OF_WORKER;
	for (int i = remainAlloc; i <= MAX_ALLOC; i += step) {
		remainAlloc = NUM_OF_WORKER - MAX_ALLOC * 3 - i;
		if (MAX_ALLOC < remainAlloc || remainAlloc < MIN_ALLOC) {
			continue;
		}
		tmpAllocRange[1] = i;		
		for (int j = remainAlloc; j <= MAX_ALLOC; j += step) {
			remainAlloc = NUM_OF_WORKER - MAX_ALLOC * 2 - i - j;
			if (MAX_ALLOC < remainAlloc || remainAlloc < MIN_ALLOC) {
				continue;
			}
			tmpAllocRange[2] = i + j;
			for (int k = remainAlloc; k <= MAX_ALLOC; k += step) {
				remainAlloc = NUM_OF_WORKER - MAX_ALLOC - i - j - k;
				if (MAX_ALLOC < remainAlloc || remainAlloc < MIN_ALLOC) {
					continue;
				}
				tmpAllocRange[3] = i + j + k;
				for (int l = remainAlloc; l <= MAX_ALLOC; l += step) {
					remainAlloc = NUM_OF_WORKER - (i + j + k + l);
					if (MAX_ALLOC < remainAlloc || remainAlloc < MIN_ALLOC) {
						continue;
					}	
					tmpAllocRange[4] = i + j + k + l;

					double cost = getCost(tmpAllocRange);
					if (cost < minCost) {
						minCost = cost;
						copyAllocRange(tmpAllocRange);
					}
				}
			}
		}
	}
	updateFactoryNAlloc(factory, alloc);
}

int findNearWorkerIdxFromPos(int left, int right, lld pos) {
	if (right < 0) {
		return 0;
	} else if (NUM_OF_WORKER <= left) {
		return NUM_OF_WORKER - 1;
	}
	if (right <= left) {
		return left;
	}
	int mid = (left + right) / 2;
	int midPos = position[mid];
	if (midPos == pos) {
		return mid;
	} else if (midPos < pos) {
		return findNearWorkerIdxFromPos(mid + 1, right, pos);
	} else {
		return findNearWorkerIdxFromPos(left, mid - 1, pos);
	}
}

void updateAllocRange(double factory[], unsigned int alloc[]) {
	int delta = 1;
	for (int i = 0; i < NUM_OF_FACTORY - 1; ++i) {
		lld factoryMidPos = (factory[i] * WORKER_BASE + factory[i + 1] * WORKER_BASE) / 2;
		int nearWorkerIdx = findNearWorkerIdxFromPos(0, NUM_OF_WORKER - 1, factoryMidPos);
		int startIdx1 = allocRange[i];
		int endIdx1 = allocRange[i + 1] - 1;

		int startIdx2 = allocRange[i + 1];
		int endIdx2 = allocRange[i + 2] - 1;

		if (nearWorkerIdx < endIdx1) {
			delta += (endIdx1 - nearWorkerIdx);
			if (MIN_ALLOC < endIdx1 - startIdx1 + 1 - delta && endIdx2 - startIdx2 + 1 + delta < MAX_ALLOC) {
				allocRange[i + 1] -= delta;
			}
		} else if (startIdx2 < nearWorkerIdx) {
			delta += (nearWorkerIdx - startIdx2);
			if (MIN_ALLOC < endIdx2 - startIdx2 + 1 - delta && endIdx1 - startIdx1 + 1 + delta < MAX_ALLOC) {
				allocRange[i + 1] += delta;
			}
		}
	}
	updateFactoryNAlloc(factory, alloc);
}

void printAlloc(const char *caller) {
	cout << "[" << caller << "]\t";
	for (int c = 0; c < 5; c++) {
		cout << allocRange[c + 1] - allocRange[c] << " ";
	}
	cout << endl;
}

void test(double const worker[], double factory[], unsigned int alloc[]) {
	initialize(worker);

	initAllocRange(factory, alloc);

	printAlloc("init");

	for (int update = 0; update < 50; ++update) {
		updateAllocRange(factory, alloc);
		printAlloc("test");
	}
}

///// ***** main.cpp *****
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <math.h>
#include <time.h>

#define MAX 150000

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

    for (int tc = 1; tc <= 1; ++tc) {

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

        cout << "[" << tc << "] ";
        for (int c = 0; c < 5; c++)
        {
        	cout << check[c] << " ";
            if (check[c] > 33000) {
                score += 100000000;
            }
        }
        cout << endl;

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