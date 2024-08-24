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

extern void test(double const worker[], double factory[], unsigned int alloc[]);

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
		worker[loop++] = (double)((tmp / 3 + beta) % 100) + (myrand() % 1000000) / 1000000.0;
	}
}


int main()
{
	//freopen("input.txt", "r", stdin);

	double total_score = 0, cut = 28807978;
	double total_time = 0;
	int sd = 3;


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

		printf("[%d] ", tc);
		for (int c = 0; c < 5; c++)
		{
			printf("%d ", check[c]);
			if (check[c] > 33000) {
				score += 100000000;
			}
		}
		printf("\n");
		printf("score : %lf\n", score);

		total_score += score;
	}

	printf("\ncut : %lf\n", cut);
	printf("\ntotal score : %lf\n", total_score);
	printf("\ntotal time : %lf\n", total_time);

	if (total_score < cut) puts("PASS");
	else puts("FAIL");

	return 0;
}