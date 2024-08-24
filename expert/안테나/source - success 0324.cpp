#include <stdio.h>
#include <malloc.h>

#define ABS(x) (((x) < 0) ? (-(x)) : (x))

struct Coordinates {
    int y, x;

    Coordinates() { y = x = 0; }

    Coordinates(int _y, int _x) {
        y = _y;
        x = _x;
    }

    int operator-(Coordinates& param) {
        return ABS(y - param.y) + ABS(x - param.x);
    }
};

static const int MAP_SIZE = 100;
static const int ANTENNA_NUM = 150;
static const int ANTENNA_CAPA = 100;
static const int UE_NUM = 10'000;
static const int MAX_EXPECTED_POS_COUNT = 21;
static const int MOVEMENT_COUNT = 5;
static const int DIR_NUM = 4;
static const int DIR_NONE = -1;
static const int DIR_UP = 0;
static const int DIR_LEFT = 1;
static const int DIR_DOWN = 2;
static const int DIR_RIGHT = 3;

static const int dy[DIR_NUM] = { -1, 0, 1, 0 };
static const int dx[DIR_NUM] = { 0, -1, 0, 1 };

int subTaskCount;
Coordinates* ats;
int atAllocCount[ANTENNA_NUM];
int ueDirs[UE_NUM];
int ueIdxs[UE_NUM];
Coordinates initialUEs[UE_NUM];
Coordinates expectedPos[UE_NUM][MAX_EXPECTED_POS_COUNT];
int expectedPosCount[UE_NUM];

void init(Coordinates antenna_list[]) {
    subTaskCount = 0;
    ats = antenna_list;
    for (register int uIdx = 0; uIdx < UE_NUM; ++uIdx) {
        ueDirs[uIdx] = DIR_NONE;
    }
}

bool isValid(int y, int x) {
    return 0 <= y && y < MAP_SIZE && 0 <= x && x < MAP_SIZE;
}

void checkUEDirs(Coordinates UE_list[]) {
    if (subTaskCount != 2) {
        return;
    }
    for (register int uIdx = 0; uIdx < UE_NUM; ++uIdx) {
        if (initialUEs[uIdx] - UE_list[uIdx] == 0) {
            continue;
        }
        for (register int d = 0; d < 4; ++d) {
            int dir = d;
            Coordinates pos = initialUEs[uIdx];
            for (register int minute = 0; minute < MOVEMENT_COUNT; ++minute) {
                int ny = pos.y + dy[dir];
                int nx = pos.x + dx[dir];
                if (!isValid(ny, nx)) {
                    dir = (dir + 2) % DIR_NUM;
                    ny = pos.y + dy[dir];
                    nx = pos.x + dx[dir];
                }
                pos.y = ny;
                pos.x = nx;
            }
            if (pos - UE_list[uIdx] == 0) {
                ueDirs[uIdx] = dir;
                break;
            }
        }
    }
}

void checkExpectedPos(Coordinates UE_list[]) {
    for (register int uIdx = 0; uIdx < UE_NUM; ++uIdx) {
        expectedPosCount[uIdx] = 0;
        expectedPos[uIdx][expectedPosCount[uIdx]++] = UE_list[uIdx];
        if (subTaskCount == 1) {
            // 4방향 이동 다 체크
            for (register int dir = 0; dir < DIR_NUM; ++dir) {
                for (register int minute = 1; minute < MOVEMENT_COUNT; ++minute) {
                    Coordinates pos = expectedPos[uIdx][0];
                    pos.y += dy[dir] * minute;
                    pos.x += dx[dir] * minute;
                    if (!isValid(pos.y, pos.x)) {
                        break;
                    }
                    expectedPos[uIdx][expectedPosCount[uIdx]++] = pos;
                }
            }
        }
        else {
            // 현재 방향만 체크
            if (ueDirs[uIdx] == DIR_NONE) {
                continue;
            }
            Coordinates pos = expectedPos[uIdx][0];
            for (register int minute = 0; minute < MOVEMENT_COUNT; ++minute) {
                int ny = pos.y + dy[ueDirs[uIdx]];
                int nx = pos.x + dx[ueDirs[uIdx]];
                if (!isValid(ny, nx)) {
                    ueDirs[uIdx] = (ueDirs[uIdx] + 2) % DIR_NUM;
                    ny = pos.y + dy[ueDirs[uIdx]];
                    nx = pos.x + dx[ueDirs[uIdx]];
                }
                pos.y = ny;
                pos.x = nx;
                expectedPos[uIdx][expectedPosCount[uIdx]++] = pos;
            }
        }
    }
}
int tmp[UE_NUM];
Coordinates center(MAP_SIZE / 2, MAP_SIZE / 2); 
void mergeSortUEs(Coordinates UE_list[], int left, int mid, int right) {
    int lIdx = left;
    int rIdx = mid + 1;
    int tIdx = left;
    

    while (lIdx <= mid && rIdx <= right) {
        if (UE_list[ueIdxs[lIdx]] - center > UE_list[ueIdxs[rIdx]] - center) {
            tmp[tIdx++] = ueIdxs[lIdx++];
        }
        else {
            tmp[tIdx++] = ueIdxs[rIdx++];
        }
    }
    while (lIdx <= mid) {
        tmp[tIdx++] = ueIdxs[lIdx++];
    }
    while (rIdx <= right) {
        tmp[tIdx++] = ueIdxs[rIdx++];
    }
    for (register int idx = left; idx <= right; ++idx) {
        ueIdxs[idx] = tmp[idx];
    }
}

