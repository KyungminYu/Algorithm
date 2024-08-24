#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

static unsigned long long seed = 5;
static int psuedo_rand(void) {
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

static const int MAX_TC = 1;// 0;
static const long long CUT_LINE = 3000000;
static const long long PENEALTY = 0;
static long long SCORE = 0;

static const int SPACESHIP_NUM = 10000;
static const int MAP_SIZE = 1000;
static const int MAP_MAX_HEIGHT = 125;

struct Spaceship {
    int width;
    int height;
};

int map_org[MAP_SIZE][MAP_SIZE];
int map_bak[MAP_SIZE][MAP_SIZE];
bool occupied[MAP_SIZE][MAP_SIZE];

Spaceship spaceships_org[SPACESHIP_NUM];
Spaceship spaceships_bak[SPACESHIP_NUM];
int rows[SPACESHIP_NUM];
int cols[SPACESHIP_NUM];
int dirs[SPACESHIP_NUM];

extern void init(int mMap[][MAP_SIZE], Spaceship spaceships[]);
extern void process(int rows[], int cols[], int dirs[]);

static void make_tc() {
    for (int r = 0; r < MAP_SIZE; ++r) {
        for (int c = 0; c < MAP_SIZE; ++c) {
            occupied[r][c] = false;
            map_org[r][c] = map_bak[r][c] = psuedo_rand() % MAP_MAX_HEIGHT;
        }
    }

    for (int i = 0; i < SPACESHIP_NUM; ++i) {
        rows[i] = cols[i] = dirs[i] = -1;
        spaceships_org[i].height = spaceships_bak[i].height = 2 + psuedo_rand() % 4;
        spaceships_org[i].width = spaceships_bak[i].width = 2 + psuedo_rand() % 4;
    }
}

static bool verify() {
    for (int i = 0; i < SPACESHIP_NUM; ++i) {
        if (rows[i] == -1 || cols[i] == -1 || dirs[i] == -1) {
            continue;
        }

        int y1 = rows[i], x1 = cols[i], y2, x2;

        if (dirs[i] == 0) {
            y2 = y1 + spaceships_org[i].height - 1;
            x2 = x1 + spaceships_org[i].width - 1;
        }
        else {
            y2 = y1 + spaceships_org[i].width - 1;
            x2 = x1 + spaceships_org[i].height - 1;
        }

        if (x2 >= MAP_SIZE || y2 >= MAP_SIZE) {
            return false;
        }

        int hi = MAX(MAX(MAX(map_org[y1][x1], map_org[y1][x2]), map_org[y2][x1]), map_org[y2][x2]);
        int lo = MIN(MIN(MIN(map_org[y1][x1], map_org[y1][x2]), map_org[y2][x1]), map_org[y2][x2]);

        if (hi - lo > 6) {
            return false;
        }
            

        for (int y = y1; y <= y2; y++) {
            for (int x = x1; x <= x2; x++) {
                if (occupied[y][x]) {
                    return false;
                }
                occupied[y][x] = true;
            }
        }

        SCORE += (spaceships_org[i].height * spaceships_org[i].width * MIN(spaceships_org[i].height, spaceships_org[i].width));
    }

    return true;
}

int main() {
    setbuf(stdout, NULL);

    for (int tc = 1; tc <= MAX_TC; ++tc) {
        make_tc();
        init(map_bak, spaceships_bak);
        process(rows, cols, dirs);
        if (verify() == false) {
            SCORE = PENEALTY;
            break;
        }
    }

    if (CUT_LINE < SCORE) {
        printf("PASS, score: %lls\n", SCORE);
    }
    else {
        printf("FAIL, score: %lld\n", SCORE);
    }

    return 0;
}