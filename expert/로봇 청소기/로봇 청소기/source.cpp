extern void scan(int floorState[3][3]);
extern int move(void);
extern void turn(int mCommand);

const int REAL_MAP_COUNT = 8 * 8; // 64 * 64
const int MAP_SIZE = 8 * 2; // 128

const int ORDER_MOVE = -1;
const int ORDER_TURN_UP = 0;
const int ORDER_TURN_LEFT = 1;
const int ORDER_TURN_DOWN = 2;
const int ORDER_TURN_RIGHT = 3;

const int HOUSE_STATE_UNKNOWN = -1;
const int HOUSE_STATE_UNCLEANED = 0;
const int HOUSE_STATE_WALL = 1;
const int HOUSE_STATE_CLEANED = 2;

static const int MOVE_COST = 10;
static const int TURN_COST = 15;
static const int SCAN_COST = 20;

int knownCount;
int xPos, yPos, cDir;
int house[MAP_SIZE][MAP_SIZE];
int current_house[MAP_SIZE][MAP_SIZE];
bool visit[MAP_SIZE][MAP_SIZE];



int orderSize;
int tmpOrderSize;
int orders[REAL_MAP_COUNT];
int tmpOrders[REAL_MAP_COUNT];

static const int dy[4] = { -1, 0, 1, 0 };
static const int dx[4] = { 0, -1, 0, 1 };

void init(void) {
    for (register int y = 0; y < MAP_SIZE; ++y) {
        for (register int x = 0; x < MAP_SIZE; ++x) {
            house[y][x] = HOUSE_STATE_UNKNOWN;
        }
    }
}

