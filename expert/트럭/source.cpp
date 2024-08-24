//#include <stdio.h>
//
//#define ABS(x) (((x) < 0) ? (-(x)) : (x))
//
//struct Coordinates {
//    int y, x;
//
//    Coordinates() { y = x = 0; }
//
//    Coordinates(int _y, int _x) {
//        y = _y;
//        x = _x;
//    }
//
//    int operator-(Coordinates& param) {
//        return ABS(y - param.y) + ABS(x - param.x);
//    }
//};
//
//static const int MAP_SIZE = 100;
//static const int ANTENNA_NUM = 150;
//static const int ANTENNA_CAPA = 100;
//static const int UE_NUM = 10'000;
//static const int MOVEMENT_COUNT = 5; 
//static const int DIR_NUM = 4;
//static const int DIR_NONE = -1;
//static const int DIR_UP = 0;
//static const int DIR_LEFT = 1;
//static const int DIR_DOWN = 2;
//static const int DIR_RIGHT = 3;
//
//static const int dy[DIR_NUM] = { -1, 0, 1, 0 };
//static const int dx[DIR_NUM] = { 0, -1, 0, 1 };
//
//// UE는 10000개, AT는 150개
//// 가운데에서 먼 순으로, UE의 주변의 AT밀도가 낮은 순으로 AT에 할당을 해야한다.
//
//bool isValidPos(int y, int x) { return 0 <= y && y < MAP_SIZE && 0 <= x && x < MAP_SIZE; }
//bool isValidPos(Coordinates& pos) { return isValidPos(pos.y, pos.x);  }
//
//int subTask;
//Coordinates* ats;
//int ueDirs[UE_NUM];
//int ueIdxs[UE_NUM];
//int ueTmpIdxs[UE_NUM];
//int atAllocCount[ANTENNA_NUM];
//Coordinates *ues;
//Coordinates prevUes[UE_NUM];
//Coordinates center(MAP_SIZE / 2, MAP_SIZE / 2);
//
//void init(Coordinates antenna_list[]) {
//    subTask = 0;
//    ats = antenna_list;
//    for (register int idx = 0; idx < UE_NUM; ++idx) {
//        ueDirs[idx] = DIR_NONE;
//    }
//}
//

