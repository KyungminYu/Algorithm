#include <iostream>

using namespace std;


#define lld long long
#define NUM_OF_WORKER 150000
#define MAX_ALLOC 33000
#define MIN_ALLOC 18000
#define NUM_OF_FACTORY 5
#define WORKER_BASE 1000000

#define lld long long
const double *workerPos;
int index[NUM_OF_WORKER];
int sum[NUM_OF_WORKER];
int allocRange[NUM_OF_FACTORY + 1] = {0, 0, 0, 0, 0, NUM_OF_WORKER};
int tmpAllocRange[NUM_OF_FACTORY + 1] = {0, 0, 0, 0, 0, NUM_OF_WORKER};
double minCostSum = 1e9;

void merge(int s, int m, int e) {
	int sIdx = s;
	int eIdx = m + 1;

	int tIdx = 0;
	int tmp[e - s + 1];
	while (sIdx <= m && eIdx <= e) {
		if (workerPos[index[sIdx]] <= workerPos[index[eIdx]]) {
			tmp[tIdx++] = index[sIdx++];
		} else {
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
		index[i] = tmp[i - s];
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
	int s = index[tmpAllocRange[factoryIdx]];
	int e = index[tmpAllocRange[factoryIdx + 1] - 1];
	int m = (s + e) / 2;
	int midPos = workerPos[index[m]];

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

	for (int i = MIN_ALLOC; i <= MAX_ALLOC; i += 95) {
		tmpAllocRange[1] = i;
		for (int j = NUM_OF_WORKER - MAX_ALLOC * 3; j <= i + MAX_ALLOC; j += 95) {
			tmpAllocRange[2] = j;
			for (int k = NUM_OF_WORKER - MAX_ALLOC * 2; k <= j + MAX_ALLOC; k += 95) {
				tmpAllocRange[3] = k;
				for (int l = NUM_OF_WORKER - MAX_ALLOC; l <= k + MAX_ALLOC; l += 95) {
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
		factory[i] = workerPos[index[m]];
		for (int j = s; j <= e; ++j) {
			alloc[index[j]] = i;
		}
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

        cout << "[" << tc << "] ";
        for (int c = 0; c < 5; c++)
        {
        	cout << check[c] << " ";
            if (check[c] > 33000) {
                score += 100000000;
            }
        }
        cout << endl;

        printf("score : %lf\n", score);

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