#include <iostream>
using namespace std;
void printCurrentHouse(const string &caller) {
    cout << "caller: " << caller << endl;
    for (register int y = 0; y < MAP_SIZE; ++y) {
        for (register int x = 0; x < MAP_SIZE; ++x) {
            cout << current_house[y][x] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void initCleanHoue() {
    knownCount = 0;
    xPos = yPos = MAP_SIZE / 2 - 1;
    cDir = 0;
    for (register int y = 0; y < MAP_SIZE; ++y) {
        for (register int x = 0; x < MAP_SIZE; ++x) {
            if (y == yPos && xPos == x) {
                knownCount++;
                current_house[y][x] = HOUSE_STATE_UNCLEANED;
            }
            else {
                current_house[y][x] = HOUSE_STATE_UNKNOWN;
            }
        }
    }
}

void drawScanResult(int floorState[3][3], int dir) {
    switch (dir) {
    case 0:  // UP
        for (int y = yPos - 1, sy = 0; y <= yPos + 1; ++y, ++sy) {
            for (int x = xPos - 1, sx = 0; x <= xPos + 1; ++x, ++sx) {
                if (current_house[y][x] == HOUSE_STATE_UNKNOWN) {
                    ++knownCount;
                    current_house[y][x] = floorState[sy][sx];
                }
            }
        }
        break;
    case 1:  // LEFT
        for (int y = yPos - 1, sx = 0; y <= yPos + 1; ++y, ++sx) {
            for (int x = xPos - 1, sy = 2; x <= xPos + 1; ++x, --sy) {
                if (current_house[y][x] == HOUSE_STATE_UNKNOWN) {
                    ++knownCount;
                    current_house[y][x] = floorState[sy][sx];
                }
            }
        }
        break;
    case 2:  // DOWN
        for (int y = yPos - 1, sy = 2; y <= yPos + 1; ++y, --sy) {
            for (int x = xPos - 1, sx = 2; x <= xPos + 1; ++x, --sx) {
                if (current_house[y][x] == HOUSE_STATE_UNKNOWN) {
                    ++knownCount;
                    current_house[y][x] = floorState[sy][sx];
                }
            }
        }
        break;
    case 3:  // RIGHT
        for (int y = yPos - 1, sx = 2; y <= yPos + 1; ++y, --sx) {
            for (int x = xPos - 1, sy = 0; x <= xPos + 1; ++x, ++sy) {
                if (current_house[y][x] == HOUSE_STATE_UNKNOWN) {
                    ++knownCount;
                    current_house[y][x] = floorState[sy][sx];
                }
            }
        }
        break;
    }
    printCurrentHouse("drawFloor - knownCount " + knownCount);
}

void scanWrapper(int dir) {
    int floorState[3][3];
    scan(floorState);
    drawScanResult(floorState, dir);
}

int moveWrapper() {
    int nYPos = yPos + dy[cDir];
    int nXPos = xPos + dx[cDir];
    if (!canMove(nYPos, nXPos)) {
        return 0;
    }
    int value = current_house[nYPos][nXPos];
    if (value == HOUSE_STATE_WALL || value == HOUSE_STATE_UNKNOWN) {
        return 0;
    }
    return move();
}

void turnWrapper(int command) {
    int mainCommand = (command + 4 - cDir) % 4;
    cDir = command;
    turn(mainCommand);
}

void initVisit() {
    for (register int y = 0; y < MAP_SIZE; ++y) {
        for (register int x = 0; x < MAP_SIZE; ++x) {
            visit[y][x] = false;
        }
    }
}

bool canMove(int y, int x) {
    return 0 <= y && y < MAP_SIZE && 0 <= x && x < MAP_SIZE
        && current_house[y][x] != HOUSE_STATE_UNKNOWN
        && current_house[y][x] != HOUSE_STATE_WALL;
}

void printOrders() {
    for (int i = orderSize - 1; 0 <= i; --i) {
        cout << orders[i] << " ";
    }
    cout << endl;
}

void printTmpOrders() {
    for (int i = tmpOrderSize - 1; 0 <= i; --i) {
        cout << tmpOrders[i] << " ";
    }
    cout << endl;
}

void copyTmpOrdersToOrders() {
    orderSize = tmpOrderSize;
    for (int idx = 0; idx < tmpOrderSize; ++idx) {
        orders[idx] = tmpOrders[idx];
    }
}

int getCost(int y, int x, int dir, int targetY, int targetX) {
    if (y == targetY && x == targetX) {
        return 0;
    }
    int minCost = 1e9;
    int minDir = -1;
    visit[y][x] = true;
    for (int d = 0; d < 4; ++d) {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (visit[ny][nx] || !canMove(ny, nx)) {
            continue;
        }
        int cost = MOVE_COST + (d == dir ? 0 : TURN_COST) + getCost(ny, nx, d, targetY, targetX);
        if (cost < minCost) {
            minCost = cost;
            minDir = d;
        }
    }
    if (minDir != -1) {
        tmpOrders[tmpOrderSize++] = ORDER_MOVE;
        if (minDir != dir) {
            tmpOrders[tmpOrderSize++] = minDir;
        }
    }

    return minCost;
}

void updateMinimumCostUnChangedPosOrder(int startY, int startX, int startDir) {
    int minCost = 1e9;
    for (register int y = 0; y < MAP_SIZE; ++y) {
        for (register int x = 0; x < MAP_SIZE; ++x) {
            if (current_house[y][x] == HOUSE_STATE_UNCLEANED) {
                tmpOrderSize = 0;
                initVisit();
                int cost = getCost(startY, startX, startDir, y, x);
                if (cost < minCost) {
                    minCost = cost;
                    copyTmpOrdersToOrders();
                }
            }
        }
    }
    cout << minCost << endl;
    printOrders();
}

void run(int y, int x, int dir) {
    // REAL_MAP_COUNT 만큼 확인이 끝났을 때까지
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    // TEST block start
    int origin = current_house[ny][nx];
    current_house[ny][nx] = 3;
    printCurrentHouse("run");
    current_house[ny][nx] = origin;
    // TEST block start

    current_house[y][x] = HOUSE_STATE_CLEANED;
    cout << y << ", " << x << " : " << current_house[y][x] << endl;
    if (current_house[ny][nx] == HOUSE_STATE_UNKNOWN) {
        scanWrapper(dir);
    }
    updateMinimumCostUnChangedPosOrder(y, x, dir);
}

void cleanHouse(void) {
    initCleanHoue();
    run(yPos, xPos, cDir);
}

