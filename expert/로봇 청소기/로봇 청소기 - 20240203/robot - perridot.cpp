extern void scanFromRobot(int ceilingState[3][3]);
extern int moveRobot(int mCommand);

const int UNKNOWN = 0;
const int UNCLEANED = 1;
const int WALL = 2;
const int CLEANED = 3;

int map[65][65];
int cy, cx, dir = 0;

static int dy[4] = { -1, 0, 1, 0 };
static int dx[4] = { 0, -1, 0, 1 };

struct point {
    int y;
    int x;
};

struct queue {
    int head = 0, tail = 0;
    point buf[900];

    void push(point a) {
        buf[tail++] = a;
        tail %= 900;
    }

    point front() {
        return buf[head];
    }

    void pop() {
        head++;
        head %= 900;
    }

    bool isEmpty() {
        return head == tail;
    }
};


void adjust(int floorState[3][3])
{
    if (dir == 0) // UP
    {
        for (int y = cy - 1, sy = 0; y <= cy + 1; y++, sy++)
        {
            for (int x = cx - 1, sx = 0; x <= cx + 1; x++, sx++)
            {

                map[y][x] |= floorState[sy][sx] + 1;
            }
        }
    }
    if (dir == 1) // LEFT
    {
        for (int y = cy - 1, sx = 2; y <= cy + 1; y++, sx--)
        {
            for (int x = cx - 1, sy = 0; x <= cx + 1; x++, sy++)
            {
                map[y][x] |= floorState[sy][sx] + 1;
            }
        }
    }
    else if (dir == 2) // DOWN
    {
        for (int y = cy - 1, sy = 2; y <= cy + 1; y++, sy--)
        {
            for (int x = cx - 1, sx = 2; x <= cx + 1; x++, sx--)
            {
                map[y][x] |= floorState[sy][sx] + 1;
            }
        }
    }
    else if (dir == 3) // RIGHT
    {
        for (int y = cy - 1, sx = 0; y <= cy + 1; y++, sx++)
        {
            for (int x = cx - 1, sy = 2; x <= cx + 1; x++, sy--)
            {
                map[y][x] |= floorState[sy][sx] + 1;
            }
        }
    }
}

int pprev[65][65];
void search(int path[300]) {
    int sy = cy;
    int sx = cx;

    queue que;
    que.push(point{ sy,sx });
    int visit[65][65] = { 0, };
    while (!que.isEmpty()) {
        point cur = que.front();
        que.pop();
        if (map[cur.y][cur.x] == UNCLEANED || map[cur.y][cur.x] == UNKNOWN) {
            int ny = cur.y;
            int nx = cur.x;
            int pcnt = 1;
            while (ny != sy || nx != sx) {
                int pdir = pprev[ny][nx];
                path[pcnt++] = pdir;
                ny += dy[(pdir + 2) % 4];
                nx += dx[(pdir + 2) % 4];
            }
            path[0] = pcnt - 1;
            return;
        }

        for (register int i = 0; i < 4; i++) {
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];
            if (map[ny][nx] == WALL) continue;
            if (ny >= 65 || nx >= 65 || ny < 0 || nx < 0 || visit[ny][nx]) continue;
            visit[ny][nx] = 1;
            pprev[ny][nx] = i;
            que.push(point{ ny,nx });
        }
    }
    path[0] = 0;
}


void init(int N, int subTaskCount)
{
    for (register int i = 0; i < 65; i++) for (register int j = 0; j < 65; j++) map[i][j] = 0;
    cy = 30; cx = 30;
    dir = 0;
}

void cleanHouse(int mLimitMoveCount)
{
    for (register int i = 0; i < 65; i++) for (register int j = 0; j < 65; j++) map[i][j] = 0;
    cy = 30; cx = 30;
    dir = 0;
    int buf[3][3];
    map[cy][cx] = CLEANED;
    while (1) {

        scanFromRobot(buf);
        adjust(buf);
        int ret = 0;
        for (register int k = 0; k < 4; k++) {

            register int ny = cy + dy[(dir + k) % 4];
            register int nx = cx + dx[(dir + k) % 4];

            if (map[ny][nx] == UNCLEANED) {
                ret = moveRobot(k);
                if (ret) {
                    map[ny][nx] = CLEANED;
                    cy = ny;
                    cx = nx;
                    dir = (dir + k) % 4;
                    break;
                }
            }
        }
        if (ret) continue;
        int path[300];
        search(path);
        if (path[0] == 0) {
            return;
        }

        for (register int k = path[0]; k >= 1; k--) {
            int ny = cy + dy[path[k]];
            int nx = cx + dx[path[k]];
            if (map[ny][nx] == UNKNOWN) {
                break;
            }

            moveRobot((path[k] - dir + 4) % 4);
            cy = ny;
            cx = nx;
            dir = path[k];
            map[ny][nx] = CLEANED;
        }
    }
}