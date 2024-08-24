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
static const int MAX_DRIVER_PASSENGER_PAIR = 10000;

Coordinate* driversPos;
Passenger* passengersPos;

Coordinate initialDrivers[MAX_DRIVER_COUNT];

int strategyStep;
int remainedPassenger;

int passengerDistIds[MAX_PASSENGER_COUNT];
long long passengerDist[MAX_PASSENGER_COUNT];

bool isPassengerAssigned[MAX_PASSENGER_COUNT];
int passengerSize[MAX_DRIVER_COUNT];
int passengerIds[MAX_DRIVER_COUNT][MAX_PASSENGER_COUNT];
long long passengerInboundMinMovement[MAX_PASSENGER_COUNT];

long long scores[MAX_DRIVER_COUNT];
int scoreIds[MAX_DRIVER_COUNT];

int numOfKeepMinDist = 200;


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

long long getDistance(Coordinate& pos1, Coordinate& pos2) {
    return ABS(pos1.y - pos2.y) + ABS(pos1.x - pos2.x);
}

long long getPassengerDist(int passengerId) {
    return getDistance(passengersPos[passengerId].departure, passengersPos[passengerId].arrival);
}

long long getEmptyMovement(int driverId, int passengerId) {
    return getDistance(driversPos[driverId], passengersPos[passengerId].departure);
}

void initDriverinfo(int driverCount, Coordinate drivers[]) {
    driversPos = drivers;
    for (register int i = 0; i < driverCount; ++i) {
        scores[i] = passengerSize[i] = 0;
        scoreIds[i] = i;
    }
}

void initPassengerinfo(int passengerCount, Passenger passengers[]) {
    passengersPos = passengers;
    remainedPassenger = passengerCount;
    for (register int i = 0; i < passengerCount; ++i) {
        passengerDist[i] = getPassengerDist(i);
        passengerDistIds[i] = i;
        isPassengerAssigned[i] = false;
        passengerInboundMinMovement[i] = INF;
        for (register int j = 0; j < passengerCount; ++j) {
            if (i == j) {
                continue;
            }
            int emptyMovement = getDistance(passengersPos[j].arrival, passengersPos[i].departure);
        }
    }
    sort(passengerDist, passengerDistIds, 0, passengerCount - 1);
}

void initInboundMinMovement(int driverCount, int passengerCount) {
    for (register int i = 0; i < passengerCount; ++i) {
        if (isPassengerAssigned[i]) {
            continue;
        }
        passengerInboundMinMovement[i] = INF;
        for (register int j = 0; j < passengerCount; ++j) {
            if (i == j || isPassengerAssigned[j]) {
                continue;
            }
            int emptyMovement = getDistance(passengersPos[j].arrival, passengersPos[i].departure);
            if (emptyMovement < passengerInboundMinMovement[i]) {
                passengerInboundMinMovement[i] = emptyMovement;
            }
        }
    }
}

void assignPassengerToDriver(int driverId, int passengerId) {
    scores[driverId] += (getDistance(driversPos[driverId], passengersPos[passengerId].departure) + getPassengerDist(passengerId));
    passengerIds[driverId][passengerSize[driverId]++] = passengerId;
    isPassengerAssigned[passengerId] = true;
    if (passengerSize[driverId] == 1) {
        initialDrivers[driverId] = driversPos[driverId];
    }
    driversPos[driverId] = passengersPos[passengerId].arrival;
    --remainedPassenger;
}

int getMinScoreDriver(int driverCount) {
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
    return scores[getMinScoreDriver(driverCount)];
}

long long getMaxScoreDriver(int driverCount) {
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
    return scores[getMaxScoreDriver(driverCount)];
}

