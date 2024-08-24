extern void scanFromRobot(int ceilingState[3][3]);
extern int moveRobot(int mCommand);

const int MAX_MAP_SIZE = 60;

int mapSize;
int rStart, cStart, dStart, virtualDir;
int task;
int visit[MAX_MAP_SIZE][MAX_MAP_SIZE];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, -1, 0, 1 };

int commands[4][4] = { { -1, }, };
int reversed[4] = { -1, };

int getCommand(int current, int next) {
    if (commands[current][next] < 0) {
        commands[current][next] = (next - current + 4) % 4;
    }
    return commands[current][next];
}

int getReversedDir(int dir) {
    if (reversed[dir] < 0) {
        reversed[dir] = (dir + 2) % 4;
    }
    return reversed[dir];
}

void init(int N, int subTaskCount) {
    mapSize = N * 2;
    rStart = cStart = N;
    dStart = 0;
    task = 0;

    for (int r = 0; r < mapSize; ++r) {
        for (int c = 0; c < mapSize; ++c) {
            visit[r][c] = 0;
        }
    }

    for (int d1 = 0; d1 < 4; ++d1) {
        for (int d2 = 0; d2 < 4; ++d2) {
            commands[d1][d2] = -1;
        }
    }
    for (int d = 0; d < 4; ++d) {
        reversed[d] = -1;
    }
}

void initSubTask() {
    ++task;
    virtualDir = 0; // UP
}

bool canAccess(int r, int c) {
    return (0 <= r && r < mapSize && 0 <= c && c < mapSize) && visit[r][c] != task;
}

void clean(int r, int c, int dir) {
    visit[r][c] = task;

    int floorState[3][3];
    scanFromRobot(floorState);

    for (int d = 0; d < 4; ++d) {
        int fr = 1 + dr[d];
        int fc = 1 + dc[d];
        if (floorState[fr][fc] != 0) {
            continue;
        }
        int nDir = (dir + d) % 4;
        int nr = r + dr[nDir];
        int nc = c + dc[nDir];

        if (!canAccess(nr, nc)) {
            continue;
        }
        moveRobot(getCommand(virtualDir, nDir));
        virtualDir = nDir;
        clean(nr, nc, virtualDir);
    }
    int reversedDir = getReversedDir(dir);
    moveRobot(getCommand(virtualDir, reversedDir));
    virtualDir = reversedDir;
}

void cleanHouse(int mLimitMoveCount) {
    initSubTask();
    clean(rStart, cStart, dStart);
}
