// 275458

#include <malloc.h>

extern int get_distance(int y1, int x1, int y2, int x2);
#define MAP_SIZE 50

#define AT_MAX_CAP 75
#define AT_NUM 50
#define UE_NUM 2500

#define RANGE_FOR_WEIGHT 5

#define DIR_NUM 6
#define DIR_NONE -1
#define DIR_NOT_MOVED 1
#define DIR_DOWN 0
#define DIR_UP 3
#define DIR_RIGHT 2
#define DIR_LEFT 5
const int dy[] = { 1, 0, 0, -1, 0, 0 };
const int dx[] = { 0, 0, 1, 0, 0, -1 };

int subtask_num;

int* antenna_y, * antenna_x;
int anttenaAllocCount[AT_NUM];

int* user_y, * user_x;
int prev_user_y[UE_NUM];
int prev_user_x[UE_NUM];
int user_dir[UE_NUM];

int userAntennaIdx[UE_NUM][AT_NUM];
int userAntennaDist[UE_NUM][AT_NUM];
int userWeight[UE_NUM];
int userWeightIdx[UE_NUM];

void merge(int values[], int idxs[], int left, int mid, int right, bool isAscending) {
    int lIdx = left;
    int rIdx = mid + 1;
    int idx = 0;

    int* tmpIdxs = (int *) malloc(sizeof(int) * (right - left + 1));

    while (lIdx <= mid && rIdx <= right) {
        if ((isAscending && values[idxs[lIdx]] < values[idxs[rIdx]]) 
            || (!isAscending && values[idxs[lIdx]] > values[idxs[rIdx]]))
            tmpIdxs[idx++] = idxs[lIdx++];
        else tmpIdxs[idx++] = idxs[rIdx++];
    }
    while (lIdx <= mid)   tmpIdxs[idx++] = idxs[lIdx++];
    while (rIdx <= right) tmpIdxs[idx++] = idxs[rIdx++];

    for (int idx = left; idx <= right; ++idx)
        idxs[idx] = tmpIdxs[idx - left];

    free(tmpIdxs);
}

void mergesort(int values[], int idxs[], int left, int right, bool isAscending) {
    if (right <= left) return;
    int mid = (left + right) / 2;
    mergesort(values, idxs, left, mid, isAscending);
    mergesort(values, idxs, mid + 1, right, isAscending);
    merge(values, idxs, left, mid, right, isAscending);
}

void initSubTaskNum() {
    subtask_num = -1;
}

void increaseSubTaskNum() {
    ++subtask_num;
}

void initAntennaCoord(int _antenna_y[], int _antenna_x[]) {
    antenna_y = _antenna_y;
    antenna_x = _antenna_x;
}

void initUserAntennaIdxPair() {
    for (register int userIdx = 0; userIdx < UE_NUM; ++userIdx)
        for (register int antennaIdx = 0; antennaIdx < AT_NUM; ++antennaIdx)
            userAntennaIdx[userIdx][antennaIdx] = antennaIdx;
}

void init(int base_y[], int base_x[]) {
    initSubTaskNum();
    initAntennaCoord(base_y, base_x);
    initUserAntennaIdxPair();
}

int getMaxDistance(int cur_antenna_y, int cur_antenna_x, int cur_user_y, int cur_user_x, int userDir) {
    int max_distance = -1;
    if (userDir == DIR_NONE) return max_distance;// default value is checked from int getMaxDistance(int usedIdx, int antennaIdx, int userDir);
    int next_user_y = cur_user_y;
    int next_user_x = cur_user_x;
    for (register int minute = 0; minute < 2; ++minute) {
        if (next_user_y + dy[userDir] < 0 || MAP_SIZE <= next_user_y + dy[userDir]
            || next_user_x + dx[userDir] < 0 || MAP_SIZE <= next_user_x + dx[userDir])
            userDir = (userDir + 3) % DIR_NUM;
        next_user_y += dy[userDir];
        next_user_x += dx[userDir];
        int dist = get_distance(next_user_y, next_user_x, cur_antenna_y, cur_antenna_x);
        max_distance = max_distance > dist ? max_distance : dist;
    }
    return max_distance;
}

int getMaxDistance(int antennaIdx, int usedIdx, int userDir) {
    int cur_antenna_y = antenna_y[antennaIdx];
    int cur_antenna_x = antenna_x[antennaIdx];
    int cur_user_y = user_y[usedIdx];
    int cur_user_x = user_x[usedIdx];
    int max_distance = get_distance(cur_antenna_y, cur_antenna_x, cur_user_y, cur_user_x);
    if (userDir == DIR_NONE) {
        for (register int dirIdx = 0; dirIdx < DIR_NUM; ++dirIdx) {
            int dist = getMaxDistance(cur_antenna_y, cur_antenna_x, cur_user_y, cur_user_x, dirIdx);
            max_distance = max_distance > dist ? max_distance : dist;
        }
    }
    else {
        int dist = getMaxDistance(cur_antenna_y, cur_antenna_x, cur_user_y, cur_user_x, userDir);
        max_distance = max_distance > dist ? max_distance : dist;
    }
    return max_distance;
}