int getPassenger(int driverId, int driverCount, int passengerCount, bool checkMaxScore) {

    int maxScoreDriverId = getMaxScoreDriver(driverCount);
    long long minEmptyMovement = INF;
    long long minPassengerDist = INF;
    long long minMovement = INF;

    int targetPassengerId = -1;
    for (register int passengerIdx = numOfKeepMinDist; passengerIdx < passengerCount; ++passengerIdx) {
        int passengerId = passengerDistIds[passengerIdx];
        if (isPassengerAssigned[passengerId]) {
            continue;
        }
        long long emptyMovement = getEmptyMovement(driverId, passengerId);
        long long passengerDist = getPassengerDist(passengerId);
        if (checkMaxScore) {
            long long score = scores[driverId] + emptyMovement + passengerCount;
            if (scores[maxScoreDriverId] < score) {
                continue;
            }
        }
        long long movement = emptyMovement - passengerInboundMinMovement[passengerId];
        if (emptyMovement < minEmptyMovement) {
            minEmptyMovement = emptyMovement;
            minPassengerDist = passengerDist;
            minMovement = movement;
            targetPassengerId = passengerId;
        }
        else if (emptyMovement == minEmptyMovement) {
            if (passengerDist < minPassengerDist) {
                minPassengerDist = passengerDist;
                minMovement = movement;
                targetPassengerId = passengerId;
            }
            else if (passengerDist == minPassengerDist) {
                if (movement < minMovement) {
                    minMovement = movement;
                    targetPassengerId = passengerId;
                }
            }
        }
    }
    if (targetPassengerId < 0) {
        targetPassengerId = getPassenger(driverId, driverCount, passengerCount, false);
    }
    return targetPassengerId;
}

int getPassenger(int driverId, int driverCount, int passengerCount) {
    return getPassenger(driverId, driverCount, passengerCount, true);
}

void assignPassengerToMinScoreDriver(int driverCount, int passengerCount) {
    int driverId;
    int passengerId;
    while (numOfKeepMinDist < remainedPassenger) {
        driverId = getMinScoreDriver(driverCount);
        passengerId = getPassenger(driverId, driverCount, passengerCount);
        assignPassengerToDriver(driverId, passengerId);
    }
}

void updateDriverPassengerPair(int& driverId, int& passengerId, int driverCount, int passengerCount, bool checkMaxScore) {
    passengerId = driverId = -1;
    int maxScoreDriverId = getMaxScoreDriver(driverCount);
    long long maxScore = scores[maxScoreDriverId];
    long long minEmptyMovement = INF;
    long long minPassengerDist = INF;
    long long minMovement = INF;

    for (register int pidx = 0; pidx < numOfKeepMinDist; ++pidx) {
        int pid = passengerDistIds[pidx];
        if (isPassengerAssigned[pid]) {
            continue;
        }
        for (register int did = 0; did < driverCount; ++did) {
            if (!checkMaxScore && did == maxScoreDriverId) {
                continue;
            }
            long long emptyMovement = getEmptyMovement(did, pid);
            long long passengerDist = getPassengerDist(pid);
            if (checkMaxScore) {
                long long score = scores[did] + emptyMovement + passengerDist;
                if (maxScore <= score) {
                    continue;
                }
            }
            long long movement = emptyMovement - passengerInboundMinMovement[pid];


            if (emptyMovement < minEmptyMovement) {
                minEmptyMovement = emptyMovement;
                minPassengerDist = passengerDist;
                minMovement = movement;
                driverId = did;
                passengerId = pid;
            }
            else if (emptyMovement == minEmptyMovement) {
                if (passengerDist < minPassengerDist) {
                    minEmptyMovement = emptyMovement;
                    minPassengerDist = passengerDist;
                    minMovement = movement;
                    driverId = did;
                    passengerId = pid;
                }
                else if (passengerDist == minPassengerDist) {
                    if (movement < minMovement) {
                        minEmptyMovement = emptyMovement;
                        minPassengerDist = passengerDist;
                        minMovement = movement;
                        driverId = did;
                        passengerId = pid;
                    }
                }
            }
        }
    }
    if (0 <= passengerId) {
        return;
    }
    updateDriverPassengerPair(driverId, passengerId, driverCount, passengerCount, false);
}

void updateDriverPassengerPair(int& driverId, int& passengerId, int driverCount, int passengerCount) {
    updateDriverPassengerPair(driverId, passengerId, driverCount, passengerCount, true);
}

void assignPassengerToDriverWithPairId(int driverCount, int passengerCount) {
    int driverId;
    int passengerId;
    while (numOfKeepMinDist < remainedPassenger) {
        updateDriverPassengerPair(driverId, passengerId, driverCount, passengerCount);
        assignPassengerToDriver(driverId, passengerId);
    }
}

