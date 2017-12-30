#include <stdio.h>
#include <algorithm>
#include <stack>
using namespace std;

#define ll long long
const int NMAX = 100005;
struct point{
	ll x, y, _x, _y;
	point(){_x = 0; _y = 0;_x = 1; _y = 0; }
	void read(){
		ll x, y; scanf("%lld %lld", &x, &y);
		this->x = x; this->y = y;
	}
	void _set(ll x0, ll y0){
		_x = x - x0;
		_y = y - y0;
	}
	bool operator< (point p) const{
		if(_y * p._x != _x * p._y) 
			return _y * p._x < _x * p._y;
		if(y != p.y) return y < p.y;
		return x < p.x;
	}
};

ll ccw(const point& p1, const point& p2, const point& p3){
	return (p2.x - p1.x) * (p3.y - p1.y) 
	- (p2.y - p1.y) * (p3.x - p1.x);
}

point p[NMAX];
int main(){
	int n; scanf("%d", &n);

	for(int i = 0; i < n; i++)
		p[i].read();
	sort(p, p + n);

	for(int i = 1; i <= n; i++)
		p[i]._set(p[0].x, p[0].y);
	sort(p + 1, p + n);

	stack<int> s;
	s.push(0);
	s.push(1);

	int nxt = 2;
	while(nxt < n){
		while(s.size() >= 2){
			int p1 = s.top();
			s.pop();
			int p2 = s.top();
			if(ccw(p[p2], p[p1], p[nxt]) > 0){
				s.push(p1);
				break;
			}
		}
		s.push(nxt++);
	}
	printf("%d\n", s.size());
	return 0;
}