int getUserDir(int usedIdx) {
    if (subtask_num <= 0) {
        return DIR_NONE;
    }
    int prev_y = prev_user_y[usedIdx];
    int prev_x = prev_user_x[usedIdx];
    int cur_y = user_y[usedIdx];
    int cur_x = user_x[usedIdx];

    if (prev_y < cur_y) return DIR_DOWN;
    else if (cur_y < prev_y) return DIR_UP;
    else if (prev_x < cur_x) return DIR_RIGHT;
    else if (cur_x < prev_x) return DIR_LEFT;
    else if (prev_x <= 1 || MAP_SIZE - 2 <= prev_x || prev_y <= 1 || MAP_SIZE - 2 <= prev_y) return DIR_NONE;
    else return DIR_NOT_MOVED;
}

void initUserCoord(int _user_y[], int _user_x[]) {
    user_y = _user_y;
    user_x = _user_x;
}

void savePrevUserCoord() {
    for (register int userIdx = 0; userIdx < UE_NUM; ++userIdx) {
        prev_user_y[userIdx] = user_y[userIdx];
        prev_user_x[userIdx] = user_x[userIdx];
    }
}

void initRange(int base_range[]) {
    for (register int antennaIdx = 0; antennaIdx < AT_NUM; ++antennaIdx)
        base_range[antennaIdx] = 0;
}

void initAntennaAllocCount() {
    for (register int antennaIdx = 0; antennaIdx < AT_NUM; ++antennaIdx)
        anttenaAllocCount[antennaIdx] = 0;
}

void initUserDirAndWeight(int userIdx) {
    user_dir[userIdx] = getUserDir(userIdx);
    for (register int antennaIdx = 0; antennaIdx < AT_NUM; ++antennaIdx)
        userAntennaDist[userIdx][antennaIdx] = getMaxDistance(antennaIdx, userIdx, user_dir[userIdx]);
    mergesort(userAntennaDist[userIdx], userAntennaIdx[userIdx], 0, AT_NUM - 1, true);

    userWeight[userIdx] = 0;
    userWeightIdx[userIdx] = userIdx;
    for (register int range = 0; range < RANGE_FOR_WEIGHT; ++range) {
        int antennaIdx = userAntennaIdx[userIdx][range];
        userWeight[userIdx] += userAntennaDist[userIdx][antennaIdx];
    }
}

void initUserDirAndWeight() {
    for (register int uIdx = 0; uIdx < UE_NUM; ++uIdx)
        initUserDirAndWeight(uIdx);
}

void allocateAntennaToUser(int uIdx, int base_range[], int terminal_to_base[]) {
    int userIdx = userWeightIdx[uIdx];

    int minAntennaAllocCount = AT_MAX_CAP;
    int minAntennaAllocIdx = -1;
    for (register int aIdx = 0; aIdx < AT_NUM; ++aIdx) {
        int antennaIdx = userAntennaIdx[userIdx][aIdx];
        if (anttenaAllocCount[antennaIdx] >= AT_MAX_CAP) {
            continue;
        }
        if (base_range[antennaIdx] >= userAntennaDist[userIdx][antennaIdx]
            && minAntennaAllocCount > anttenaAllocCount[antennaIdx]) {
            minAntennaAllocCount = anttenaAllocCount[antennaIdx];
            minAntennaAllocIdx = antennaIdx;
        }
    }

    if (minAntennaAllocIdx < 0) {
        int minDist = 10000;
        for (register int aIdx = 0; aIdx < AT_NUM; ++aIdx) {
            int antennaIdx = userAntennaIdx[userIdx][aIdx];
            if (anttenaAllocCount[antennaIdx] >= AT_MAX_CAP) continue;
            if (minDist > userAntennaDist[userIdx][antennaIdx]) {
                minDist = userAntennaDist[userIdx][antennaIdx];
                minAntennaAllocIdx = antennaIdx;
            }
        }
        terminal_to_base[userIdx] = minAntennaAllocIdx;
        ++anttenaAllocCount[minAntennaAllocIdx];
        base_range[minAntennaAllocIdx] = base_range[minAntennaAllocIdx] > minDist ? base_range[minAntennaAllocIdx] : minDist;
    }
    else {
        terminal_to_base[userIdx] = minAntennaAllocIdx;
        ++anttenaAllocCount[minAntennaAllocIdx];
    }
}

void allocateAntennaToUser(int base_range[], int terminal_to_base[]) {
    mergesort(userWeight, userWeightIdx, 0, UE_NUM - 1, false);
    for (register int userIdx = 0; userIdx < UE_NUM; ++userIdx) 
        allocateAntennaToUser(userIdx, base_range, terminal_to_base);
}

void solve(int __uy[], int __ux[], int arange[], int assign_antenna[]) {
    increaseSubTaskNum();
    initUserCoord(__uy, __ux);
    initRange(arange);
    initAntennaAllocCount();
    initUserDirAndWeight();
    allocateAntennaToUser(arange, assign_antenna);
    savePrevUserCoord();
}