#include <stdio.h>

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


/*
* 2번째 scan부터 방향을 확인 할 수 있다.
// SubTask 2 -> dir계산
// SubTask 1 종료 이후, 다음 SubTask 2에서 dir 계산을 위해 이전 UEList를 백업해야 한다
// Scan 동작에서
   1. 예상 위치 계산
      - dir이 없는 경우(-1) 4방향 모두 이동한다고 가정하고 예상 위치 계산해야함
      - dir이 있는 경우(0~3) 한방향만 이동한다고 가정하고 예상위치 계산해야함
   2. 정렬 -> 가운데에 있는 UE들은 영향 받을 수 있는 AT가 많을 것, 모서리 쪽에 있는 UE는 잘못 할당하면 AT가 멀리 잡힐 수 있다. 
      -> 중심에서 먼 순서대로 정렬을 해야함
   3. 할당 -> AT Range 안쪽으로 UE가 존재하는 경우, 할당된 AT의 수가 적은 AT로 할당.
           -> AT Range 안쪽으로 UE가 존재하지 않는 경우, AT와 UE가 이동할 수 있는 위치간의 거리의 최소값을 가지는 AT를 할당
*/

#define MAP_SIZE 100
#define AT_NUM 150
#define UE_NUM 10000
#define AT_MAX_ALLOC 100
#define UE_MOVE_TIME 5

#define DIR_NUM 4
#define DIR_NONE -1
#define DIR_UP 0
#define DIR_LEFT 1
#define DIR_DOWN 2
#define DIR_RIGHT 3

static const int dy[] = { 1, 0, -1, 0 };
static const int dx[] = { 0, -1, 0, 1 };

int subTask;
Coordinates* ats;
Coordinates initial_ues[UE_NUM];
int ueIdxs[UE_NUM];
int ueTmpIdxs[UE_NUM];
int ueDirs[UE_NUM];
int atAllocCount[AT_NUM];

void init(Coordinates antenna_list[]) {
    subTask = 0;
    ats = antenna_list;
    for (register int idx = 0; idx < UE_NUM; ++idx) {
        ueDirs[idx] = DIR_NONE;
    }
}

bool isValidPos(int y, int x) {
    return 0 <= y && y < MAP_SIZE && 0 <= x && x < MAP_SIZE;
}

bool isValidPos(Coordinates& p) {
    return isValidPos(p.y, p.x);
}

void updateUEDirs(Coordinates UE_list[]) {
    if (subTask != 2) {
        return;
    }
    for (register int idx = 0; idx < UE_NUM; ++idx) {
        if (UE_list[idx] - initial_ues[idx] == 0) {
            continue;
        }
        int dir;
        for (register int d = 0; d < 4; ++d) {
            Coordinates pos = initial_ues[idx];
            dir = d;
            for (register int minute = 0; minute < UE_MOVE_TIME; ++minute) {
                int ny = pos.y + dy[dir];
                int nx = pos.x + dx[dir];
                if (!isValidPos(ny, nx)) {
                    dir = (dir + 2) % DIR_NUM;
                    ny = pos.y + dy[dir];
                    nx = pos.x + dx[dir];
                }
                pos.y = ny;
                pos.x = nx;
            }
            if (UE_list[idx] - pos == 0) {
                ueDirs[idx] = dir;
                break;
            }
        }
    
    }
}

#define MAX_EXPECTED_POS_COUNT 20
Coordinates expectedUEPos[UE_NUM][MAX_EXPECTED_POS_COUNT];
int expectedUEPosCount[UE_NUM];

void calculateExpectedUEPos(Coordinates UE_list[]) {
    for (register int idx = 0; idx < UE_NUM; ++idx) {
        expectedUEPosCount[idx] = 0;
        expectedUEPos[idx][expectedUEPosCount[idx]++] = UE_list[idx];
        if (subTask <= 1) {
            for (register int d = 0; d < 4; ++d) {
                int dir = d;
                for (register int minute = 1; minute < UE_MOVE_TIME; ++minute) {
                    Coordinates pos = expectedUEPos[idx][0];
                    pos.y += dy[dir] * minute;
                    pos.x += dx[dir] * minute;
                    if (!isValidPos(pos)) {
                        break;
                    }
                    expectedUEPos[idx][expectedUEPosCount[idx]++] = pos;
                }
            }
        }
        else {
            if (ueDirs[idx] == DIR_NONE) {
                continue;
            }
            Coordinates pos = expectedUEPos[idx][0];
            for (register int minute = 0; minute < UE_MOVE_TIME; ++minute) {
                int ny = pos.y + dy[ueDirs[idx]];
                int nx = pos.x + dx[ueDirs[idx]];
                if (!isValidPos(ny, nx)) {
                    ueDirs[idx] = (ueDirs[idx] + 2) % DIR_NUM;
                    ny = pos.y + dy[ueDirs[idx]];
                    nx = pos.x + dx[ueDirs[idx]];
                }
                pos.y = ny;
                pos.x = nx;
                expectedUEPos[idx][expectedUEPosCount[idx]++] = pos;
            }
        }
    }
}

