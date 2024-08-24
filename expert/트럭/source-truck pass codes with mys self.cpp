///* SCORE: 9'917'466'570, 8.2s
//          9897221880  
//<문제를 처음 보고 드는 생각>
//변수명 잘지어야함.. cid, did, pid...
//일단 센터랑 배송지랑 연결을 해야겠지?
//일단, 각 센터의 재고를 보고 가까운 센터에 나이브하게 할당해보고 나중에
//최적화해보자. 연결이 다 되었으면, 배송을 시작해야하는데 다음의 순서로 해보자.
//1. 현재 위치에서 가장 가까운 센터를 찾는다.
//2-1. 각 센터에 할당된 배송지를 훑으면서 가까운 배송지를 찾는다.
//2-2. 그 다음 배송지는 2-1에서 선택된 배송지에서 가까운 놈이여야함
//2-3. MAX개만큼 다 채울때까지 반복해보자. MAX는 50이하로 나중에 튜닝.
//3-1. 할당이 마무리되었으면 순서대로 ㄱㄱ
//3-2. 마지막 배송이 끝나면, 그 자리에서 가장 가까운 센터를 찾는다. 1로 돌아가기.
//*/
//
//#define ABS(x) ((x) > 0 ? (x) : -(x))
//
//struct Coordinates {
//    int y;
//    int x;
//
//    Coordinates() { y = x = 0; }
//    Coordinates(int _y, int _x) {
//        y = _y;
//        x = _x;
//    }
//
//    int operator-(Coordinates& param) {
//        return ABS(y - param.y) + ABS(x - param.x);
//    }
//};
//
//struct Product {
//    int id;
//    int count;
//
//    Product() { id = count = 0; }
//    Product(int _id, int _count) {
//        id = _id;
//        count = _count;
//    }
//};
//
//extern int truckMove(int);
//extern int truckLoading(int, int[], int);
//
//#define CENTER 1000
//#define PRODUCT 10000
//#define DELIVER 1000000
//#define INF 1000000000
//#define LIMIT 30
//
//
//////////////////////////// 변수 선언 /////////////////////////////////
//Coordinates* centerPos;
//// c번째 center의 위치
//Coordinates* deliverPos;
//// d번째 배달의 위치
//int mainMatrix[PRODUCT][CENTER];
//// p번째 상품이 c번째 센터에 몇개씩 있는지.
//int deliverInfo[CENTER][PRODUCT];
//// c번째 center에 할당된 배송지 정보
//int deliverInfoSize[CENTER];
//// c번째 center에 할당된 배송지 개수
//int D2C[DELIVER];
//// d번째 배달이 몇번 센터인지?
//int* D2P;
//// d번째 배달이 몇번 물건인지?
//struct _SOLUTION {
//    // truckLoading, truckMove 할때 쓸거
//    int deliverList[50];
//    int productList[50];
//    int size;
//    int center;
//    void alloc(int targetDid) {
//        deliverList[size] = targetDid;
//        productList[size++] = D2P[targetDid];
//    }
//} SOLUTION;
//
//void sendCenterList(int N, int M, Coordinates centerCoordinatesList[],
//    Product centerProductList[][100], int centerProductSize[]) {
//    centerPos = centerCoordinatesList;
//    for (int cid = 0; cid < CENTER; cid++) {
//        int cpsz = centerProductSize[cid];
//        Product* productList = centerProductList[cid];
//        for (int i = 0; i < cpsz; i++) {
//            mainMatrix[productList[i].id][cid] += productList[i].count;
//        }
//    }
//}
//
//void sendDeliveryList(int K, Coordinates deliveryCoordinatesList[],
//    int deliveryProductList[]) {
//    deliverPos = deliveryCoordinatesList;
//    D2P = deliveryProductList;
//    for (int did = 0; did < DELIVER; did++) {
//        Coordinates dPos = deliveryCoordinatesList[did];
//        int pid = deliveryProductList[did];
//        int targetCid = -1;
//        int minDis = INF;
//        for (int cid = 0; cid < CENTER; cid++) {
//            if (mainMatrix[pid][cid]) {
//                int curDis = centerPos[cid] - dPos;
//                if (curDis < minDis) {
//                    minDis = curDis;
//                    targetCid = cid;
//                }
//            }
//        }
//        mainMatrix[pid][targetCid]--;
//        D2C[did] = targetCid;
//        deliverInfo[targetCid][deliverInfoSize[targetCid]++] = did;
//    }
//}
//
//
//
//void solve(Coordinates truckCoordinates) {
//    Coordinates POS = truckCoordinates;
//    int finished = 0;
//    while (finished < DELIVER) {
//        // 1. center 찾기
//        int targetCid = -1;
//        int minDis = INF;
//        for (int cid = 0; cid < CENTER; cid++) {
//            if (deliverInfoSize[cid]) {
//                int curDis = centerPos[cid] - POS;
//                if (curDis < minDis) {
//                    minDis = curDis;
//                    targetCid = cid;
//                }
//            }
//        }
//
//        SOLUTION.center = targetCid;
//        SOLUTION.size = 0;
//        // 2. 물건 싣기
//        while (SOLUTION.size < LIMIT) {
//            int targetDid = -1;
//            int targetDidIndex = -1;
//            int minDis = INF;
//            for (int i = 0; i < deliverInfoSize[targetCid]; i++) {
//                int did = deliverInfo[targetCid][i];
//                int curDis = POS - deliverPos[did];
//                if (curDis < minDis) {
//                    targetDid = did;
//                    targetDidIndex = i;
//                    minDis = curDis;
//                }
//            }
//
//            POS = deliverPos[targetDid];
//            deliverInfo[targetCid][targetDidIndex] = deliverInfo[targetCid][--deliverInfoSize[targetCid]];
//            SOLUTION.alloc(targetDid);
//
//            if (deliverInfoSize[targetCid] == 0) break;
//        }
//
//        // 3. 배송시작하기
//        truckLoading(SOLUTION.center, SOLUTION.productList, SOLUTION.size);
//        for (int i = 0; i < SOLUTION.size; i++) {
//            truckMove(SOLUTION.deliverList[i]);
//        }
//        finished += SOLUTION.size;
//    }
//}

