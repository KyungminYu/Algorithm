#include <stdio.h>
#include <malloc.h>

struct Coordinate
{
    int y, x;
};

struct Passenger
{
    Coordinate departure;
    Coordinate arrival;
};


extern bool assign_driver(int driverId, int passengerSize, int passengerIds[]);

#define ABS(a) (((a) < 0) ? (-(a)) : (a))
static const long long INF = 500000000;
static const int MAX_DRIVER_COUNT = 100;
static const int MAX_PASSENGER_COUNT = 10000;

int passengerSize[MAX_DRIVER_COUNT];
int passengerIds[MAX_DRIVER_COUNT][MAX_PASSENGER_COUNT];
long long passengerDist[MAX_PASSENGER_COUNT];
int passengerDistIds[MAX_PASSENGER_COUNT];

int scoresIdx[MAX_DRIVER_COUNT];
long long scores[MAX_DRIVER_COUNT];
bool isPassengerAssigned[MAX_PASSENGER_COUNT];

int numOfKeepMinDist = 200;
int minMaxSwapCount = 200;

long long getDistance(Coordinate& c1, Coordinate& c2) {
    return ABS(c1.y - c2.y) + ABS(c1.x - c2.x);
}

long long getPassengerDist(Passenger& p) {
    return getDistance(p.arrival, p.departure);
}

int getDriver(int driverCount) {
    int minScoreDriverId = -1;
    long long minScore = INF;
    for (register int driverId = 0; driverId < driverCount; ++driverId) {
        if (scores[driverId] < minScore) {
            minScore = scores[driverId];
            minScoreDriverId = driverId;
        }
    }
    return minScoreDriverId;
}

int getPassenger(Coordinate& driver, Passenger passengers[], int passengerCount) {
    int selectedPassengerId = -1;
    long long minDist = INF;
    long long minPathDist = INF;
    for (register int passengerIdx = numOfKeepMinDist; passengerIdx < passengerCount; ++passengerIdx) {
        int passengerId = passengerDistIds[passengerIdx];
        if (isPassengerAssigned[passengerId]) {
            continue;
        }
        long long dist = getDistance(driver, passengers[passengerId].departure);
        long long pathDist = passengerDist[passengerId];
        if ((dist < minDist) || (dist == minDist && pathDist < minPathDist)) {
            minDist = dist;
            minPathDist = pathDist;
            selectedPassengerId = passengerId;
        }
    }
    return selectedPassengerId;
}

void sortMerge(long long values[], int idxs[], int left, int mid, int right) {
    int lIdx = left;
    int rIdx = mid + 1;
    int tIdx = 0;
    int* tmp = (int*)malloc((right - left + 1) * sizeof(int));

    while (lIdx <= mid && rIdx <= right) {
        if (values[idxs[lIdx]] < values[idxs[rIdx]]) {
            tmp[tIdx++] = idxs[lIdx++];
        }
        else {
            tmp[tIdx++] = idxs[rIdx++];
        }
    }
    while (lIdx <= mid) {
        tmp[tIdx++] = idxs[lIdx++];
    }
    while (rIdx <= right) {
        tmp[tIdx++] = idxs[rIdx++];
    }

    for (register int idx = left; idx <= right; ++idx) {
        idxs[idx] = tmp[idx - left];
    }

    free(tmp);
}

void sort(long long values[], int idxs[], int left, int right) {
    if (right <= left) {
        return;
    }
    int mid = (left + right) / 2;
    sort(values, idxs, left, mid);
    sort(values, idxs, mid + 1, right);
    sortMerge(values, idxs, left, mid, right);
}

int getMinScoreDriverId(int driverCount) {
    int minScoreDriverId = -1;
    long long minScore = INF;
    for (register int driverId = 0; driverId < driverCount; ++driverId) {
        if (minScore > scores[driverId]) {
            minScore = scores[driverId];
            minScoreDriverId = driverId;
        }
    }
    return minScoreDriverId;
}

long long getMinScore(int driverCount) {
    return scores[getMinScoreDriverId(driverCount)];
}

long long getMaxScoreDriverId(int driverCount) {
    int maxScoreDriverId = -1;
    long long maxScore = 0;
    for (register int driverId = 0; driverId < driverCount; ++driverId) {
        if (maxScore < scores[driverId]) {
            maxScore = scores[driverId];
            maxScoreDriverId = driverId;
        }
    }
    return maxScoreDriverId;
}

long long getMaxScore(int driverCount) {
    return scores[getMaxScoreDriverId(driverCount)];
}

