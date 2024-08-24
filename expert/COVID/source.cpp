extern char flu_checkup(int n);
extern void culture(int n, int a, int b);
extern void clear(int n);

#define MAX_SAMPLE 50000000
#define BULK_SIZE 512

int pivot;

inline bool isFluExistInRange(int s, int e) {
    for (register int i = s; i <= e; ++i)
        culture(pivot, pivot, i);
    return flu_checkup(pivot++);
}

void flu_clear(int s, int e) {
    if (e <= s) {
        clear(s);
        return;
    }
    int m = (s + e) / 2;
    if (isFluExistInRange(s, m))
        flu_clear(s, m);
    else 
        flu_clear(m + 1, e);
}

void test() {
    pivot = MAX_SAMPLE;
    int s = 0, e;
    while (s < MAX_SAMPLE) {
        e = s + BULK_SIZE;
        if (MAX_SAMPLE <= e) 
            e = MAX_SAMPLE - 1;
        if (isFluExistInRange(s, e)) 
            flu_clear(s, e);
        else 
            s = e + 1;
    }
}