//
//void initUeIdxs() {
//    for (register int idx = 0; idx < UE_NUM; ++idx) {
//        ueIdxs[idx] = idx;
//    }
//}
//
//bool isLeftBigger(Coordinates& lPos, Coordinates& rPos) {
//
//    if (lPos - center > rPos - center) {
//        return true;
//    }
//    else if (lPos - center < rPos - center) {
//        return false;
//    }
//    // 밀도 체크
//    return false;
//}
//
//void movePos(Coordinates& pos, int &dir) {
//    int ny = pos.y + dy[dir];
//    int nx = pos.x + dx[dir];
//    if (!isValidPos(ny, nx)) {
//        dir = (dir + 2) / 2;
//        ny = pos.y + dy[dir];
//        nx = pos.x + dx[dir];
//    }
//    pos.y = ny;
//    pos.x = nx;
//}
//
//void sortUesMerge(Coordinates UE_list[], int left, int mid, int right) {
//    int lIdx = left;
//    int rIdx = mid + 1;
//    int tIdx = left;
//
//    while (lIdx <= mid && rIdx <= right) {
//        int leftBiggerCount = 0;
//        int rightBiggerCount = 0;
//        Coordinates lPos = UE_list[ueIdxs[lIdx]];
//        Coordinates rPos = UE_list[ueIdxs[rIdx]];
//        if (isLeftBigger(lPos, rPos)) {
//            ++leftBiggerCount;
//        }
//        else {
//            ++rightBiggerCount;
//        }
//        // for simulation do not update dir, so do not ues reference, alloc new dir
//        int lDir = ueDirs[lIdx];
//        int rDir = ueDirs[rIdx];
//        for (register int minute = 0; minute < MOVEMENT_COUNT; ++minute) {
//            movePos(lPos, lDir);
//            movePos(rPos, rDir);
//            if (isLeftBigger(lPos, rPos)) {
//                ++leftBiggerCount;
//            }
//            else {
//                ++rightBiggerCount;
//            }
//        }
//        if (isLeftBigger) {
//            ueTmpIdxs[tIdx++] = ueIdxs[lIdx++];
//        }
//        else {
//            ueTmpIdxs[tIdx++] = ueIdxs[rIdx++];
//        }
//    }
//    while (lIdx <= mid) {
//        ueTmpIdxs[tIdx++] = ueIdxs[lIdx++];
//    }
//    while (rIdx <= right) {
//        ueTmpIdxs[tIdx++] = ueIdxs[rIdx++];
//    }
//
//    for (register int idx = left; idx <= right; ++idx) {
//        ueIdxs[idx] = ueTmpIdxs[idx];
//    }
//
//}
//
//void sortUEs(Coordinates UE_list[], int left, int right) {
//    if (right <= left) {
//        return;
//    }
//    int mid = (left + right) / 2;
//    sortUEs(UE_list, left, mid);
//    sortUEs(UE_list, mid + 1, right);
//    sortUesMerge(UE_list, left, mid, right);
//}
//
//void sortUEs(Coordinates UE_list[]) {
//    initUeIdxs();
//    sortUEs(UE_list, 0, UE_NUM - 1);
//}
//
//void allocUEToAT(Coordinates UE_list[], int antenna_range[], int assign_antenna[]) {
//    for (register int atIdx = 0; atIdx < ANTENNA_NUM; ++atIdx) {
//        atAllocCount[atIdx] = 0;
//        antenna_range[atIdx] = 0;
//    }
//    for (register int idx = 0; idx < UE_NUM; ++idx) {
//        int uIdx = ueIdxs[idx];
//        int targetAtIdx = -1;
//        int minAllocCount = 1e9;
//        for (register int atIdx = 0; atIdx < ANTENNA_NUM; ++atIdx) {
//            if (ANTENNA_CAPA <= atAllocCount[atIdx] || minAllocCount <= atAllocCount[atIdx]) {
//                continue;
//            }
//            bool inRange = true;
//            Coordinates pos = UE_list[uIdx];
//            int dir = ueDirs[uIdx];
//            if (antenna_range[atIdx] < ats[atIdx] - pos) {
//                inRange = false;
//            }
//            for (register int minute = 0; inRange && minute < MOVEMENT_COUNT; ++minute) {
//                movePos(pos, dir);
//                if (antenna_range[atIdx] < ats[atIdx] - pos) {
//                    inRange = false;
//                }
//            }
//            if (inRange && atAllocCount[atIdx] < minAllocCount) {
//                minAllocCount = atAllocCount[atIdx];
//                targetAtIdx = atIdx;
//            }
//        }
//        if (0 <= targetAtIdx) {
//            ++atAllocCount[targetAtIdx];
//            assign_antenna[uIdx] = targetAtIdx;
//            continue;
//        }
//        int minDist = 1e9;
//        for (register int atIdx = 0; atIdx < ANTENNA_NUM; ++atIdx) {
//            if (ANTENNA_CAPA <= atAllocCount[atIdx]) {
//                continue;
//            }
//
//            Coordinates pos = UE_list[uIdx];
//            int dir = ueDirs[uIdx];
//            int maxPosDist = ats[atIdx] - pos;
//            for (register int minute = 0; minute < MOVEMENT_COUNT; ++minute) {
//                movePos(pos, dir);
//                int dist = ats[atIdx] - pos;
//                if (maxPosDist < dist) {
//                    maxPosDist = dist;
//                }
//            }
//
//            if (maxPosDist < minDist) {
//                minDist = maxPosDist;
//                targetAtIdx = atIdx;
//            }
//        }
//        ++atAllocCount[targetAtIdx];
//        assign_antenna[uIdx] = targetAtIdx;
//        antenna_range[targetAtIdx] = minDist;
//    }
//}
//
//
//void saveUes(Coordinates UE_list[]) {
//    for (register int idx = 0; idx < UE_NUM; ++idx) {
//        prevUes[idx] = UE_list[idx];
//    }
//}
//
//void scanUE(Coordinates UE_list[], int antenna_range[], int assign_antenna[]) {
//    ++subTask;
//    checkDir(UE_list);
//    sortUEs(UE_list);
//    allocUEToAT(UE_list, antenna_range, assign_antenna);
//    saveUes(UE_list);
//}


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
Coordinates center(MAP_SIZE / 2, MAP_SIZE / 2);

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

