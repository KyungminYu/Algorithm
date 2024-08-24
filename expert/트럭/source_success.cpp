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


#define CENTER_SIZE 1'000
#define PRODUCT_SIZE 10'000
#define DELIVERY_SIZE 1'000'000
#define MAX_LOADING_SIZE 30

Coordinates* centerPos;
int centerPerProductCount[CENTER_SIZE][PRODUCT_SIZE];

void sendCenterList(int N, int M, Coordinates centerCoordinatesList[], Product centerProductList[][100], int centerProductSize[]) {
    printf("sendCenterList - start\n");
    centerPos = centerCoordinatesList;
    for (register int centerId = 0; centerId < CENTER_SIZE; ++centerId) {
        Product* productList = centerProductList[centerId];
        for (register int idx = 0; idx < centerProductSize[centerId]; ++idx) {
            centerPerProductCount[centerId][productList[idx].id] += productList[idx].count;
        }
    }
    printf("sendCenterList - end\n");
}

Coordinates* deliveryPos;
int* deliveryProducts;
int deliveryToCenter[DELIVERY_SIZE];
int centerDeliveries[CENTER_SIZE][PRODUCT_SIZE * 10];
int centerDeliveryCount[CENTER_SIZE];

int findNearestProductRemainedCenterId(int deliveryId, int productId) {
    int nearestCenterId = -1;
    int minDist = 1e9;
    for (register int centerId = 0; centerId < CENTER_SIZE; ++centerId) {
        if (centerPerProductCount[centerId][productId] <= 0) {
            continue;
        }
        int dist = centerPos[centerId] - deliveryPos[deliveryId];
        if (dist < minDist) {
            minDist = dist;
            nearestCenterId = centerId;
        }
    }
    return nearestCenterId;
}

void sendDeliveryList(int K, Coordinates deliveryCoordinatesList[], int deliveryProductList[]) {
    printf("sendDeliveryList - start\n");
    deliveryPos = deliveryCoordinatesList;
    deliveryProducts = deliveryProductList;
    for (register int deliveryId = 0; deliveryId < DELIVERY_SIZE; ++deliveryId) {
        int productId = deliveryProductList[deliveryId];
        int nearestCenterId = findNearestProductRemainedCenterId(deliveryId, productId);
        --centerPerProductCount[nearestCenterId][productId];
        deliveryToCenter[deliveryId] = nearestCenterId;
        centerDeliveries[nearestCenterId][centerDeliveryCount[nearestCenterId]++] = deliveryId;
    }
    printf("sendDeliveryList - end\n");
}

struct TrunkInfo {
    int deliveredCount;
    int centerId;
    int deliverIds[MAX_LOADING_SIZE];
    int productIds[MAX_LOADING_SIZE];
    int size;

    void addDeliveryInfo(int deliveryId, int productId) {
        deliverIds[size] = deliveryId;
        productIds[size++] = productId;
    }
};
Coordinates currentPos;

void updateNearestCenterIdFromPos(Coordinates &pos, TrunkInfo& info) {
    int nearestCenterId = info.centerId;
    int minDist = 1e9;
    for (register int centerId = 0; centerId < CENTER_SIZE; ++centerId) {
        if (centerDeliveryCount[centerId] <= 0) {
            continue;
        }
        int dist = pos - centerPos[centerId];
        if (dist < minDist) {
            minDist = dist;
            nearestCenterId = centerId;
        }
    }
    info.centerId = nearestCenterId;
}

void packaging(TrunkInfo& info) {
    info.size = 0;
    currentPos = centerPos[info.centerId];
    while (info.size < MAX_LOADING_SIZE && info.deliveredCount + info.size <= DELIVERY_SIZE) {
        int nearestDeliveryIdx = -1;
        int nearestDeliveryId = -1;
        int minDist = 1e9;
        int size = centerDeliveryCount[info.centerId];
        for (register int deliveryIdx = 0; deliveryIdx < size; ++deliveryIdx) {
            int deliveryId = centerDeliveries[info.centerId][deliveryIdx];
            int dist = currentPos - deliveryPos[deliveryId];
            if (dist < minDist) {
                minDist = dist;
                nearestDeliveryId = deliveryId;
                nearestDeliveryIdx = deliveryIdx;
            }
        }
        if (nearestDeliveryId < 0) {
            break;
        }
        info.addDeliveryInfo(nearestDeliveryId, deliveryProducts[nearestDeliveryId]);
        centerDeliveries[info.centerId][nearestDeliveryIdx] = centerDeliveries[info.centerId][--centerDeliveryCount[info.centerId]];
        currentPos = deliveryPos[nearestDeliveryId];
    }
}

void solve(Coordinates truckCoordinates) {
    printf("solve - start\n");
    currentPos = truckCoordinates;
    TrunkInfo info;
    info.deliveredCount = 0;
    int loopCount = 0;
    while (info.deliveredCount < DELIVERY_SIZE) {
        // 1. 가까운 Center 찾기
        updateNearestCenterIdFromPos(currentPos, info);
        // 2. 물건 Loading
        packaging(info);
        truckLoading(info.centerId, info.productIds, info.size);
        // 3. 물건 Move
        for (register int deliveryIdx = 0; deliveryIdx < info.size; ++deliveryIdx) {
            truckMove(info.deliverIds[deliveryIdx]);
        }
        info.deliveredCount += info.size;
        loopCount++;
        if (loopCount % 10000 == 0) 
            printf("solve - nearestCenterId: %d, packageCount: %d, deliveryCount: %d, loopCount: %d\n", info.centerId, info.size, info.deliveredCount, loopCount);
    }
}