void sortUEs(Coordinates UE_list[], int left, int right) {
    if (right <= left) {
        return;
    }
    int mid = (left + right) / 2;
    sortUEs(UE_list, left, mid);
    sortUEs(UE_list, mid + 1, right);
    mergeSortUEs(UE_list, left, mid, right);
}

void sortUEs(Coordinates UE_list[]) {
    for (register int uIdx = 0; uIdx < UE_NUM; ++uIdx) {
        ueIdxs[uIdx] = uIdx;
    }
    sortUEs(UE_list, 0, UE_NUM - 1);
}

void allocUEToAT(Coordinates UE_list[], int antenna_range[], int assign_antenna[]) {
    for (register int idx = 0; idx < ANTENNA_NUM; ++idx) {
        atAllocCount[idx] = 0;
        antenna_range[idx] = 0;
    }
    for (register int idx = 0; idx < UE_NUM; ++idx) {
        int uIdx = ueIdxs[idx];
        int targetAtIdx = -1;
        int minAllocCount = 1e9;
        // 안테나 범위 내에 allocCount 최소인것
        for (register int aIdx = 0; aIdx < ANTENNA_NUM; ++aIdx) {
            if (ANTENNA_CAPA <= atAllocCount[aIdx] || minAllocCount <= atAllocCount[aIdx]) {
                continue;
            }
            bool isInRange = true;
            for (register int pIdx = 0; isInRange && pIdx < expectedPosCount[uIdx]; ++pIdx) {
                if (antenna_range[aIdx] < ats[aIdx] - expectedPos[uIdx][pIdx]) {
                    isInRange = false;
                }
            }
            if (isInRange && atAllocCount[aIdx] < minAllocCount) {
                targetAtIdx = aIdx;
                minAllocCount = atAllocCount[aIdx];
            }
        }
        if (0 <= targetAtIdx) {
            ++atAllocCount[targetAtIdx];
            assign_antenna[uIdx] = targetAtIdx;
            continue;
        }
        int minDist = 1e9;
        // 안테나 범위 내에 없으면 새로운 Connection 생성 -> Dist 최소화
        for (register int aIdx = 0; aIdx < ANTENNA_NUM; ++aIdx) {
            if (ANTENNA_CAPA <= atAllocCount[aIdx]) {
                continue;
            }
            int maxDist = -1;
            for (register int pIdx = 0; pIdx < expectedPosCount[uIdx]; ++pIdx) {
                int dist = ats[aIdx] - expectedPos[uIdx][pIdx];
                if (maxDist < dist) {
                    maxDist = dist;
                }
            }

            if (maxDist < minDist) {
                minDist = maxDist;
                targetAtIdx = aIdx;
            }
        }
        ++atAllocCount[targetAtIdx];
        antenna_range[targetAtIdx] = minDist;
        assign_antenna[uIdx] = targetAtIdx;
    }
}

void saveInitialUEs(Coordinates UE_list[]) {
    if (subTaskCount != 1) {
        return;
    }
    for (register int uIdx = 0; uIdx < UE_NUM; ++uIdx) {
        initialUEs[uIdx] = UE_list[uIdx];
    }
}

void scanUE(Coordinates UE_list[], int antenna_range[], int assign_antenna[]) {
    ++subTaskCount;
    checkUEDirs(UE_list);
    checkExpectedPos(UE_list);
    sortUEs(UE_list);
    allocUEToAT(UE_list, antenna_range, assign_antenna);
    saveInitialUEs(UE_list);
}