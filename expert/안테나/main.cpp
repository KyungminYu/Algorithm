#include <stdio.h>
#include <string.h>

#define ABS(x) (((x)<0)?(-(x)):(x))

static unsigned long long seed = 5;
static int psuedo_rand(void)
{
	seed = seed * 25214903917ULL + 11ULL;
	return (seed >> 16) & 0x3fffffff;
}

static const int WORLD_SIZE = 50;
static const int NUM_BASE = 50;
static const int BASE_CAPACITY = 75;
static const int NUM_TERMINAL = 2'500;
static const int DIR_NUM = 10;
static const long long PENALTY = 1'000'000'000;
static const int dy[DIR_NUM] = { 1, 0, 0, 0, 0, -1, 0,  0, 0, 0 };
static const int dx[DIR_NUM] = { 0, 0, 1, 0, 0,  0, 0, -1, 0, 0 };

extern int get_distance(int y1, int x1, int y2, int x2) {
	return ABS(y2 - y1) * ABS(y2 - y1) + ABS(x2 - x1) * ABS(x2 - x1);
}

extern void init(int base_y[], int base_x[]);
extern void solve(int terminal_y[], int terminal_x[], int base_range[], int terminal_to_base[]);

static int base_y[NUM_BASE];
static int base_x[NUM_BASE];
static int orig_base_y[NUM_BASE];
static int orig_base_x[NUM_BASE];

static int base_range[NUM_BASE];
static int base_count[NUM_BASE];

static int terminal_y[NUM_TERMINAL];
static int terminal_x[NUM_TERMINAL];
static int orig_terminal_y[NUM_TERMINAL];
static int orig_terminal_x[NUM_TERMINAL];

static int terminal_move_direction[NUM_TERMINAL];
static int terminal_to_base[NUM_TERMINAL];

static long long test()
{
	long long score = 0;
	for (int b = 0; b < NUM_BASE; b++) {
		orig_base_y[b] = base_y[b] = psuedo_rand() % WORLD_SIZE;
		orig_base_x[b] = base_x[b] = psuedo_rand() % WORLD_SIZE;
	}

	init(orig_base_y, orig_base_x);

	for (register int t = 0; t < NUM_TERMINAL; t++) {
		terminal_y[t] = psuedo_rand() % WORLD_SIZE;
		terminal_x[t] = psuedo_rand() % WORLD_SIZE;
		terminal_move_direction[t] = psuedo_rand() % DIR_NUM;
	}


	for (int s = 0; s < 10; s++)
	{
		for (register int t = 0; t < NUM_TERMINAL; t++) {
			orig_terminal_y[t] = terminal_y[t];
			orig_terminal_x[t] = terminal_x[t];
		}

		solve(orig_terminal_y, orig_terminal_x, base_range, terminal_to_base);

		for (int b = 0; b < NUM_BASE; b++)
			base_count[b] = 0;

		for (int t = 0; t < NUM_TERMINAL; t++)
		{
			int b = terminal_to_base[t];
			if (b < 0 || b >= NUM_BASE)
				score += PENALTY;

			base_count[b]++;
		}

		for (int b = 0; b < NUM_BASE; b++)
		{
			if (base_count[b] > BASE_CAPACITY)
				score += PENALTY;
		}

		for (int minutes = 0; minutes < 2; minutes++)
		{
			for (int t = 0; t < NUM_TERMINAL; t++)
			{
				int dir = terminal_move_direction[t];
				if (dy[dir] == 0 && dx[dir] == 0)
					continue;

				if (terminal_y[t] + dy[dir] < 0 || terminal_x[t] + dx[dir] < 0 || terminal_y[t] + dy[dir] >= WORLD_SIZE || terminal_x[t] + dx[dir] >= WORLD_SIZE)
					dir = (dir + 5) % DIR_NUM;

				terminal_y[t] += dy[dir];
				terminal_x[t] += dx[dir];
			}

			for (register int t = 0; t < NUM_TERMINAL; t++)
			{
				int b = terminal_to_base[t];
				if (base_range[b] < get_distance(terminal_y[t], terminal_x[t], base_y[b], base_x[b])) {
					score += PENALTY;
				}
			}
		}

		for (int b = 0; b < NUM_BASE; b++)
			score += (base_range[b]);
	}
	return score;
}

int main()
{
	setbuf(stdout, NULL);
	long long total_score = 0;

	for (int tc = 0; tc < 10; ++tc)
	{
		long long this_score = test();
		total_score += this_score;
	}
	if (total_score < 500'000)
		printf("PASS\n");
	printf("SCORE: %lld\n", total_score);
	return 0;
}