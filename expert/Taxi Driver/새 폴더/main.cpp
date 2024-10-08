#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <time.h>

static unsigned long long seed = 5;
static int pseudo_rand(void)
{
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

static const int MAX_TC = 5;

/* These constant variables will NOT be changed */
static const int MAP_SIZE = 1'000'000;
static const int MAX_DRIVER_COUNT = 100;
static const int MAX_PASSENGER_COUNT = 10'000;

static const long long PENALTY = 10'000'000'000'000LL;

struct Coordinate
{
    int y, x;
};

struct Passenger
{
    Coordinate departure;
    Coordinate arrival;
};

extern void run(int, int, Coordinate[], int, Passenger[]);

#define ABS(x) (((x) > 0) ? (x) : -(x))

static int driverCnt;
static Coordinate driverList[MAX_DRIVER_COUNT];
static Coordinate driverList_bak[MAX_DRIVER_COUNT];
static int passengerCnt;
static Passenger passengerList[MAX_PASSENGER_COUNT];
static Passenger passengerList_bak[MAX_PASSENGER_COUNT];
static int isFinished[MAX_PASSENGER_COUNT];
static int assignList[MAX_DRIVER_COUNT][MAX_PASSENGER_COUNT];
static int assignListSize[MAX_DRIVER_COUNT];

static long long SCORE = 0;

bool assign_driver(int driverID, int passengerSize, int passengerIDs[])
{
    if (driverID < 0 || driverID >= driverCnt)
    {
        return false;
    }

    if (passengerSize < 0 || passengerSize > MAX_PASSENGER_COUNT)
    {
        return false;
    }

    for (int i = 0; i < passengerSize; i++)
    {
        if (passengerIDs[i] < 0 || passengerIDs[i] >= passengerCnt)
        {
            return false;
        }
    }

    for (int i = 0; i < passengerSize; i++)
    {
        assignList[driverID][i] = passengerIDs[i];
    }
    assignListSize[driverID] = passengerSize;

    return true;
}

static void make_tc()
{
    driverCnt = pseudo_rand() % 50 + 51;
    passengerCnt = pseudo_rand() % 5000 + 5001;

    for (int i = 0; i < driverCnt; i++)
    {
        driverList[i].y = driverList_bak[i].y = pseudo_rand() % MAP_SIZE;
        driverList[i].x = driverList_bak[i].x = pseudo_rand() % MAP_SIZE;
        assignListSize[i] = 0;
    }

    for (int i = 0; i < passengerCnt; i++)
    {
        passengerList[i].departure.y = passengerList_bak[i].departure.y = pseudo_rand() % MAP_SIZE;
        passengerList[i].departure.x = passengerList_bak[i].departure.x = pseudo_rand() % MAP_SIZE;
        passengerList[i].arrival.y = passengerList_bak[i].arrival.y = pseudo_rand() % MAP_SIZE;
        passengerList[i].arrival.x = passengerList_bak[i].arrival.x = pseudo_rand() % MAP_SIZE;
        isFinished[i] = 0;
    }
}

long long TC_SCORE = 0;
static bool verify()
{
    TC_SCORE = 0;
    for (int i = 0; i < driverCnt; i++)
    {
        Coordinate driverPos = driverList[i];
        long long score = 0;
        for (int j = 0; j < assignListSize[i]; j++)
        {
            int passengerID = assignList[i][j];
            Coordinate pickUp = passengerList[passengerID].departure;
            Coordinate dropOff = passengerList[passengerID].arrival;

            if (isFinished[passengerID] == 1)
            {
                return false;
            }

            score += ABS(pickUp.y - driverPos.y) + ABS(pickUp.x - driverPos.x) + ABS(dropOff.y - pickUp.y) + ABS(dropOff.x - pickUp.x);
            driverPos = dropOff;
            isFinished[passengerID] = 1;
        }
        if (TC_SCORE < score)
        {
            TC_SCORE = score;
        }
    }

    bool flag = true;
    for (int i = 0; i < passengerCnt; i++)
    {
        if (isFinished[i] == 0)
        {
            flag = false;
        }
    }
    if (flag == false)
        return false;

    SCORE += TC_SCORE;
    return true;
}

int main()
{
    setbuf(stdout, NULL);

    clock_t start = clock();
    for (int tc = 0; tc < MAX_TC; tc++)
    {
        clock_t tc_start = clock();
        make_tc();
        run(MAP_SIZE, driverCnt, driverList_bak, passengerCnt, passengerList_bak);
        bool verifyResult = verify();
        clock_t tc_finish = clock();
        double tc_duration = (double)(tc_finish - tc_start) / CLOCKS_PER_SEC;
        if (verifyResult == false)
        {
            printf("FAIL ! \n");
            printf("TC #%d SCORE: %lld, %f sec\n", tc, PENALTY, tc_duration);
            return 0;
        }
        else {
            printf("TC #%d SCORE: %lld, %f sec\n", tc, TC_SCORE, tc_duration);
        }
    }

    clock_t finish = clock();
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    if (SCORE <= 450000000) {
        printf("PASS\n");
        printf("TOTAL SCORE: %lld, %f sec\n\n", SCORE, duration);
    }
    else {
        printf("FAIL, score: %lld, %f sec\n", SCORE, duration);
    }

    return 0;
}