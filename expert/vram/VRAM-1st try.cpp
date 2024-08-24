#include <iostream>
using namespace std;

static unsigned char RAM[1024 * 8192] = { 0 };

bool isBitmapInitialized = false;
unsigned char bitLookup[8][8];

void init() {

	if (isBitmapInitialized) {
		return;
	}
	isBitmapInitialized = true;
	for (register int i = 0; i < 8; ++i) {
		bitLookup[i][i] = (1 << (7 - i));
		for (register int j = i + 1; j < 8; ++j) {
			bitLookup[i][j] = bitLookup[i][j - 1] | (1 << (7 - j));
		}
	}
}

unsigned char getBitValue(int from, int to) {
	return bitLookup[from][to];
}

bool fillLookupChecked[256][8][8];
unsigned char fillLookup[256][8][8];
unsigned char getFillValue(unsigned char src, int from, int to) {
	if (!fillLookupChecked[src][from][to]) {
		fillLookup[src][from][to] = src | getBitValue(from, to);
		fillLookupChecked[src][from][to] = true;
	}
	return fillLookup[src][from][to];
}

bool clearLookupChecked[256][8][8];
unsigned char clearLookup[256][8][8];
unsigned char getClearValue(unsigned char src, int from, int to) {
	if (!clearLookupChecked[src][from][to]) {
		clearLookup[src][from][to] = src & ~getBitValue(from, to);
		clearLookupChecked[src][from][to] = true;
	}
	return clearLookup[src][from][to];
}

bool reverseLookupChecked[256][8][8];
unsigned char reverseLookup[256][8][8];
unsigned char getReverseValue(unsigned char src, int from, int to) {
	if (!reverseLookupChecked[src][from][to]) {
		reverseLookup[src][from][to] = src ^ getBitValue(from, to);
		reverseLookupChecked[src][from][to] = true;
	}
	return reverseLookup[src][from][to];
}

bool yLookupChecked[8192];
int yLookup[8192];
int getYLookup(int y) {
	if (!yLookupChecked[y]) {
		yLookup[y] = (y % 4) * 4 + (y / 4);
		yLookupChecked[y] = true;
	}
	return yLookup[y];
}

bool xBaseLookupChecked[8192];
int xBaseLookup[8192];
int getXBaseLookup(int x) {
	if (!xBaseLookupChecked[x]) {
		xBaseLookup[x] = x / 8;
		xBaseLookupChecked[x] = true;
	}
	return xBaseLookup[x];
}

bool xOffsetLookupChecked[8192];
int xOffsetLookup[8192] = { -1 };
int getXOffsetLookup(int x) {
	if (!xOffsetLookupChecked[x]) {
		xOffsetLookup[x] = x % 8;
		xOffsetLookupChecked[x] = true;
	}
	return xOffsetLookup[x];
}

void fullFill(int y, int xBase) {
	register int index = y * xBase;
	RAM[index] = 0xFF;
}

void partialFill(int y, int xBase, int sBit, int eBit) {
	register int index = y * xBase;
	RAM[index] = getFillValue(RAM[index], sBit, eBit);
}

void fill_rect(int x1, int y1, int x2, int y2) {
	init();
	int xbase1 = getXBaseLookup(x1);
	int xbase2 = getXBaseLookup(x2);

	for (register int i = y1; i <= y2; ++i) {
		register int y = getYLookup(i);
		register int xOffset1 = getXOffsetLookup(x1);
		register int xOffset2 = getXOffsetLookup(x2);
		if (xbase1 == xbase2) {
			partialFill(y, xbase1, xOffset1, xOffset2);
		}
		else {
			partialFill(y, xbase1, xOffset1, 7);
			for (int xbase = xbase1 + 1; xbase < xbase2; ++xbase) {
				fullFill(y, xbase);
			}
			partialFill(y, xbase2, 0, xOffset2);
		}
	}
}

void fullClear(int y, int xBase) {
	register int index = y * xBase;
	RAM[index] = 0x00;
}

void partialClear(int y, int xBase, int sBit, int eBit) {
	register int index = y * xBase;
	RAM[index] = getClearValue(RAM[index], sBit, eBit);
}

void clear_rect(int x1, int y1, int x2, int y2) {
	init();

	register int xbase1 = getXBaseLookup(x1);
	register int xbase2 = getXBaseLookup(x2);

	for (register int i = y1; i <= y2; ++i) {
		register int y = getYLookup(i);
		register int xOffset1 = getXOffsetLookup(x1);
		register int xOffset2 = getXOffsetLookup(x2);

		if (xbase1 == xbase2) {
			partialClear(y, xbase1, xOffset1, xOffset2);
		}
		else {
			partialClear(y, xbase1, xOffset1, 7);
			for (int xbase = xbase1 + 1; xbase < xbase2; ++xbase) {
				fullClear(y, xbase);
			}
			partialClear(y, xbase2, 0, xOffset2);
		}
	}
}

void fullReverse(int y, int xBase) {
	register int index = y * xBase;
	RAM[index] = ~RAM[index];
}

void partialReverse(int y, int xBase, int sBit, int eBit) {
	register int index = y * xBase;
	RAM[index] = getReverseValue(RAM[index], sBit, eBit);
}

void reverse_rect(int x1, int y1, int x2, int y2) {
	init();

	register int xbase1 = getXBaseLookup(x1);
	register int xbase2 = getXBaseLookup(x2);

	for (register int i = y1; i <= y2; ++i) {
		register int y = getYLookup(i);
		register int xOffset1 = getXOffsetLookup(x1);
		register int xOffset2 = getXOffsetLookup(x2);

		if (xbase1 == xbase2) {
			partialReverse(y, xbase1, xOffset1, xOffset2);
		}
		else {
			partialReverse(y, xbase1, xOffset1, 7);
			for (int xbase = xbase1 + 1; xbase < xbase2; ++xbase) {
				fullReverse(y, xbase);
			}
			partialReverse(y, xbase2, 0, xOffset2);
		}
	}
}

unsigned char* get_vram() {
	return RAM;
}

int need_score() {
	return true;
}