#include <stdio.h>
#define PI 3.14159265358979323846
int main(){
    double R; scanf("%lf", &R);
    printf("%.6lf\n",  PI * R * R);
    printf("%.6lf\n",  2.0 * R * R);
    return 0;
}