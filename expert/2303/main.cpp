#include <stdio.h>
#include <time.h>

#define lld long long
#define min(a, b) (a < b ? a : b)
#define max(a, b) (a < b ? b : a)

int SCORE = 0;
int TC = 1;//00;

using namespace std;

lld unit[8] { 50000, 10000, 5000, 1000, 500, 100, 50, 10 };
lld unitWeight[8] { 1, 1, 1, 1, 1, 1, 1, 1 };
lld requiredUnit[8];

lld this_money[8];
lld priority[1000];
lld sortedIdx[1000];
bool visit[1000];

void save(int money[8]) {
	for (register int c = 0; c < 8; ++c) {
		this_money[c] = money[c];
	}
}


void initWithdraw(int result[1000][8]) {
	for (register int i = 0; i < 1000; ++i) {
		sortedIdx[i] = i;
		priority[i] = 0;
		for (register int c = 0; c < 8; ++c) {
			result[i][c] = 0;
		}
	}
}

void countRequiredUnit(int account[1000]) {
	for (register int c = 0; c < 8; ++c) {
		requiredUnit[c] = 0;
	}

	for (register int i = 0; i < 1000; ++i) {
		lld currAccount = account[i];
		for (register int c = 0; c < 8; ++c) {
			lld unitCount = currAccount / unit[c];
			requiredUnit[c] += unitCount;
			currAccount %= unit[c];
		}
	}
	lld minRequiredUnit = 1e9;
	for (register int c = 0; c < 8; ++c) {
		minRequiredUnit = min(minRequiredUnit, requiredUnit[c]);
	}

	for (register int c = 0; c < 8; ++c) {
		unitWeight[c] = requiredUnit[c] / minRequiredUnit;
	}
}

void calculatePriority(int account[1000]) {
	for (register int i = 0; i < 1000; ++i) {
		priority[i] = 0;
	}

	lld lack[8] = {0};
	lld carry[8] = {0};

	for (register int c = 0; c < 8; ++c) {
		unitWeight[c] = 1;
	}

	for (register int c = 7; c >= 0; --c) {
		lack[c] = requiredUnit[c] - (this_money[c] + carry[c]);
		if (lack[c] < 0) {
			if(c > 0) {
				carry[c - 1] = -lack[c] / (unit[c - 1] / unit[c]);
		    }
		    lack[c] = 0;
		}
	}

	for (register int i = 0; i < 1000; ++i) {
		lld currAccount = account[i];
		for (register int c = 0; c < 8; ++c) {
			lld unitCount = currAccount / unit[c];
			priority[i] += (unitCount * lack[c] * lack[c]);
			currAccount %= unit[c];
		}	
	}
}

void merge(int s, int m, int e) {
	int sIdx = s;
	int eIdx = m + 1;

	int tIdx = 0;
	int tmp[e - s + 1];
	while (sIdx <= m && eIdx <= e) {
		if (!visit[sortedIdx[sIdx]] && visit[sortedIdx[eIdx]]) {
			tmp[tIdx++] = sortedIdx[eIdx++];
		} else if (visit[sortedIdx[sIdx]] && !visit[sortedIdx[eIdx]]) {
			tmp[tIdx++] = sortedIdx[sIdx++];
		} else {
			if (priority[sortedIdx[sIdx]] <= priority[sortedIdx[eIdx]]) {
				tmp[tIdx++] = sortedIdx[sIdx++];
			} else {
				tmp[tIdx++] = sortedIdx[eIdx++];
			}
		}
	}
	while (sIdx <= m) {
		tmp[tIdx++] = sortedIdx[sIdx++];
	}
	while (eIdx <= e) {
		tmp[tIdx++] = sortedIdx[eIdx++];
	}
	for (int i = s; i <= e; ++i) {
		sortedIdx[i] = tmp[i - s];
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

void withdrawAccount(int idx, int account[1000], int result[1000][8]) {
	visit[idx] = true;
	lld currAccount = account[idx];

	for (register int c = 0; c < 8; ++c) {
		lld unitCount = currAccount / unit[c];
		if (this_money[c] < unitCount) {
			unitCount = 0;
		}
		result[idx][c] = unitCount;
		currAccount %= unit[c];
		this_money[c] -= unitCount;
	}

	if (currAccount > 0) {
		for (register int c = 0; c < 8; ++c) {
			this_money[c] += result[idx][c];
			result[idx][c] = 0;
		}
	}
	account[idx] = 0;
}

void withdraw(int account[1000], int result[1000][8]) {
	initWithdraw(result);
	for (register int i = 0; i < 1000; ++i) visit[i] = false;
	for (register int i = 0; i < 1000; ++i) {
		countRequiredUnit(account);
		calculatePriority(account);
		mergeSort(0, 999);

		withdrawAccount(sortedIdx[i], account, result);
	}

}

static int money[8];
static int _money[8];
static int account[1000];
static int _account[1000];
static int result[1000][8];

static inline int rand(void)
{
    static unsigned long long seed = 55; // This variable can be modified
    seed = 25214903917ull * seed + 11ull;
    return (seed >> 16) & 0x7fffffff;
}

int main(void)
{

    time_t start = clock();
    double totalRunTime = 0.0;
    for (int J = 0; J < TC; J++) {
        for (int i = 0; i < 8; i++) {
            money[i] = _money[i] = 500 + (rand() % 1500);
        }

        save(money);

        for (int i = 0; i < 1000; i++) {
            account[i] = _account[i] = (rand() % 10000 + 1) * 10;
        }

        withdraw(account, result);

        for (int i = 0; i < 1000; i++) {
            for (int c = 0; c < 8; c++) {
                _money[c] -= result[i][c];
            }

            for (int c = 0; c < 8; c++) {
                if (result[i][c] < 0) {
                    SCORE += 1000;
                    break;
                }
            }

            if (_account[i] != 
            	result[i][0] * 50000 + 
            	result[i][1] * 10000 + 
            	result[i][2] * 5000 + 
            	result[i][3] * 1000 + 
            	result[i][4] * 500 + 
            	result[i][5] * 100 + 
            	result[i][6] * 50 + 
            	result[i][7] * 10) {
                SCORE += 1000;
            }
        }

        if (_money[0] < 0 ||
        	_money[1] < 0 ||
        	_money[2] < 0 ||
        	_money[3] < 0 ||
        	_money[4] < 0 ||
        	_money[5] < 0 ||
        	_money[6] < 0 ||
        	_money[7] < 0) {
            SCORE += 10000000;
        }
    }

    SCORE += (clock() - start) / (CLOCKS_PER_SEC / 1000);
    if (SCORE > 282000 * TC) {
        printf("FAIL ");
    } else {
        printf("PASS ");
    }
    printf("%d\n", SCORE);
    // fflush(stdout);
    return 0;
}