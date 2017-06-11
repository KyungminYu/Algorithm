#include <stdio.h>
#include <vector>
using namespace std;

long long dr[] = { 0, 1, 0, -1 };
long long dc[] = { 1, 0, -1, 0 };
long long L, N, t, dir, flag;
long long r, c, pr, pc, diff, cnt;
char d;
vector<pair<pair<long long, long long>, pair<long long, long long> > > lines;

long long isIntersect(long long dir, long long dir2, pair<long long, long long> v1, pair<long long, long long> v2, pair<long long, long long> v3, pair<long long, long long> v4){
	if(dir2 % 2 == 0){
		if(v3.first < v4.first) dir2 = 0;
		else dir2 = 2;
	}
	else{
		if(v3.second < v4.second) dir2 = 1;
		else dir2 = 3;
	}
	if(dir == 0){
		if(dir2 == 0 && v1.second == v3.second && v1.first <= v3.first && v3.first <= v2.first) return v3.first - v1.first;
		else if(dir2 == 1 && v1.first <= v3.first && v3.first <= v2.first && v3.second <= v2.second && v2.second <= v4.second) return v3.first - v1.first;
		else if(dir2 == 2 && v1.second == v3.second && v1.first <= v4.first && v4.first <= v2.first) return v4.first - v1.first;
		else if(dir2 == 3 && v1.first <= v3.first && v3.first <= v2.first && v4.second <= v2.second && v2.second <= v3.second) return v3.first - v1.first;
	}
	else if(dir == 1){
		if(dir2 == 0 && v1.second <= v3.second && v3.second <= v2.second && v3.first <= v2.first && v2.first <= v4.first) return v3.second - v1.second;
		else if(dir2 == 1 && v1.first == v3.first && v1.second <= v3.second && v3.second <= v2.second)return v3.second - v1.second;
		else if(dir2 == 2 && v1.second <= v3.second && v3.second <= v2.second && v4.first <= v2.first && v2.first <= v3.first) return v3.second - v1.second;
		else if(dir2 == 3 && v1.first == v3.first && v1.second <= v4.second && v4.second <= v2.second)return v4.second - v1.second;
	}
	else if(dir == 2){
		if(dir2 == 0 && v1.second == v3.second && v2.first <= v4.first && v4.first <= v1.first)return v1.first - v4.first;
		else if(dir2 == 1 && v2.first <= v3.first && v3.first <= v1.first && v3.second <= v2.second && v2.second <= v4.second) return v1.first - v3.first;
		else if(dir2 == 2 && v1.second == v3.second && v2.first <= v3.first && v3.first <= v1.first)return v1.first - v3.first;
		else if(dir2 == 3 && v2.first <= v3.first && v3.first <= v1.first && v4.second <= v2.second && v2.second <= v3.second) return v1.first - v3.first;
	}
	else{
		if(dir2 == 0 && v2.second <= v3.second && v3.second <= v1.second && v3.first <= v2.first && v2.first <= v4.first) return v1.second - v3.second;
		else if(dir2 == 1 && v1.first == v3.first && v2.second <= v4.second && v4.second <= v1.second) return v1.second - v4.second;
		else if(dir2 == 2 && v2.second <= v3.second && v3.second <= v1.second && v4.first <= v2.first && v2.first <= v3.first) return v1.second - v3.second;
		else if(dir2 == 3 && v1.first == v3.first && v2.second <= v3.second && v3.second <= v1.second) return v1.second - v3.second;
	}
	return -1;
}
long long isCrossed(long long dir, pair<long long, long long> v1, pair<long long, long long> v2){
	long long len = lines.size();
	long long diff = -1, dist, mindist = 1e9;
	pair<long long, long long> v3;
	pair<long long, long long> v4;
	for(long long i = 0; i < len - 1; i++){
		v3 = lines[i].first;
		v4 = lines[i].second;
		if((dist = isIntersect(dir, i, v1, v2, v3, v4)) != -1){
			if(dist < mindist){
				mindist = dist;
				if(dir == 0){ //right	
					diff = v2.first - v3.first;
				}else if(dir == 1){ //up
					diff = v2.second - v3.second;
				}else if(dir == 2){ // left
					diff = v3.first - v2.first;
				}else{ //down
					diff = v3.second - v2.second;
				}
			}
		}
	}
	return diff;
}

long long onBoundary(long long dir, pair<long long, long long> v){
	if(dir == 0 && (L + 1 <= v.first)) return v.first - (L + 1);
	else if(dir == 1 && (L + 1 <= v.second)) return v.second - (L + 1);
	else if(dir == 2 && (v.first <= -L - 1)) return (-L - 1) - v.first;
	else if(dir == 3 && (v.second <= -L - 1)) return (-L - 1) - v.second;
	return -1;
}
int main(){
	scanf("%lld %lld", &L, &N);
	r = c = pr = pc = 0;
	for(long long i = 0; i< N; i++){
		scanf("%lld %c", &t, &d);
		r += (dr[dir]) * t;
		c += (dc[dir]) * t; 
		cnt += t;
		if((diff = isCrossed(dir, make_pair(pc, pr), make_pair(c, r))) != -1){
			cnt -= diff;
			flag = 1;
			break;
		}    
		if((diff = onBoundary(dir, make_pair(c, r))) != -1){
			cnt -= diff;
			flag = 2;
			break;
		}
		lines.push_back(make_pair(make_pair(pc, pr), make_pair(c, r)));
		pr = r;
		pc = c;
		if(d == 'R') dir = (dir + 3) % 4;
		else dir = (dir + 1) % 4;
	}
	if(!flag){
		r += (dr[dir]) * 2e8;
		c += (dc[dir]) * 2e8;
		cnt += 2e8;
		if((diff = isCrossed(dir, make_pair(pc, pr), make_pair(c, r))) != -1)
			cnt -= diff;

		else if((diff = onBoundary(dir, make_pair(c, r))) != -1)
			cnt -= diff;
	}
	printf("%lld\n", cnt);
	return 0;
}