void updateDriverPassengerPairMinScore(int& driverId, int& passengerId, int driverCount, int passengerCount, bool checkMaxScore) {
    passengerId = driverId = -1;
    int maxScoreDriverId = getMaxScoreDriver(driverCount);
    long long maxScore = scores[maxScoreDriverId];
    long long minScore = INF;
    long long minEmptyMovement = INF;
    long long minPassengerDist = INF;
    long long minMovement = INF;

    for (register int pidx = 0; pidx < numOfKeepMinDist; ++pidx) {
        int pid = passengerDistIds[pidx];
        if (isPassengerAssigned[pid]) {
            continue;
        }
        for (register int did = 0; did < driverCount; ++did) {
            if (!checkMaxScore && did == maxScoreDriverId) {
                continue;
            }
            long long score = scores[did] + getEmptyMovement(did, pid) + getPassengerDist(pid);
            if (checkMaxScore) {
                if (maxScore <= score) {
                    continue;
                }
            }
            long long emptyMovement = getEmptyMovement(did, pid);
            long long passengerDist = getPassengerDist(pid);
            long long movement = emptyMovement - passengerInboundMinMovement[pid];
            if (score < minScore) {
                minScore = score;
                minEmptyMovement = emptyMovement;
                minPassengerDist = passengerDist;
                minMovement = movement;
                driverId = did;
                passengerId = pid;
            }
            else if (score == minScore) {
                if (emptyMovement < minEmptyMovement) {
                    minScore = score;
                    minEmptyMovement = emptyMovement;
                    minPassengerDist = passengerDist;
                    minMovement = movement;
                    driverId = did;
                    passengerId = pid;
                }
                else if (emptyMovement == minEmptyMovement) {
                    if (passengerDist < minPassengerDist) {
                        minScore = score;
                        minEmptyMovement = emptyMovement;
                        minPassengerDist = passengerDist;
                        minMovement = movement;
                        driverId = did;
                        passengerId = pid;
                    }
                    else if (passengerDist == minPassengerDist) {
                        if (movement < minMovement) {
                            minScore = score;
                            minEmptyMovement = emptyMovement;
                            minPassengerDist = passengerDist;
                            minMovement = movement;
                            driverId = did;
                            passengerId = pid;
                        }
                    }
                }
            }
        }
    }
    if (0 <= passengerId) {
        return;
    }
    updateDriverPassengerPairMinScore(driverId, passengerId, driverCount, passengerCount, false);
}

void updateDriverPassengerPairMinScore(int& driverId, int& passengerId, int driverCount, int passengerCount) {
    updateDriverPassengerPairMinScore(driverId, passengerId, driverCount, passengerCount, true);
}

void assignPassengerToDriverWithPairIdMinScore(int driverCount, int passengerCount) {
    int driverId;
    int passengerId;
    while (0 < remainedPassenger) {
        updateDriverPassengerPairMinScore(driverId, passengerId, driverCount, passengerCount);
        assignPassengerToDriver(driverId, passengerId);
    }
}

long long getReducingScore(int driverId, int removingPassengerIdx) {
    int prevPassengerId = removingPassengerIdx < 0 ? -1 : passengerIds[driverId][removingPassengerIdx - 1];
    int removePassengerId = passengerIds[driverId][removingPassengerIdx];
    int nextPassengerId = passengerSize[driverId] <= removingPassengerIdx + 1 ? -1 :  passengerIds[driverId][removingPassengerIdx + 1];
    
    if (0 < prevPassengerId && 0 < nextPassengerId) {
        return getDistance(passengersPos[prevPassengerId].arrival, passengersPos[nextPassengerId].departure)
            - getDistance(passengersPos[prevPassengerId].arrival, passengersPos[removePassengerId].departure)
            - getPassengerDist(removePassengerId)
            - getDistance(passengersPos[removePassengerId].arrival, passengersPos[nextPassengerId].departure);
    }
    else if (0 < prevPassengerId) {
        return -getDistance(passengersPos[prevPassengerId].arrival, passengersPos[removePassengerId].departure)
            - getPassengerDist(removePassengerId);
    }
    else if (0 < nextPassengerId) { // use next and drop prev
        return 
            getDistance(initialDrivers[driverId], passengersPos[nextPassengerId].departure)
            - getDistance(passengersPos[prevPassengerId].arrival, passengersPos[removePassengerId].departure)
            - getPassengerDist(removePassengerId);
    }
    return - getDistance(passengersPos[prevPassengerId].arrival, passengersPos[removePassengerId].departure)
        - getPassengerDist(removePassengerId);
}