//10919671040, 7.65s
//using namespace std;
//#define PRODUCT_SIZE 10'000
//#define CENTER_SIZE 1'000
//#define DELIVERY_SIZE 1'000'000
//#define NUM 17
//#define R register
//
//#define ABS(x)	((x) > 0 ? (x) : -(x))
//struct Coordinates
//{
//    int y;
//    int x;
//
//    Coordinates()
//    {
//        y = x = 0;
//    }
//    Coordinates(int _y, int _x)
//    {
//        y = _y;
//        x = _x;
//    }
//
//    int operator-(Coordinates& param)
//    {
//        return ABS(y - param.y) + ABS(x - param.x);
//    }
//};
//
//struct Product
//{
//    int id;
//    int count;
//
//    Product()
//    {
//        id = count = 0;
//    }
//    Product(int _id, int _count)
//    {
//        id = _id;
//        count = _count;
//    }
//};
//
//extern int truckMove(int);
//extern int truckLoading(int, int[], int);
//
//
//struct Center {
//    int proudct[PRODUCT_SIZE] = { 0, };
//    int todo[3000] = { 0, };;
//    int top = 0;
//    Coordinates pos;
//    int pop() {
//
//
//        return todo[--top];
//    }
//};
//
//Center my_center[CENTER_SIZE];
//Coordinates* my_delivery_pos;
//int* my_delivery_product;
//int product_to_center[PRODUCT_SIZE][3000];
//int product_to_center_size[PRODUCT_SIZE];
//void sendCenterList(int N, int M, Coordinates centerCoordinatesList[], Product centerProductList[][100], int centerProductSize[])
//{
//
//    // 초기화
//    for (R int i = 0; i < CENTER_SIZE; i++)
//    {
//        Center& cur = my_center[i];
//        cur.top = 0;
//        for (R int j = 0; j < PRODUCT_SIZE; j++)
//        {
//            cur.proudct[j] = 0;
//
//        }
//
//    }
//
//    for (R int i = 0; i < PRODUCT_SIZE; i++)
//    {
//        product_to_center_size[i] = 0;
//    }
//
//    // 데이터 저장
//
//    for (R int i = 0; i < CENTER_SIZE; i++)
//    {
//        Center& cur = my_center[i];
//        cur.pos = centerCoordinatesList[i];
//
//        for (R int j = 0; j < centerProductSize[i]; j++)
//        {
//            Product& cur_product = centerProductList[i][j];
//            cur.proudct[cur_product.id] += cur_product.count;
//        }
//        for (R int j = 0; j < PRODUCT_SIZE; j++)
//        {
//            if (cur.proudct[j] > 0)
//            {
//                product_to_center[j][product_to_center_size[j]++] = i;
//            }
//
//        }
//
//    }
//
//
//
//}
//
//void sendDeliveryList(int K, Coordinates deliveryCoordinatesList[], int deliveryProductList[])
//{
//    my_delivery_pos = deliveryCoordinatesList;
//    my_delivery_product = deliveryProductList;
//    for (R int i = 0; i < DELIVERY_SIZE; i++)
//    {
//        int min = 10000000;
//        Coordinates deliver_pos = deliveryCoordinatesList[i];
//        int cur_product_id = deliveryProductList[i];
//        int center_id = 0;
//        for (R int j = 0; j < product_to_center_size[cur_product_id]; j++)
//        {
//            Center& cur_center = my_center[product_to_center[cur_product_id][j]];
//            int dist = ABS(deliver_pos - cur_center.pos);
//            //cout<<( cur_center.proudct[cur_product_id] - 1 >= 0 )<< cur_center.proudct[cur_product_id] << " " << dist << endl;
//            if (cur_center.proudct[cur_product_id] - 1 >= 0)
//            {
//
//                if (dist < min)
//                {
//
//                    min = dist;
//                    center_id = product_to_center[cur_product_id][j];
//
//                }
//
//
//            }
//
//        }
//
//        my_center[center_id].todo[my_center[center_id].top++] = i;
//        my_center[center_id].proudct[cur_product_id]--;
//
//    }
//
//}
//
//unsigned long long seed = 5;
//int pseudo_rand(void)
//{
//    seed = seed * 25214903917ULL + 11ULL;
//    return (seed >> 16) & 0x3fffffff;
//}
//void solve(Coordinates truckCoordinates)
//
//{
//    Coordinates truck = truckCoordinates;
//    int done = 0;
//
//
//    //센터별로 NUM 크기만큼 거리 최적화 해놓기
//
//    for (R int i = 0; i < CENTER_SIZE; i++)
//    {
//        Center& cur = my_center[i];
//        Coordinates deliver = cur.pos;
//        for (R int j = cur.top - 1; j >= 0; --j)
//        {
//
//            int min = ABS(deliver - my_delivery_pos[cur.todo[j]]);
//            int target = j;
//
//            for (R int k = j; k >= 0; --k)
//            {
//                int dist = ABS(deliver - my_delivery_pos[cur.todo[k]]);
//                if (dist < min)
//                {
//                    min = dist;
//                    target = k;
//
//                }
//            }
//
//            int temp = cur.todo[j];
//            cur.todo[j] = cur.todo[target];
//            cur.todo[target] = temp;
//            deliver = my_delivery_pos[cur.todo[j]];
//
//        }
//    }
//
//    while (done != DELIVERY_SIZE)
//    {
//        // 가장 가까운 센터 찾기
//        int min = 10000000;
//        int close_center_id = 0;
//        for (R int i = 0; i < CENTER_SIZE; i++)
//        {
//            if (my_center[i].top > 0)
//            {
//                int dist = ABS(my_center[i].pos - truck);
//                if (dist < min)
//                {
//                    min = dist;
//                    close_center_id = i;
//                }
//            }
//
//        }
//
//
//        Center& close = my_center[close_center_id];
//
//        //가서 담고 배달
//        int todo_deliver[NUM];
//        int todo_product[NUM];
//        int todo_size = 0;
//
//        todo_size = 0;
//        if (NUM + todo_size <= close.top)
//        {
//            while (todo_size != NUM)
//            {
//                int deliver_id = close.pop();
//                todo_deliver[todo_size] = deliver_id;
//                todo_product[todo_size++] = my_delivery_product[deliver_id];
//            }
//
//
//        }
//        else {
//
//            while (close.top != 0)
//            {
//                int deliver_id = close.pop();
//                todo_deliver[todo_size] = deliver_id;
//                todo_product[todo_size++] = my_delivery_product[deliver_id];
//            }
//
//        }
//        // 물건 담기
//        truckLoading(close_center_id, todo_product, todo_size);
//
//        // 물건 배달
//        for (R int i = 0; i < todo_size; i++)
//        {
//            truckMove(todo_deliver[i]);
//            //!!!
//            truck = my_delivery_pos[todo_deliver[i]];
//        }
//
//
//        done += todo_size;
//    }
//}