void printScoreMinMax(int driverCount, int passengerCount, bool isPrintScore) {
    if (isPrintScore) {
        for (register int driverId = 0; driverId < driverCount; ++driverId) {
            printf("DriverId: %d: %lld\n", driverId, scores[driverId]);
        }
    }
    long long minScore = getMinScore(driverCount);
    long long maxScore = getMaxScore(driverCount);
    printf("driverCount: %d,\tpassnegerCount: %d,\ttotalPairs: %d,\tmax_score: %lld,\tmin_score: %lld,\tscore diff: %lld\n", driverCount, passengerCount, driverCount * passengerCount, maxScore, minScore, maxScore - minScore);
}

void getDriverPassengerPair(int& driverId, int& passengerId, int driverCount, Coordinate drivers[], int passengerCount, Passenger passengers[]) {
    passengerId = driverId = -1;

    int maxScoreDriverId = getMaxScoreDriverId(driverCount);
    int maxScore = scores[maxScoreDriverId];

    int minScore = INF;
    for (register int pidx = 0; pidx < numOfKeepMinDist; ++pidx) {
        int pid = passengerDistIds[pidx];
        if (isPassengerAssigned[pid]) {
            continue;
        }
        for (register int did = 0; did < driverCount; ++did) {
            if (did == maxScoreDriverId) {
                continue;
            }

            long long score = getDistance(drivers[did], passengers[pid].departure) + getPassengerDist(passengers[pid]);
            if (score < minScore && score + scores[did] < maxScore) {
                driverId = did;
                passengerId = pid;
                minScore = score;
            }
        }
    }

    if (0 <= passengerId) {
        return;
    }
    minScore = INF;
    for (register int pidx = 0; pidx < numOfKeepMinDist; ++pidx) {
        int pid = passengerDistIds[pidx];
        if (isPassengerAssigned[pid]) {
            continue;
        }
        for (register int did = 0; did < driverCount; ++did) {
            long long score = scores[did] + getDistance(drivers[did], passengers[pid].departure) + getPassengerDist(passengers[pid]);
            if (score < minScore) {
                driverId = did;
                passengerId = pid;
                minScore = score;
            }
        }
    }
}

void swapDriveCourse(Passenger passengers[], int firstDriverId, int firstDriverPassengerIdx, int secondDriverId, int secondDriverPassengerIdx) {
    int prevPassengerId = passengerIds[firstDriverId][firstDriverPassengerIdx - 1];
    int removePassengerId = passengerIds[firstDriverId][firstDriverPassengerIdx];
    int nextPassengerId = passengerIds[firstDriverId][firstDriverPassengerIdx + 1];
    long long scoreReduce =
        getDistance(passengers[prevPassengerId].arrival, passengers[nextPassengerId].departure)
        - getDistance(passengers[prevPassengerId].arrival, passengers[removePassengerId].departure)
        - getPassengerDist(passengers[removePassengerId])
        - getDistance(passengers[removePassengerId].arrival, passengers[nextPassengerId].departure);
    for (register int idx = firstDriverPassengerIdx; idx < passengerSize[firstDriverId]; ++idx) {
        passengerIds[firstDriverId][idx] = passengerIds[firstDriverId][idx + 1];
    }
    --passengerSize[firstDriverId];
    scores[firstDriverId] += scoreReduce;

    prevPassengerId = passengerIds[secondDriverId][secondDriverPassengerIdx - 1];
    int curPassengerId = passengerIds[secondDriverId][secondDriverPassengerIdx];
    long long scoreIncrease =
        getDistance(passengers[prevPassengerId].arrival, passengers[removePassengerId].departure)
        + getPassengerDist(passengers[removePassengerId])
        + getDistance(passengers[removePassengerId].arrival, passengers[curPassengerId].departure)
        - getDistance(passengers[prevPassengerId].arrival, passengers[curPassengerId].departure);
    for (register int idx = passengerSize[secondDriverId]; secondDriverPassengerIdx <= idx; --idx) {
        passengerIds[secondDriverId][idx] = passengerIds[secondDriverId][idx - 1];
    }
    passengerIds[secondDriverId][secondDriverPassengerIdx] = removePassengerId;
    ++passengerSize[secondDriverId];
    scores[secondDriverId] += scoreIncrease;
}

