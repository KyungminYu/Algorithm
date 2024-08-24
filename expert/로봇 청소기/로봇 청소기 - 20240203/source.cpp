#include <stdio.h>

extern void scanFromRobot(int ceilingState[3][3]);
extern int moveRobot(int mCommand);

void init(int N, int subTaskCount) {
}

const int MAX_MAP_SIZE = 61;

const int STATE_UNKNWON = -1;
const int STATE_UNCLEANED= 0;
const int STATE_WALL = 1;
const int STATE_CLEANED = 2;

const int DIR_NONE = -1;
const int DIR_UP = 0;
const int DIR_LEFT = 1;
const int DIR_DOWN = 2;
const int DIR_RIGHT = 3;

const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, -1, 0, 1 };

int map[MAX_MAP_SIZE][MAX_MAP_SIZE];
int cRow, cCol, cDir;

void initSubTask() {
    cRow = cCol = MAX_MAP_SIZE / 2;
    cDir = DIR_UP;
    for (int r = 0; r < MAX_MAP_SIZE; ++r) {
        for (int c = 0; c < MAX_MAP_SIZE; ++c) {
            map[r][c] = STATE_UNKNWON;
        }
    }
    map[cRow][cCol] = STATE_CLEANED;
}


void drawStateToMap(int state[3][3]) {
    if (cDir == DIR_UP) {
        for (int r = cRow - 1, sRow = 0; r <= cRow + 1; ++r, ++sRow) {
            for (int c = cCol - 1, sCol = 0; c <= cCol + 1; ++c, ++sCol) {
                if (map[r][c] == STATE_UNKNWON) {
                    map[r][c] = state[sRow][sCol];
                }
            }
        }
    }
    else if (cDir == DIR_LEFT) {
        for (int r = cRow - 1, sCol = 2; r <= cRow + 1; ++r, --sCol) {
            for (int c = cCol - 1, sRow = 0; c <= cCol + 1; ++c, ++sRow) {
                if (map[r][c] == STATE_UNKNWON) {
                    map[r][c] = state[sRow][sCol];
                }
            }
        }
    }
    else if (cDir == DIR_DOWN) {
        for (int r = cRow - 1, sRow = 2; r <= cRow + 1; ++r, --sRow) {
            for (int c = cCol - 1, sCol = 2; c <= cCol + 1; ++c, --sCol) {
                if (map[r][c] == STATE_UNKNWON) {
                    map[r][c] = state[sRow][sCol];
                }
            }
        }
    }
    else { // if (cDir == DIR_RIGHT) {
        for (int r = cRow - 1, sCol = 0; r <= cRow + 1; ++r, ++sCol) {
            for (int c = cCol - 1, sRow = 2; c <= cCol + 1; ++c, --sRow) {
                if (map[r][c] == STATE_UNKNWON) {
                    map[r][c] = state[sRow][sCol];
                }
            }
        }
    }
}

void scanWrapper() {
    int state[3][3];
    scanFromRobot(state);
    drawStateToMap(state);
}

struct position {
    int r, c;
    position() {};
    position(int _r, int _c) : r(_r), c(_c) {};
    position(const position& p) : position(p.r, p.c) {}
};

const int MAX_QUEUE_SIZE = MAX_MAP_SIZE * MAX_MAP_SIZE;

struct queue {
    int head, tail;
    position elements[MAX_QUEUE_SIZE];

    queue() : head(0), tail(0) {}

    void push(const position& e) {
        elements[tail] = e;
        tail = (tail + 1) % MAX_QUEUE_SIZE;
    }

    position front() {
        return elements[head];
    }

    void pop() {
        head = (head + 1) % MAX_QUEUE_SIZE;
    }

    bool isEmpty() {
        return head == tail;
    }

    void clear() {
        head = tail = 0;
    }
};

int directionsCount;
int directions[MAX_MAP_SIZE * MAX_MAP_SIZE];
int savedDirections[MAX_MAP_SIZE][MAX_MAP_SIZE];
bool visit[MAX_MAP_SIZE][MAX_MAP_SIZE];
queue posQueue;

bool cleanUncleanedState() {
    int moveResult = 0;

    for (int command = 0; command < 4; ++command) {
        int nDir = (cDir + command) % 4;
        int nRow = cRow + dr[nDir];
        int nCol = cCol + dc[nDir];
        if (map[nRow][nCol] == STATE_UNCLEANED) {
            moveResult = moveRobot(command);
            if (moveResult) {
                cDir = nDir;
                cRow = nRow;
                cCol = nCol;
                map[cRow][cCol] = STATE_CLEANED;
            }
        }
    }
    return moveResult;
}

bool canAccess(int r, int c) {
    return (0 <= r && r < MAX_MAP_SIZE) && (0 <= c && c < MAX_MAP_SIZE);
}

void initDataBeforeFindDirections() {
    for (int r = 0; r < MAX_MAP_SIZE; ++r) {
        for (int c = 0; c < MAX_MAP_SIZE; ++c) {
            visit[r][c] = false;
            savedDirections[r][c] = DIR_NONE;
        }
    }
    posQueue.clear();
}

bool findDirections() {
    initDataBeforeFindDirections();

    int sRow = cRow;
    int sCol = cCol;
    posQueue.push({cRow, cCol});
    while (!posQueue.isEmpty()) {
        position cPos = posQueue.front();
        posQueue.pop();
        if (map[cPos.r][cPos.c] == STATE_UNCLEANED || map[cPos.r][cPos.c] == STATE_UNKNWON) {
            int nRow = cPos.r;
            int nCol = cPos.c;
            directionsCount = 0;
            while (nRow != sRow || nCol != sCol) {
                int savedDirection = savedDirections[nRow][nCol];
                directions[directionsCount++] = savedDirection;
                nRow += dr[(savedDirection + 2) % 4];
                nCol += dc[(savedDirection + 2) % 4];
            }
            return true;
        }
        for (int dir = 0; dir < 4; ++dir) {
            int nRow = cPos.r + dr[dir];
            int nCol = cPos.c + dc[dir];
            if (!canAccess(nRow, nCol)
                || visit[nRow][nCol]
                || map[nRow][nCol] == STATE_WALL) {
                continue;
            }
            visit[nRow][nCol] = true;
            savedDirections[nRow][nCol] = dir;
            posQueue.push({ nRow, nCol });
        }
    }
    return false;
}

void cleanUsingDirections() {
    int moveResult;
    for (int idx = directionsCount - 1; 0 <= idx; --idx) {
        int nDir = directions[idx];
        int nRow = cRow + dr[nDir];
        int nCol = cCol + dc[nDir];
        if (map[nRow][nCol] == STATE_UNKNWON) {
            break;
        }
        moveResult = moveRobot((nDir - cDir + 4) % 4);
        if (moveResult) {
            cDir = nDir;
            cRow = nRow;
            cCol = nCol;
            map[cRow][cCol] = STATE_CLEANED;
        }
    }
}

void cleanHouse(int mLimitMoveCount) {
    initSubTask();
    while (true) {
        scanWrapper();
        if (cleanUncleanedState()) {
            continue;
        }
        if (!findDirections()) {
            break;
        }
        cleanUsingDirections();
    }
}