int calculateDir(Coordinates &prev, Coordinates &cur) {
    if (prev - cur == 0) {
        return DIR_NONE;
    }
    bool isVertical = prev.x == cur.x;
    for (register int d = 0; d < 4; ++d) {
        if ((isVertical && (d == DIR_LEFT || d == DIR_RIGHT)) || (!isVertical && (d == DIR_UP || d == DIR_DOWN))) {
            continue;
        } 
        Coordinates pos = prev;
        int dir = d;
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
        if (cur - pos == 0) {
            return dir;
        }
    }
    // do not handle;
    return DIR_NONE;
}

void updateUEDirs(Coordinates UE_list[]) {
    if (subTask != 2) {
        return;
    }
    for (register int idx = 0; idx < UE_NUM; ++idx) {
        ueDirs[idx] = calculateDir(initial_ues[idx], UE_list[idx]);
    }
}

#define MAX_EXPECTED_POS_COUNT 20
Coordinates expectedUEPos[UE_NUM][MAX_EXPECTED_POS_COUNT];
int expectedUEPosCount[UE_NUM];

void calculateExpectedUEPos(Coordinates UE_list[]) {
    for (register int idx = 0; idx < UE_NUM; ++idx) {
        int& dir = ueDirs[idx];
        expectedUEPosCount[idx] = 0;
        expectedUEPos[idx][expectedUEPosCount[idx]++] = UE_list[idx];
        if (subTask == 1) {
            for (register int d = 0; d < 4; ++d) {
                dir = d;
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
            if (dir == DIR_NONE) {
                continue;
            }
            Coordinates pos = expectedUEPos[idx][0];
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
                expectedUEPos[idx][expectedUEPosCount[idx]++] = pos;
            }
        }
    }
}

bool isLeftBigger(Coordinates& lPos, Coordinates& rPos) {

    if (lPos - center > rPos - center) {
        return true;
    }
    else {
        return false;
    }
}
void sortUEMerge(Coordinates UE_list[], int left, int mid, int right) {
    int lIdx = left;
    int rIdx = mid + 1;
    int tmpIdx = left;
    Coordinates center{ MAP_SIZE / 2, MAP_SIZE / 2 };
    while (lIdx <= mid && rIdx <= right) {

        int leftBiggerCount = 0;
        int rightBiggerCount = 0;

        int size = expectedUEPosCount[ueIdxs[lIdx]] < expectedUEPosCount[ueIdxs[rIdx]] ? expectedUEPosCount[ueIdxs[lIdx]] : expectedUEPosCount[ueIdxs[rIdx]];
        for (register int idx = 0; idx < size; ++idx) {
            if (isLeftBigger(expectedUEPos[ueIdxs[lIdx]][expectedUEPosCount[idx]], expectedUEPos[ueIdxs[rIdx]][expectedUEPosCount[idx]])) {
                ++leftBiggerCount;
            }
            else {
                ++rightBiggerCount;
            }
        }
        if (leftBiggerCount > rightBiggerCount) {
            ueTmpIdxs[tmpIdx++] = ueIdxs[lIdx++];
        }
        else {
            ueTmpIdxs[tmpIdx++] = ueIdxs[rIdx++];
        }


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