bool minMaxSwap(int driverCount, Passenger passengers[]) {
    int maxScoreDriverId = getMaxScoreDriverId(driverCount);
    int minScoreDriverId = getMinScoreDriverId(driverCount);
    long long maxScore = scores[maxScoreDriverId];
    long long minScore = scores[minScoreDriverId];

    int maxScoreSwapPassengerIdx = -1;
    int minScoreSwapPassengerIdx = -1;

    long long minScoreIncrease = INF;
    for (register int maxIdx = 1; maxIdx < passengerSize[maxScoreDriverId] - 1; ++maxIdx) {
        int addPassengerId = passengerIds[maxScoreDriverId][maxIdx];
        for (register int minIdx = 1; minIdx < passengerSize[minScoreDriverId] - 1; ++minIdx) {
            int prevPassengerId = passengerIds[minScoreDriverId][minIdx - 1];
            int curPassengerId = passengerIds[minScoreDriverId][minIdx];
            long long scoreIncrease =
                getDistance(passengers[prevPassengerId].arrival, passengers[addPassengerId].departure)
                + getPassengerDist(passengers[addPassengerId])
                + getDistance(passengers[addPassengerId].arrival, passengers[curPassengerId].departure)
                - getDistance(passengers[prevPassengerId].arrival, passengers[curPassengerId].departure);
            if (scoreIncrease < minScoreIncrease  && minScore + scoreIncrease < maxScore) {
                minScoreIncrease = scoreIncrease;
                maxScoreSwapPassengerIdx = maxIdx;
                minScoreSwapPassengerIdx = minIdx;
            }
        }
    }
    
    if (maxScoreSwapPassengerIdx < 0 || minScoreSwapPassengerIdx < 0) {
        return false;
    }
    swapDriveCourse(passengers, maxScoreDriverId, maxScoreSwapPassengerIdx, minScoreDriverId, minScoreSwapPassengerIdx);
    return true;
}

void run(int AN, int driverCount, Coordinate drivers[], int passengerCount, Passenger passengers[]) {
    for (register int i = 0; i < driverCount; ++i) {
        scores[i] = 0;
        passengerSize[i] = 0;
    }

    for (register int passengerId = 0; passengerId < passengerCount; ++passengerId) {
        isPassengerAssigned[passengerId] = false;
        passengerDist[passengerId] = getPassengerDist(passengers[passengerId]);
        passengerDistIds[passengerId] = passengerId;
    }
    sort(passengerDist, passengerDistIds, 0, passengerCount - 1);

    numOfKeepMinDist = driverCount * 5;// driverCount * 5;
    int driverId;
    int passengerId;

    for (register int i = 0; i < passengerCount; ++i) {
        if (i + numOfKeepMinDist < passengerCount) {
            driverId = getDriver(driverCount);
            passengerId = getPassenger(drivers[driverId], passengers, passengerCount);
        }
        else {
            getDriverPassengerPair(driverId, passengerId, driverCount, drivers, passengerCount, passengers);
        }
        if (isPassengerAssigned[passengerId]) {
            printf("assigned passenger %d", passengerId);
            break;
        }
        scores[driverId] += (getDistance(drivers[driverId], passengers[passengerId].departure) + getPassengerDist(passengers[passengerId]));
        passengerIds[driverId][passengerSize[driverId]++] = passengerId;
        isPassengerAssigned[passengerId] = true;
        drivers[driverId] = passengers[passengerId].arrival;
    }

    printScoreMinMax(driverCount, passengerCount, false);
    for (register int i = 0; i < minMaxSwapCount; ++i) {
        bool result = minMaxSwap(driverCount, passengers);
        if (!result) {
            printf("minMaxSwap end index: %d\n", i);
            break;
        }
    }
    
    for (register int driverId = 0; driverId < driverCount; ++driverId) {
        assign_driver(driverId, passengerSize[driverId], passengerIds[driverId]);
    }

    printScoreMinMax(driverCount, passengerCount, true);
}


/*


numOfKeepMinDist = driverCount * 5;
numOfKeepMinDist: 475
driverCount: 95,        passnegerCount: 5303,   totalPairs: 503785,     max_score: 39420905,    min_score: 37461898,   score diff: 1959007
TC #0 SCORE: 39420905, 0.320000 sec
numOfKeepMinDist: 395
driverCount: 79,        passnegerCount: 9482,   totalPairs: 749078,     max_score: 83258250,    min_score: 81429143,   score diff: 1829107
TC #1 SCORE: 83258250, 0.755000 sec
numOfKeepMinDist: 300
driverCount: 60,        passnegerCount: 9230,   totalPairs: 553800,     max_score: 107378015,   min_score: 105260512,  score diff: 2117503
TC #2 SCORE: 107378015, 0.642000 sec
numOfKeepMinDist: 325
driverCount: 65,        passnegerCount: 8133,   totalPairs: 528645,     max_score: 87690946,    min_score: 85616154,   score diff: 2074792
TC #3 SCORE: 87690946, 0.517000 sec
numOfKeepMinDist: 300
driverCount: 60,        passnegerCount: 9919,   totalPairs: 595140,     max_score: 115101169,   min_score: 113119118,  score diff: 1982051
TC #4 SCORE: 115101169, 0.583000 sec
PASS
TOTAL SCORE: 432849285, 2.829000 sec
*/