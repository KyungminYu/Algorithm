#include <stdio.h>

#define ABS(x) ((x)) < 0 ? (-(x)) : (x)

#define MAP_SIZE 5001
#define TOWER_CATEGORY 5
#define MAX_TOWER_PER_CATEGORY 110000

struct Position {
	int r;
	int c;
};

int mapSize;
int colorMap[MAP_SIZE][MAP_SIZE];
int indexMap[MAP_SIZE][MAP_SIZE];

int towersCount[TOWER_CATEGORY + 1];
Position towers[TOWER_CATEGORY + 1][MAX_TOWER_PER_CATEGORY];

void init(int N) {
	mapSize = N;
	for (register int r = 0; r < MAP_SIZE; ++r) {
		for (register int c = 0; c < MAP_SIZE; ++c) {
			colorMap[r][c] = 0;
			indexMap[r][c] = -1;
		}
	}
	for (register int category = 0; category <= TOWER_CATEGORY; ++category) {
		towersCount[category] = 0;
	}
}

void buildTower(int mRow, int mCol, int mColor) {
	//printf("buildTower, row: %d, col: %d, color: %d\n", mRow, mCol, mColor);
	colorMap[mRow][mCol] = mColor;
	indexMap[mRow][mCol] = towersCount[mColor];
	towers[mColor][indexMap[mRow][mCol]] = {mRow, mCol};
	++towersCount[mColor];
}

void removeTower(int mRow, int mCol) {
	int color = colorMap[mRow][mCol];
	int index = indexMap[mRow][mCol];
	if (index < 0) {
		return;
	}
	int removeRow = towers[color][index].r;
	int removeCol = towers[color][index].c;
	//printf("removeTower, row: %d, col: %d, color: %d, index: %d, removeRow: %d, removeCol: %d\n", mRow, mCol, color, index, removeRow, removeCol);

	colorMap[removeRow][removeCol] = 0;
	indexMap[removeRow][removeCol] = -1;

	towers[color][index] = towers[color][--towersCount[color]];

}

int countTower(int mRow, int mCol, int mColor, int mDis) {
	int rStart = (mRow - mDis) < 1 ? 1 : (mRow - mDis);
	int cStart = (mCol - mDis) < 1 ? 1 : (mCol - mDis);
	int rEnd = (mRow + mDis) > mapSize ? mapSize : (mRow + mDis);
	int cEnd = (mCol + mDis) > mapSize ? mapSize : (mCol + mDis);
	int count = 0;
	for (register int r = rStart; r <= rEnd; ++r) {
		for (register int c = cStart; c <= cEnd; ++c) {
			if (indexMap[r][c] >= 0) {
				if (mColor == 0 || colorMap[r][c] == mColor) {
					++count;
				}
			}
		}
	}
	//printf("countTower, row: %d, col: %d, color: %d, ditance: %d, count: %d\n", mRow, mCol, mColor, mDis, count);
	return count;
}

int getClosest(int mRow, int mCol, int mColor) {
	int minDist = 1e9;
	if (mColor != 0) {
		bool towerChecked = false;
		for (register int posIdx = 0; posIdx < towersCount[mColor]; ++posIdx) {
			towerChecked = true;
			int rDist = ABS(mRow - towers[mColor][posIdx].r);
			int cDist = ABS(mCol - towers[mColor][posIdx].c);
			//printf("r from %d to %d: %d\n", mRow, towers[mColor][posIdx].r, rDist);
			//printf("c from %d to %d: %d\n", mCol, towers[mColor][posIdx].c, cDist);
			int dist = rDist + cDist;
			//printf("from %d, %d to %d, %d: %d\n", mRow, mCol, towers[mColor][posIdx].r, towers[mColor][posIdx].c, dist);
			if (dist < minDist) {
				minDist = dist;
			}
		}
		if (!towerChecked) {
			minDist = -1;
		}
	}
	else {
		bool towerChecked = false;
		for (register int color = 1; color <= TOWER_CATEGORY; ++color) {
			for (register int posIdx = 0; posIdx < towersCount[color]; ++posIdx) {
				towerChecked = true;
				int rDist = ABS(mRow - towers[color][posIdx].r);
				int cDist = ABS(mCol - towers[color][posIdx].c);
				int dist = rDist + cDist;
				//printf("color0, from %d, %d to %d, %d: %d\n", mRow, mCol, towers[color][posIdx].r, towers[color][posIdx].c, dist);
				if (dist < minDist) {
					minDist = dist;
				}
			}
		}
		if (!towerChecked) {
			minDist = -1;
		}
	}
	//printf("getClosest, row: %d, col: %d, color: %d, colosest: %d\n", mRow, mCol, mColor, minDist);
	return minDist;
}