long long getIncreasingScore(int driverId, int insertPassengerIdx, int insertPassengerId) {
    int prevPassengerId = passengerIds[driverId][insertPassengerIdx - 1];
    int curPassengerId = passengerIds[driverId][insertPassengerIdx];
    return getDistance(passengersPos[prevPassengerId].arrival, passengersPos[insertPassengerId].departure)
        + getPassengerDist(insertPassengerId)
        + getDistance(passengersPos[insertPassengerId].arrival, passengersPos[curPassengerId].departure)
        - getDistance(passengersPos[prevPassengerId].arrival, passengersPos[curPassengerId].departure);
}

void swapDriveCourse(int firstDriverId, int firstDriverPassengerIdx, int secondDriverId, int secondDriverPassengerIdx) {
    int insertPassengerId = passengerIds[firstDriverId][firstDriverPassengerIdx];

    long long reducingScore = getReducingScore(firstDriverId, firstDriverPassengerIdx);
    for (register int idx = firstDriverPassengerIdx; idx < passengerSize[firstDriverId]; ++idx) {
        passengerIds[firstDriverId][idx] = passengerIds[firstDriverId][idx + 1];
    }
    --passengerSize[firstDriverId];
    scores[firstDriverId] += reducingScore;

    long long increasingScore = getIncreasingScore(secondDriverId, secondDriverPassengerIdx, insertPassengerId);
    for (register int idx = passengerSize[secondDriverId]; secondDriverPassengerIdx <= idx; --idx) {
        passengerIds[secondDriverId][idx] = passengerIds[secondDriverId][idx - 1];
    }
    passengerIds[secondDriverId][secondDriverPassengerIdx] = insertPassengerId;
    ++passengerSize[secondDriverId];
    scores[secondDriverId] += increasingScore;
}

bool minMaxSwap(int driverCount) {
    int maxScoreDriverId = getMaxScoreDriver(driverCount);
    int minScoreDriverId = getMinScoreDriver(driverCount);
    long long maxScore = scores[maxScoreDriverId];
    long long minScore = scores[minScoreDriverId];

    int maxScoreSwapPassengerIdx = -1;
    int minScoreSwapPassengerIdx = -1;

    long long minIncreasingScore = INF;
    for (register int maxIdx = 0; maxIdx < passengerSize[maxScoreDriverId]; ++maxIdx) {
        int addPassengerId = passengerIds[maxScoreDriverId][maxIdx];
        for (register int minIdx = 0; minIdx < passengerSize[minScoreDriverId]; ++minIdx) {
            long long increasingScore = getIncreasingScore(minScoreDriverId, minIdx, addPassengerId);
            if (increasingScore < minIncreasingScore && minScore + increasingScore < maxScore) {
                minIncreasingScore = increasingScore;
                maxScoreSwapPassengerIdx = maxIdx;
                minScoreSwapPassengerIdx = minIdx;
            }
        }
    }

    if (maxScoreSwapPassengerIdx < 0 || minScoreSwapPassengerIdx < 0) {
        return false;
    }
    swapDriveCourse(maxScoreDriverId, maxScoreSwapPassengerIdx, minScoreDriverId, minScoreSwapPassengerIdx);
    return true;
}


void run(int an, int driverCount, Coordinate drivers[], int passengerCount, Passenger passengers[]) {
    initDriverinfo(driverCount, drivers);
    initPassengerinfo(passengerCount, passengers);
    initInboundMinMovement(driverCount, passengerCount);

    numOfKeepMinDist = driverCount * 5;

    assignPassengerToMinScoreDriver(driverCount, passengerCount);
    assignPassengerToDriverWithPairId(driverCount, passengerCount);
    assignPassengerToDriverWithPairIdMinScore(driverCount, passengerCount);

    while (minMaxSwap(driverCount));

    for (register int driverId = 0; driverId < driverCount; ++driverId) {
        assign_driver(driverId, passengerSize[driverId], passengerIds[driverId]);
    }
}