void sortUEMerge(Coordinates UE_list[], int left, int mid, int right) {
    int lIdx = left;
    int rIdx = mid + 1;
    int tmpIdx = left;
    Coordinates center{ MAP_SIZE / 2, MAP_SIZE / 2 };
    while (lIdx <= mid && rIdx <= right) {
        if (UE_list[ueIdxs[lIdx]] - center > UE_list[ueIdxs[rIdx]] - center) {
            ueTmpIdxs[tmpIdx++] = ueIdxs[lIdx++];
        }
        else {
            ueTmpIdxs[tmpIdx++] = ueIdxs[rIdx++];
        }
    }
    while (lIdx <= mid) {
        ueTmpIdxs[tmpIdx++] = ueIdxs[lIdx++];
    }
    while (rIdx <= right) {
        ueTmpIdxs[tmpIdx++] = ueIdxs[rIdx++];
    }
    for (register int idx = left; idx <= right; ++idx) {
        ueIdxs[idx] = ueTmpIdxs[idx];
    }
}

void sortUE(Coordinates UE_list[], int left, int right) {
    if (right <= left) {
        return;
    }
    int mid = (left + right) / 2;
    sortUE(UE_list, left, mid);
    sortUE(UE_list, mid + 1, right);
    sortUEMerge(UE_list, left, mid, right);
}

void initUEIdxs() {
    for (register int idx = 0; idx < UE_NUM; ++idx) {
        ueIdxs[idx] = idx;
    }
}

void sortUE(Coordinates UE_list[]) {
    initUEIdxs();
    sortUE(UE_list, 0, UE_NUM - 1);
}

void allocUEToAT(Coordinates UE_list[], int antenna_range[], int assign_antenna[]) {
    for (register int atIdx = 0; atIdx < AT_NUM; ++atIdx) {
        atAllocCount[atIdx] = 0;
        antenna_range[atIdx] = 0;
    }
    for (register int idx = 0; idx < UE_NUM; ++idx) {
        // AT Range 안쪽으로 UE가 존재하는 경우, 할당된 AT의 수가 적은 AT로 할당.
        int uIdx = ueIdxs[idx];
        int targetAtIdx = -1;
        int minAllocCount = 1e9;
        for (register int atIdx = 0; atIdx < AT_NUM; ++atIdx) {
            if (AT_MAX_ALLOC <= atAllocCount[atIdx] || minAllocCount <= atAllocCount[atIdx]) {
                continue;
            }
            // check in range
            bool inRange = true;
            for (register int pIdx = 0; inRange && pIdx < expectedUEPosCount[uIdx]; ++pIdx) {
                if (antenna_range[atIdx] < ats[atIdx] - expectedUEPos[uIdx][pIdx]) {
                    inRange = false;
                }
            }
            if (inRange && atAllocCount[atIdx] < minAllocCount) {
                minAllocCount = atAllocCount[atIdx];
                targetAtIdx = atIdx;
            }
        }
        if (0 <= targetAtIdx) {
            ++atAllocCount[targetAtIdx];
            assign_antenna[uIdx] = targetAtIdx;
            continue;
        }
        // AT Range 안쪽으로 UE가 존재하지 않는 경우, AT와 UE가 이동할 수 있는 위치간의 거리의 최소값을 가지는 AT를 할당
        int minDist = 1e9;
        for (register int atIdx = 0; atIdx < AT_NUM; ++atIdx) {
            if (AT_MAX_ALLOC <= atAllocCount[atIdx]) {
                continue;
            }
            int maxPosDist = -1;
            for (register int pIdx = 0; pIdx < expectedUEPosCount[uIdx]; ++pIdx) {
                int dist = ats[atIdx] - expectedUEPos[uIdx][pIdx];
                if (maxPosDist < dist) {
                    maxPosDist = dist;
                }
            }

            if (maxPosDist < minDist) {
                minDist = maxPosDist;
                targetAtIdx = atIdx;
            }
        }
        ++atAllocCount[targetAtIdx];
        assign_antenna[uIdx] = targetAtIdx;
        antenna_range[targetAtIdx] = minDist;
    }
}

void savaInitialUEs(Coordinates UE_list[]) {
    if (1 < subTask) {
        return;
    }
    for (register int idx = 0; idx < UE_NUM; ++idx) {
        initial_ues[idx] = UE_list[idx];
    }
}

void scanUE(Coordinates UE_list[], int antenna_range[], int assign_antenna[]) {
    ++subTask;
    updateUEDirs(UE_list);
    calculateExpectedUEPos(UE_list);
    sortUE(UE_list);
    allocUEToAT(UE_list, antenna_range, assign_antenna);
    savaInitialUEs(UE_list);
}