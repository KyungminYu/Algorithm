#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
struct Student{
	int idx, able;
	long long cost;
};
struct Bug{
	int idx, amount, solve;
};
queue<int> ans;
Student S[100005];
Bug B[100005];
int n, m;
long long s;

int sCmp(Student s1, Student s2){ return s1.able > s2.able;}
int bCmp(Bug b1, Bug b2){ return b1.amount > b2.amount;}
int bIdxCmp(Bug b1, Bug b2){ return b1.idx < b2.idx;}

int isable(int day){
	priority_queue<pair<long long, int> > pq;
	queue<int> q;
	int cur = 0;
	long long price = 0;
	for(int i = 0; i < m; i+= day){
		while(n > cur && S[cur].able >= B[i].amount){
			pq.push(make_pair(-S[cur].cost, S[cur].idx));
			cur++;
		}
		if(pq.empty()) return 0;
		price += (-pq.top().first);
		q.push(pq.top().second);
		pq.pop();
	}
	if(q.empty() || price > s) return 0;
	ans = q;
	return 1;
}

int main(){
	//freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &n, &m, &s);
	for(int i = 0; i < m; i++) {
		scanf("%d", &B[i].amount);
		B[i].idx = i + 1;
	}
	for(int i = 0; i < n; i++) {
		scanf("%d", &S[i].able);
		S[i].idx = i + 1;
	}
	for(int i = 0; i < n; i++) scanf("%lld", &S[i].cost);
	sort(S, S + n, sCmp);
	sort(B, B + m, bCmp);

	int low = 1, high = m, mid, day = m; 
	while(low <= high){
		mid = (low + high) / 2;
		if(isable(mid)) {
			high = mid - 1;
			day = mid;
		}
		else low = mid + 1;
	}
	if(ans.empty())	printf("NO\n");
	else{
		for(int i = 0; i < m;){
			int solve = ans.front();
			ans.pop();
			for(int j = 0; j < day && i < m; j++, i++){
				B[i].solve = solve;
			}
		}
		sort(B, B + m, bIdxCmp);
		printf("YES\n");
		for(int i = 0; i < m ;i++) printf("%d ", B[i].solve);
	}
	return 0;
}