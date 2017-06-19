#include <stdio.h>
void func(int n, int from, int to) {
	if (n == 1)
		printf("%d %d\n", from, to);		//원판이 한개이면 바로 간다.
	else {
		int mid = 6 - from - to;			//6-from-to는 from to가 1,2->3, 1,3->2, 2, 3->1이므로
		func(n - 1, from, mid);				//이것을 통해서 중간에 거쳐가는 것을 만들 수 있다.
		printf("%d %d\n", from, to);		//from -> mid, mid -> to의 형태로 진행 시킨다.		
		func(n - 1, mid, to);
	}
}
int main() {
	int n;
	scanf("%d", &n);
	printf("%d\n", (1<<n)-1);				//하노이 탑 이동 횟수는 2^n -1회이다.
	func(n, 1, 3);
	return 0;
}