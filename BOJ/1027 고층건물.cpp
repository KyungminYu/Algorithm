#include <stdio.h>
#define lld long long
#define INF 2e9
lld n, h[52];

struct tilt {
	lld x, y;
	tilt(){}
	tilt(lld x, lld y):x(x), y(y){}
	bool operator < (tilt v) const {
		return  v.x * y < v.y * x;
	}
	tilt& operator = (const tilt& c) {
		x = c.x;
		y = c.y;
		return *this;
	}
};

int main(){
	scanf("%lld", &n);
	for (lld i = 1; i <= n; ++i) scanf("%lld", &h[i]);
	lld res = 0;
	tilt mx, mi, tmp;	
	for (lld i = 1; i <= n; ++i) {
		lld cnt = 0;
		mi = tilt(-1, -INF);
		for (lld j = i - 1; 1 <= j; --j) {
			tmp = tilt(j - i, h[j] - h[i]);
			if (tmp < mi) {
				mi = tmp;
				cnt++;
			}
		}

		mx = tilt(1, -INF);
		for (lld j = i + 1; j <= n; ++j) {
			tmp = tilt(j - i, h[j] - h[i]);
			if (mx < tmp) {
				mx = tmp;
				cnt++;
			}
		}
		res = res > cnt ? res : cnt;
	}
	printf("%lld\n", res);
	return 0;
}
