///// ***** main.cpp *****
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <math.h>
#include <time.h>

#define MAX 150000
#define WORKER_BASE 10000
#define BORDER_MAX 1000000
#define NUM_OF_FACTORY 5

int factoryStart[NUM_OF_FACTORY];
int factoryEnd[NUM_OF_FACTORY];
int allocCount[NUM_OF_FACTORY];
int count[BORDER_MAX];
int workerCounter[BORDER_MAX];
int workerChain[BORDER_MAX][400];

void init(double const worker[], unsigned int alloc[]) {
	for (int idx = 0; idx < BORDER_MAX; ++idx) {
		workerCounter[idx] = 0;
		count[idx] = 0;
	}
	for (int idx = 0; idx < NUM_OF_FACTORY; ++idx) {
		factoryStart[idx] = 0;
		factoryEnd[idx] = 0;
		allocCount[idx] = 0;
	}
	for (int idx = 0; idx < MAX; ++idx) {
		alloc[idx] = -1;
		int workerPos = worker[idx] * WORKER_BASE;
		workerChain[workerPos][workerCounter[workerPos]] = idx;
		++workerCounter[workerPos];
	}
	count[0] = workerCounter[0];
	for (int idx = 1; idx < BORDER_MAX; ++idx) {
		count[idx] = count[idx - 1] + workerCounter[idx];
	}
}

void allocateAloc(unsigned int alloc[], int factoryIdx, int pos) {
	int posCount = workerCounter[pos];
	for (int idx = 0; idx < posCount; ++idx) {
		int prevFactoryIdx = alloc[workerChain[pos][idx]];
		if (prevFactoryIdx == factoryIdx) {
			continue;
		} else if (prevFactoryIdx >= 0) {
			--allocCount[prevFactoryIdx];
		}
		alloc[workerChain[pos][idx]] = factoryIdx;
		++allocCount[factoryIdx];
	}
}

void allocateAloc(unsigned int alloc[], int factoryIdx, int startPos, int endPos) {
	for (int pos = startPos; pos <= endPos; ++pos) {
		allocateAloc(alloc, factoryIdx, pos);
	}
}

void allocateFactory(double factory[], int factoryIdx, int startPos, int endPos) {
	double num = count[endPos] - count[startPos];
	double sum = 0;
	for (int pos = startPos; pos <= endPos; ++pos) {
		sum += pos * workerCounter[pos];
	}
	factory[factoryIdx] = sum / num / WORKER_BASE;
	factoryStart[factoryIdx] = startPos;
	factoryEnd[factoryIdx] = endPos;
}

void calculateAllocNFactory(double const worker[], double factory[], unsigned int alloc[]) {

	int startIdx = 0;
	int factoryIdx = 0;
	for (int idx = 0; idx < BORDER_MAX; ++idx) {
		int check = count[idx] - count[startIdx];
		if (check < 30000) {
			continue;
		}
		allocateFactory(factory, factoryIdx, startIdx, idx);
		allocateAloc(alloc, factoryIdx,startIdx, idx);
		++factoryIdx;
		startIdx = idx + 1;
	}	
	allocateFactory(factory, factoryIdx, startIdx, BORDER_MAX - 1);
	allocateAloc(alloc, factoryIdx, startIdx, BORDER_MAX - 1);
}

double getDistribution(double factory[], int factoryIdx) {
	double location = factory[factoryIdx] * WORKER_BASE;
	int startPos = factoryStart[factoryIdx];
	int endPos = factoryEnd[factoryIdx];

	return ((location - startPos) / (endPos - startPos));
}


bool isAllocChangeValid(int sourceIdx, int distIdx) {
	if (allocCount[distIdx] + workerCounter[sourceIdx] > 33000 
		|| allocCount[sourceIdx] - workerCounter[sourceIdx] < 18000) {
		return false;
	}
	return true;
}

void adjustAllocNFactory(double factory[], unsigned int alloc[], int factoryIdx) {

	double firstPos = factory[factoryIdx];
	double secondPos = factory[factoryIdx + 1];

	double firstDiff = factoryStart[factoryIdx + 1] - firstPos;
	double secondDiff = secondPos - factoryEnd[factoryIdx];

	int firstEndPos = factoryEnd[factoryIdx];

	if (firstDiff > secondDiff) {
		if (!isAllocChangeValid(factoryIdx, factoryIdx + 1)) {
			return;
		}
		allocateFactory(factory, factoryIdx, factoryStart[factoryIdx], firstEndPos - 1);
		allocateFactory(factory, factoryIdx + 1, firstEndPos, factoryEnd[factoryIdx + 1]);
		allocateAloc(alloc, factoryIdx + 1, firstEndPos);
	} else {
		if (!isAllocChangeValid(factoryIdx + 1, factoryIdx)) {
			return;
		}
		allocateFactory(factory, factoryIdx, factoryStart[factoryIdx], firstEndPos + 1);
		allocateFactory(factory, factoryIdx + 1, firstEndPos + 2, factoryEnd[factoryIdx + 1]);
		allocateAloc(alloc, factoryIdx, firstEndPos + 1);
	}			
}

void test(double const worker[], double factory[], unsigned int alloc[]) {
	init(worker, alloc);
	calculateAllocNFactory(worker, factory, alloc);
	for (int idx = 0; idx < 4000; ++idx) {
		adjustAllocNFactory(factory, alloc, idx % 5);
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