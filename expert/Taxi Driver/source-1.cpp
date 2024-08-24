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

long long passengerMinDist[MAX_PASSENGER_COUNT];

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

long long distSumAvg;

int getPassenger(Coordinate drivers[], int driverId, Passenger passengers[], int passengerCount) {
    int selectedPassengerId = -1;
    long long minDist = INF;
    long long minPathDist = INF;
    for (register int passengerIdx = numOfKeepMinDist; passengerIdx < passengerCount; ++passengerIdx) {
        int passengerId = passengerDistIds[passengerIdx];
        if (isPassengerAssigned[passengerId]) {
            continue;
        }
        long long dist = getDistance(drivers[driverId], passengers[passengerId].departure);
        if (0 < passengerSize[driverId]) {
            dist += passengerMinDist[passengerId];
        }

        long long pathDist = passengerDist[passengerId];
        if (((dist < minDist) || (dist == minDist && pathDist < minPathDist))
            && (scores[driverId] + dist + pathDist < distSumAvg)) {
            minDist = dist;
            minPathDist = pathDist;
            selectedPassengerId = passengerId;
        }
    }
    if (0 < selectedPassengerId) {
        return selectedPassengerId;
    }
    minDist = INF;
    minPathDist = INF;
    for (register int passengerIdx = numOfKeepMinDist; passengerIdx < passengerCount; ++passengerIdx) {
        int passengerId = passengerDistIds[passengerIdx];
        if (isPassengerAssigned[passengerId]) {
            continue;
        }
        long long dist = getDistance(drivers[driverId], passengers[passengerId].departure);
        if (0 < passengerSize[driverId]) {
            dist += passengerMinDist[passengerId];
        }

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

long long getDiffScoreAfterRemovePassenger(Passenger passengers[], int driverId, int removePassengerIdx) {
    int prevPassengerId = passengerIds[driverId][removePassengerIdx - 1];
    int removePassengerId = passengerIds[driverId][removePassengerIdx];
    int nextPassengerId = passengerIds[driverId][removePassengerIdx + 1];
    return  getDistance(passengers[prevPassengerId].arrival, passengers[nextPassengerId].departure)
        - getDistance(passengers[prevPassengerId].arrival, passengers[removePassengerId].departure)
        - getPassengerDist(passengers[removePassengerId])
        - getDistance(passengers[removePassengerId].arrival, passengers[nextPassengerId].departure);
}

long long getDiffScoreAfterAddPassenger(Passenger passengers[], int driverId, int addPassengerIdx, int addPassengerId) {
    int prevPassengerId = passengerIds[driverId][addPassengerIdx - 1];
    int curPassengerId = passengerIds[driverId][addPassengerIdx];
    return  getDistance(passengers[prevPassengerId].arrival, passengers[addPassengerId].departure)
        + getPassengerDist(passengers[addPassengerId])
        + getDistance(passengers[addPassengerId].arrival, passengers[curPassengerId].departure)
        - getDistance(passengers[prevPassengerId].arrival, passengers[curPassengerId].departure);;
}

void swapDriveCourse(Passenger passengers[], int firstDriverId, int firstDriverPassengerIdx, int secondDriverId, int secondDriverPassengerIdx) {
    int prevPassengerId = passengerIds[firstDriverId][firstDriverPassengerIdx - 1];
    int removePassengerId = passengerIds[firstDriverId][firstDriverPassengerIdx];
    int nextPassengerId = passengerIds[firstDriverId][firstDriverPassengerIdx + 1];
    long long reducedScore = getDiffScoreAfterRemovePassenger(passengers, firstDriverId, firstDriverPassengerIdx);
    for (register int idx = firstDriverPassengerIdx; idx < passengerSize[firstDriverId]; ++idx) {
        passengerIds[firstDriverId][idx] = passengerIds[firstDriverId][idx + 1];
    }
    --passengerSize[firstDriverId];
    scores[firstDriverId] += reducedScore;

    prevPassengerId = passengerIds[secondDriverId][secondDriverPassengerIdx - 1];
    int curPassengerId = passengerIds[secondDriverId][secondDriverPassengerIdx];
    long long scoreIncrease = getDiffScoreAfterAddPassenger(passengers, secondDriverId, secondDriverPassengerIdx, removePassengerId);
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
            long long scoreIncrease = getDiffScoreAfterAddPassenger(passengers, minScoreDriverId, minIdx, addPassengerId);
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

#include <stdio.h>


void run(int AN, int driverCount, Coordinate drivers[], int passengerCount, Passenger passengers[]) {
    for (register int i = 0; i < driverCount; ++i) {
        scores[i] = 0;
        passengerSize[i] = 0;
    }

    long long distSum = 0;
    for (register int passengerId = 0; passengerId < passengerCount; ++passengerId) {
        isPassengerAssigned[passengerId] = false;
        passengerDist[passengerId] = getPassengerDist(passengers[passengerId]);
        passengerDistIds[passengerId] = passengerId;
        distSum += passengerDist[passengerId];
    }
    distSumAvg = distSum / driverCount;
    printf("%lld\n", distSumAvg);
    sort(passengerDist, passengerDistIds, 0, passengerCount - 1);

    for (register int passengerId = 0; passengerId < passengerCount; ++passengerId) {
        passengerMinDist[passengerId] = INF;
        for (register int passengerFromId = 0; passengerFromId < passengerCount; ++passengerFromId) {
            if (passengerFromId == passengerId) {
                continue;
            }
            long long dist = getDistance(passengers[passengerId].departure, passengers[passengerFromId].arrival);
            passengerMinDist[passengerId] = passengerMinDist[passengerId] < dist ? passengerMinDist[passengerId] : dist;
        }
    }

    numOfKeepMinDist = driverCount * 5;

    
    int driverId;
    int passengerId;

    for (register int i = 0; i < passengerCount; ++i) {
        if (i + numOfKeepMinDist < passengerCount) {
            driverId = getDriver(driverCount);
            passengerId = getPassenger(drivers, driverId, passengers, passengerCount);
        }
        else {
            getDriverPassengerPair(driverId, passengerId, driverCount, drivers, passengerCount, passengers);
        }
        if (isPassengerAssigned[passengerId]) {
            break;
        }
        scores[driverId] += (getDistance(drivers[driverId], passengers[passengerId].departure) + getPassengerDist(passengers[passengerId]));
        passengerIds[driverId][passengerSize[driverId]++] = passengerId;
        isPassengerAssigned[passengerId] = true;
        drivers[driverId] = passengers[passengerId].arrival;
    }
    for (register int i = 0; i < minMaxSwapCount; ++i) {
        if (!minMaxSwap(driverCount, passengers)) {
            break;
        }
    }

    for (register int driverId = 0; driverId < driverCount; ++driverId) {
        assign_driver(driverId, passengerSize[driverId], passengerIds[driverId]);
    }
}