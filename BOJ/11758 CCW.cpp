#include <stdio.h>
//https://www.acmicpc.net/blog/view/27
struct point{
    int x, y;
    void read(){scanf("%d %d", &x, &y);}
}P[3];
int ccw(point &p1, point &p2, point &p3) {
    int val = (p2.x - p1.x) * (p3.y - p1.y)
     - (p2.y - p1.y) * (p3.x - p1.x);
    if(val > 0) return 1;
    else if(val < 0) return -1;
    else return 0; 
}
int main(){
    for(int i = 0; i < 3; i++) P[i].read();
    printf("%d\n", ccw(P[0], P[1], P[2]));
    return 0;
}