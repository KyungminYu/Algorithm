
#define rint register int
#define MAX_BIT 8

unsigned char VRAM[1024 * 8192] = { 0 };

unsigned char bitmap[MAX_BIT][MAX_BIT];

int yPos[8192];
int xBase[8192];
int xOffset[8192];

bool visit[2060];

bool isInitialized = false;
void init() {
	if (isInitialized) {
		return;
	}
	isInitialized = true;
	for (rint i = 0; i < MAX_BIT; ++i) {
		bitmap[i][i] = (1 << (MAX_BIT - 1 - i));
		for (rint j = i + 1; j < MAX_BIT; ++j) {
			bitmap[i][j] = bitmap[i][j - 1] | (1 << (MAX_BIT - 1 - j));
		}
	}
	for (rint i = 0; i < 8192; ++i) {
		xBase[i] = i / MAX_BIT;
		xOffset[i] = i % MAX_BIT;
		yPos[i] = (i % 4) * 4 + (i / 4);
	}
}

void initVisit(int y1, int y2, bool value) {
	for (rint i = y1; i <= y2; ++i) {
		visit[yPos[i]] = value;
	}
}

void initVisitForReverse(int y1, int y2) {
	initVisit(y1, y2, true);
	for (rint i = y1; i <= y2; ++i) {
		visit[yPos[i]] = !visit[yPos[i]];
	}
}

void fill_rect(int x1, int y1, int x2, int y2) {
	init();
	initVisit(y1, y2, false);
	rint xbase1 = xBase[x1];
	rint xbase2 = xBase[x2];
	rint xOffset1 = xOffset[x1];
	rint xOffset2 = xOffset[x2];
	
	for (rint i = y1; i <= y2; ++i) {
		rint y = yPos[i];
		if (visit[y]) {
			continue;
		}
		visit[y] = true;

		if (xbase1 == xbase2) {
			VRAM[xbase1 * y] |= bitmap[xOffset1][xOffset2];
		}
		else {
			VRAM[xbase1 * y] |= bitmap[xOffset1][MAX_BIT - 1];
			for (rint xbase = xbase1 + 1; xbase < xbase2; ++xbase) {
				VRAM[xbase * y] = 0xFF;
			}
			VRAM[xbase2 * y] |= bitmap[0][xOffset2];
		}
	}
}

void clear_rect(int x1, int y1, int x2, int y2) {
	init();
	initVisit(y1, y2, false);
	rint xbase1 = xBase[x1];
	rint xbase2 = xBase[x2];
	rint xOffset1 = xOffset[x1];
	rint xOffset2 = xOffset[x2];

	for (rint i = y1; i <= y2; ++i) {
		rint y = yPos[i];
		if (visit[y]) {
			continue;
		}
		visit[y] = true;

		if (xbase1 == xbase2) {
			VRAM[xbase1 * y] &= ~bitmap[xOffset1][xOffset2];
		}
		else {
			VRAM[xbase1 * y] &= ~bitmap[xOffset1][MAX_BIT - 1];
			for (rint xbase = xbase1 + 1; xbase < xbase2; ++xbase) {
				VRAM[xbase * y] = 0;
			}
			VRAM[xbase2 * y] &= ~bitmap[0][xOffset2];
		}
	}
}

void reverse_rect(int x1, int y1, int x2, int y2) {
	init();
	initVisitForReverse(y1, y2);
	rint xbase1 = xBase[x1];
	rint xbase2 = xBase[x2];
	rint xOffset1 = xOffset[x1];
	rint xOffset2 = xOffset[x2];

	for (rint i = y1; i <= y2; ++i) {
		rint y = yPos[i];
		if (visit[y]) {
			continue;
		}
		visit[y] = true;

		if (xbase1 == xbase2) {
			VRAM[xbase1 * y] ^= bitmap[xOffset1][xOffset2];
		}
		else {
			VRAM[xbase1 * y] ^= bitmap[xOffset1][MAX_BIT - 1];
			for (rint xbase = xbase1 + 1; xbase < xbase2; ++xbase) {
				VRAM[xbase * y] = ~VRAM[xbase * y];
			}
			VRAM[xbase2 * y] ^= bitmap[0][xOffset2];
		}
	}
}

unsigned char* get_vram() {
	return VRAM;
}