//
//#include <stdio.h>
//#include <malloc.h>
//
//#define ABS(x)	((x) > 0 ? (x) : -(x))
//
//struct Coordinates {
//	int y;
//	int x;
//
//	Coordinates() {
//		y = x = 0;
//	}
//
//	Coordinates(int _y, int _x) {
//		y = _y;
//		x = _x;
//	}
//
//	int operator-(Coordinates& param) {
//		return ABS(y - param.y) + ABS(x - param.x);
//	}
//};
//
//struct Product {
//	int id;
//	int count;
//
//	Product() {
//		id = count = 0;
//	}
//	Product(int _id, int _count) {
//		id = _id;
//		count = _count;
//	}
//};
//
//extern int truckMove(int);
//extern int truckLoading(int, int[], int);
//
//const int MAX_NUM_OF_CENTER = 1'000;
//const int MAX_NUM_OF_DELIVERY = 1'000'000;
//const int MAX_NUM_OF_PRODUCT_FOR_EACH_CENTER = 100;
//
//int numOfCenter;
//int maxNumOfType;
//Coordinates* centers;
//Product* centerProducts[MAX_NUM_OF_PRODUCT_FOR_EACH_CENTER];
//int* centerProductsSize;
//
//int numOfDelivery;
//Coordinates* deliveries;
//int* deliveryProducts;
//
//const int MAP_SIZE = 1000;
//const int EXPECTED_DUPLICATED_DELIVERY_COUNT = 10;
//int centerMap[MAP_SIZE][MAP_SIZE];
//bool emptyCenterChecker[MAX_NUM_OF_CENTER];
//int deliveryMap[MAP_SIZE][MAP_SIZE][EXPECTED_DUPLICATED_DELIVERY_COUNT];
//
//void initSendCenterListParameters(int N, int M, Coordinates centerCoordinatesList[], Product centerProductList[][100], int centerProductSize[]) {
//	numOfCenter = N;
//	maxNumOfType = M;
//	centers = centerCoordinatesList;
//	for (int i = 0; i < MAX_NUM_OF_PRODUCT_FOR_EACH_CENTER; ++i) {
//		centerProducts[i] = centerProductList[i];
//	}
//	centerProductsSize = centerProductSize;
//}
//
//void initCenter() {
//	for (int y = 0; y < MAP_SIZE; ++y) {
//		for (int x = 0; x < MAP_SIZE; ++x) {
//			centerMap[y][x] = -1;
//		}
//	}
//	for (int i = 0; i < numOfCenter; ++i) {
//		emptyCenterChecker[i] = false;
//		Coordinates center = centers[i];
//		centerMap[center.y][center.x] = i;
//	}
//}
//
//void sendCenterList(int N, int M, Coordinates centerCoordinatesList[], Product centerProductList[][100], int centerProductSize[]) {
//	initSendCenterListParameters(N, M, centerCoordinatesList, centerProductList, centerProductSize);
//	initCenter();
//}
//
//void initSendDeliveryListParameters(int K, Coordinates deliveryCoordinatesList[], int deliveryProductList[]) {
//	numOfDelivery = K;
//	deliveries = deliveryCoordinatesList;
//	deliveryProducts = deliveryProductList;
//}
//
//void initDelivery() {
//	for (int y = 0; y < MAP_SIZE; ++y) {
//		for (int x = 0; x < MAP_SIZE; ++x) {
//			for (int s = 0; s < EXPECTED_DUPLICATED_DELIVERY_COUNT; ++s) {
//				deliveryMap[y][x][s] = 0;
//			}
//		}
//	}
//	
//	for (int i = 0; i < numOfDelivery; ++i) {
//		Coordinates delivery = deliveries[i];
//		deliveryMap[delivery.y][delivery.x][++deliveryMap[delivery.y][delivery.x][0]] = i;
//	}
//}
//
//void sendDeliveryList(int K, Coordinates deliveryCoordinatesList[], int deliveryProductList[]) {
//	initSendDeliveryListParameters(K, deliveryCoordinatesList, deliveryProductList);
//	initDelivery();
//}
//
//int getNearestCenter(Coordinates pos) {
//	int centerId = -1;
//	int minDist = 1e9;
//	for (int i = 0; i < numOfCenter; ++i) {
//		if (emptyCenterChecker[i]) {
//			continue;
//		}
//		int dist = ABS(pos - centers[i]);
//		if (dist < minDist) {
//			minDist = dist;
//			centerId = i;
//		}
//	}
//	return centerId;
//}
//
//bool visit[MAP_SIZE][MAP_SIZE] = { false, };
//
//void initVisitForUpdateNearestDeliveryForCenter() {
//	for (int y = 0; y < MAP_SIZE; ++y) {
//		for (int x = 0; x < MAP_SIZE; ++x) {
//			visit[y][x] = false;
//		}
//	}
//}
//
//Product* tmpProducts;
//
//void initTmpProducts(int centerId) {
//	int productsSize = centerProductsSize[centerId];
//	tmpProducts = (Product*)malloc(productsSize * sizeof(Product));
//	for (int i = 0; i < productsSize; ++i) {
//		tmpProducts[i] = { centerProducts[i]->id, centerProducts[i]->count };
//	}
//}
//
//void releaseTmpProducts() {
//	if (tmpProducts == nullptr) {
//		return;
//	}
//	delete tmpProducts;
//	tmpProducts = nullptr;
//}
//
//int findProductIdxFromTmpProducts(int centerId, int productId) {
//	int productsSize = centerProductsSize[centerId];
//	for (int i = 0; i < productsSize; ++i) {
//		if (tmpProducts[i].id == productId && tmpProducts[i].count > 0) {
//			return i;
//		}
//	}
//	return -1;
//}
//
//void removeProductFromTmpProducts(int productIdx) {
//	tmpProducts[productIdx].count--;
//}
//
//struct queue {
//	Coordinates* elements;
//	int size;
//	int head, tail;
//
//	queue() : queue(1000) {}
//
//	queue(int _size) {
//		size = _size;
//		elements = (Coordinates*)malloc(size * sizeof(Coordinates));
//		head = tail = 0;
//	}
//
//	~queue() {
//		delete elements;
//	}
//
//	bool isEmpty() {
//		return head == tail;
//	}
//
//	void push(const Coordinates& e) {
//		elements[tail++] = e;
//		tail %= size;
//	}
//
//	Coordinates front() {
//		return elements[head];
//	}
//
//	void pop() {
//		head++;
//		head %= size;
//	}
//};
//
//int dy[] = { -1, 0, 1, 0 };
//int dx[] = { 0, -1, 0, 1 };
//
//bool canMove(int y, int x) {
//	return 0 <= y && y < MAP_SIZE && 0 <= x && x < MAP_SIZE;
//}
//
//struct CoordIdx {
//	Coordinates coords;
//	int idx;
//
//	CoordIdx() {
//		coords = { -1, -1 };
//		idx = -1;
//	}
//
//	CoordIdx(Coordinates _coords, int _idx) {
//		coords = _coords;
//		idx = _idx;
//	}
//};
//
//const int MAX_NEAREST_DELIVERIES_COUNT = 50;
//int nearestDeliveriesCount;
//CoordIdx nearestDeliveries[MAX_NEAREST_DELIVERIES_COUNT];
//
//void searchNearestDeliveryFromCenter(int centerId) {
//	nearestDeliveriesCount = 0;
//	Coordinates centerCoord = centers[centerId];
//	queue q(MAP_SIZE * MAP_SIZE);
//	q.push({ centerCoord.y, centerCoord.x });
//	visit[centerCoord.y][centerCoord.x] = true;
//
//	while (!q.isEmpty() && nearestDeliveriesCount < MAX_NEAREST_DELIVERIES_COUNT) {
//		Coordinates cur = q.front();
//		q.pop();
//		int cy = cur.y;
//		int cx = cur.x;
//		int coordDeliveryCount = deliveryMap[cy][cx][0];
//		int assinedDeliveryCount = 0;
//
//		for (int idx = 1; idx <= coordDeliveryCount; ++idx) {
//			if (deliveryMap[cy][cx][idx] > 0) { // 필요한지 확인 해야 함
//				int productIdx = findProductIdxFromTmpProducts(centerId, deliveryMap[cy][cx][idx]);
//				if (productIdx > 0) {
//					removeProductFromTmpProducts(productIdx);
//					nearestDeliveries[nearestDeliveriesCount++] = { {cy, cx}, idx };
//				}
//			}
//		}
//		deliveryMap[cy][cx][0] -= assinedDeliveryCount;
//		for (int d = 0; d < 4; ++d) {
//			int ny = cy + dy[d];
//			int nx = cx + dx[d];
//			if (!canMove(ny, nx)) {
//				continue;
//			}
//			else if (visit[ny][nx]) {
//				continue;
//			}
//			q.push({ ny, nx });
//			visit[ny][nx] = true;
//		}
//	}
//}
//
//void printCoordinates(Coordinates coord) {
//	printf("print Coord: %d, %d\n", coord.y, coord.x);
//}
//
//void printCoordIdx(CoordIdx coordIdx) {
//	printf("print CoordIdx, idx: %d, coords: %d, %d\n", deliveryMap[coordIdx.coords.y][coordIdx.coords.x][coordIdx.idx], coordIdx.coords.y, coordIdx.coords.x);
//}
//
//void updateNearestDeliveryForCenter(int centerId) {
//	initVisitForUpdateNearestDeliveryForCenter();
//	initTmpProducts(centerId);
//	searchNearestDeliveryFromCenter(centerId);
//	releaseTmpProducts();
//}
//
//Coordinates currentCoords;
//
//void initSolve(Coordinates truckCoordinates) {
//	currentCoords = truckCoordinates;
//	printCoordinates(truckCoordinates);
//}
//
//void solve(Coordinates truckCoordinates) {
//	initSolve(truckCoordinates);
//
//
//	int nearestCenterId = getNearestCenter(truckCoordinates);
//	printCoordinates(centers[nearestCenterId]);
//	updateNearestDeliveryForCenter(nearestCenterId);
//
//	truckLoading(nearestCenterId);
//	for (int i = 0; i < nearestDeliveriesCount; ++i) {
//		printCoordIdx(nearestDeliveries[i]);
//	}
//
//}
