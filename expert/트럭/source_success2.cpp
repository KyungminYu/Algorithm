#include <stdio.h>

#define ABS(x) ((x) > 0 ? (x) : -(x))

struct Coordinates {
    int y;
    int x;

    Coordinates() { y = x = 0; }
    Coordinates(int _y, int _x) {
        y = _y;
        x = _x;
    }

    int operator-(Coordinates& param) {
        return ABS(y - param.y) + ABS(x - param.x);
    }
};

struct Product {
    int id;
    int count;

    Product() { id = count = 0; }
    Product(int _id, int _count) {
        id = _id;
        count = _count;
    }
};

extern int truckMove(int);
extern int truckLoading(int, int[], int);

#define NUM_OF_CENTER        1000
#define NUM_OF_PRODUCT_TYPE  10000
#define NUM_OF_DELIVERY      1000000
#define MAX_TRUCK_LOADING    30

Coordinates* centerPos;
int productToCenterCount[NUM_OF_PRODUCT_TYPE][NUM_OF_CENTER];

void sendCenterList(int N, int M, Coordinates centerCoordinatesList[], Product centerProductList[][100], int centerProductSize[]) {
    centerPos = centerCoordinatesList;
    for (register int centerId = 0; centerId < NUM_OF_CENTER; ++centerId) {
        Product* products = centerProductList[centerId];
        for (register int productIdx = 0; productIdx < centerProductSize[centerId]; ++productIdx) {
            productToCenterCount[products[productIdx].id][centerId] += products[productIdx].count;
        }
    }
}

#define MAX_ALLOC_DELIVERY_COUNT 10000
Coordinates* deliveryPos;
int* deliveryProducts;
int centerToDelivery[NUM_OF_CENTER][MAX_ALLOC_DELIVERY_COUNT];
int centerToDeliveryCount[NUM_OF_CENTER];

void sendDeliveryList(int K, Coordinates deliveryCoordinatesList[], int deliveryProductList[]) {
    deliveryPos = deliveryCoordinatesList;
    deliveryProducts = deliveryProductList;
    for (register int deliveryId = 0; deliveryId < NUM_OF_DELIVERY; ++deliveryId) {
        int productId = deliveryProducts[deliveryId];
        Coordinates curDeliveryPos = deliveryPos[deliveryId];
        int nearestCenterId = -1;
        int minDist = 1e9;
        for (register int centerId = 0; centerId < NUM_OF_CENTER; ++centerId) {
            if (productToCenterCount[productId][centerId] <= 0) {
                continue;
            }
            int dist = centerPos[centerId] - curDeliveryPos;
            if (dist < minDist) {
                minDist = dist;
                nearestCenterId = centerId;
            }
        }
        if (nearestCenterId < 0) {
            continue;
        }
        centerToDelivery[nearestCenterId][centerToDeliveryCount[nearestCenterId]++] = deliveryId;
        --productToCenterCount[productId][nearestCenterId];
    }
}

Coordinates trucPos;

void solve(Coordinates truckCoordinates) {
    trucPos = truckCoordinates;
    int deliveryCount = 0;
    int loopCount = 0;
    while (deliveryCount < NUM_OF_DELIVERY) {
        // 1. 현위치에서 가장 가까운 Center 찾기
        int nearestCenterId = -1;
        int minDist = 1e9;
        for (register int centerId = 0; centerId < NUM_OF_CENTER; ++centerId) {
            if (centerToDeliveryCount[centerId] <= 0) {
                continue;
            }
            int dist = centerPos[centerId] - trucPos;
            if (dist < minDist) {
                minDist = dist;
                nearestCenterId = centerId;
            }
        }
        if (nearestCenterId < 0) {
            break;
        }
        //2. Vertual Truck Loadnig and Move
        //해당 Center가 갈 수 있는 Delivery를 가까운 순으로 50개 미만 할당
        //    product -> delivery List 만들기
        //    deliveryList중 가까운것 선택
        int listSize = 0;
        int packages[MAX_TRUCK_LOADING];
        int deliveries[MAX_TRUCK_LOADING];
        trucPos = centerPos[nearestCenterId];
        while (listSize < MAX_TRUCK_LOADING 
            && deliveryCount + listSize < NUM_OF_DELIVERY 
            && 0 < centerToDeliveryCount[nearestCenterId]) {
            int nearestDeliveryIdx = -1;
            int deliveryId = -1;
            int minDist = 1e9;
            for (int deliveryIdx = 0; deliveryIdx < centerToDeliveryCount[nearestCenterId]; ++deliveryIdx) {
                deliveryId = centerToDelivery[nearestCenterId][deliveryIdx];
                if (deliveryProducts[deliveryId] < 0) {
                    continue;
                }
                int dist = trucPos - deliveryPos[deliveryId];
                if (dist < minDist) {
                    minDist = dist;
                    nearestDeliveryIdx = deliveryIdx;
                }
            }
            deliveryId = centerToDelivery[nearestCenterId][nearestDeliveryIdx];
            int productId = deliveryProducts[deliveryId];
            packages[listSize] = productId;
            deliveries[listSize++] = deliveryId;
            deliveryProducts[deliveryId] = -1;
            centerToDelivery[nearestCenterId][nearestDeliveryIdx] = centerToDelivery[nearestCenterId][--centerToDeliveryCount[nearestCenterId]];
        }

        if (listSize <= 0) {
            break;
        }
        //3. TruckLoading
        truckLoading(nearestCenterId, packages, listSize);
        //4. TruckMove
        for (register int idx = 0; idx < listSize; ++idx) {
            truckMove(deliveries[idx]);
        }
        deliveryCount += listSize;
        ++loopCount;

        if (loopCount % 1000 == 0) {
            int successCenterCount = 0;
            for (int centerId = 0; centerId < NUM_OF_CENTER; ++centerId) {
                if (centerToDeliveryCount[centerId] == 0) {
                    successCenterCount++;
                }
            }


            printf("%d\t%d\t%d, nearestCenterId: %d, x, y: (%d ,%d)nyang: %d\n", loopCount, listSize, deliveryCount, nearestCenterId, centerPos[nearestCenterId].y, centerPos[nearestCenterId].x, successCenterCount);
        }
    }
}
