#include <stdio.h>
void func(int n, int from, int to) {
	if (n == 1)
		printf("%d %d\n", from, to);		//������ �Ѱ��̸� �ٷ� ����.
	else {
		int mid = 6 - from - to;			//6-from-to�� from to�� 1,2->3, 1,3->2, 2, 3->1�̹Ƿ�
		func(n - 1, from, mid);				//�̰��� ���ؼ� �߰��� ���İ��� ���� ���� �� �ִ�.
		printf("%d %d\n", from, to);		//from -> mid, mid -> to�� ���·� ���� ��Ų��.		
		func(n - 1, mid, to);
	}
}
int main() {
	int n;
	scanf("%d", &n);
	printf("%d\n", (1<<n)-1);				//�ϳ��� ž �̵� Ƚ���� 2^n -1ȸ�̴�.
	func(n, 1, 3);
	return 0;
}