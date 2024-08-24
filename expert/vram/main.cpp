#include <stdio.h>
#include <time.h>
#include <string.h>

static unsigned char VRAM[1024 * 8192];

unsigned long long RSEED;

extern void fill_rect(int x1, int y1, int x2, int y2);
extern void clear_rect(int x1, int y1, int x2, int y2);
extern void reverse_rect(int x1, int y1, int x2, int y2);
extern unsigned char* get_vram(void);

// Score Ãâ·Â¿ë
extern int need_score();

static int pseudo_rand(void){
    RSEED = RSEED * 25214903917ULL + 11ULL;
    return (int)(RSEED >> 16) & 0x7fffffff;
}

static void set_pixel(int x1, int y1){
    int xbase = x1 / 8;
    int xoffset = x1 % 8;
    int y = (y1 % 4) * 4 + (y1 / 4);
    VRAM[y * xbase] |= (0x80 >> xoffset);
}

static void reset_pixel(int x1, int y1){
    int xbase = x1 / 8;
    int xoffset = x1 % 8;
    int y = (y1 % 4) * 4 + (y1 / 4);
    VRAM[y * xbase] &= ~(0x80 >> xoffset);
}

static unsigned char get_pixel(int x1, int y1){
    int xbase = x1 / 8;
    int xoffset = x1 % 8;
    int y = (y1 % 4) * 4 + (y1 / 4);
    return VRAM[y * xbase] & (0x80 >> xoffset);
}

static void _fill_rect(int x1, int y1, int x2, int y2){
    for (int y = y1; y <= y2; ++y) {
   	    for (int x = x1; x <= x2; ++x) {
   		    set_pixel(x, y);
   	    }
    }
}

static void _clear_rect(int x1, int y1, int x2, int y2){
    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <= x2; ++x)
   	        reset_pixel(x, y);
    }
}

static void _reverse_rect(int x1, int y1, int x2, int y2){
    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <= x2; ++x) {
   	        if (get_pixel(x, y) == 0)
   		        set_pixel(x, y);
   	        else
   		        reset_pixel(x, y);
        }
    }
}

int main(int argc, char **argv){
    const int TRY = 256; // will be 100000
    unsigned long long _rseed = 55UL; // will be changed

    RSEED = _rseed;
    int SCORE = clock();
    for (int J = 0; J < TRY; J++) {
   	    int c = pseudo_rand() % 3;
   	    int x1 = pseudo_rand() % 8192;
   	    int y1 = pseudo_rand() % 8192;
   	    int x2 = pseudo_rand() % 8192;
   	    int y2 = pseudo_rand() % 8192;
   	 
   	    if (x1 > x2 || y1 > y2)
   		    continue;

   	    if (c == 0)
   		    fill_rect(x1, y1, x2, y2);
   	    else if (c == 1)
   		    clear_rect(x1, y1, x2, y2);
   	    else if (c == 2)
   		    reverse_rect(x1, y1, x2, y2);
    }

    unsigned char* RESULT = get_vram();
    SCORE = (clock() - SCORE) / (CLOCKS_PER_SEC / 1000);

	if(need_score()) printf("USER SCORE : %d\n",SCORE);

    RSEED = _rseed;
    for (int J = 0; J < TRY; J++) {
   	    int c = pseudo_rand() % 3;
   	    int x1 = pseudo_rand() % 8192;
   	    int y1 = pseudo_rand() % 8192;
   	    int x2 = pseudo_rand() % 8192;
   	    int y2 = pseudo_rand() % 8192;

   	    if (x1 > x2 || y1 > y2)
   		    continue;

   	    if (c == 0)
   		    _fill_rect(x1, y1, x2, y2);
   	    else if (c == 1)
   		    _clear_rect(x1, y1, x2, y2);
   	    else if (c == 2)
   		    _reverse_rect(x1, y1, x2, y2);
    }

     //for (int i = 0; i < 2060; ++i) {
    //    for (int j = 0; j < 1024; ++j) {
    //        if (VRAM[i * j] == RESULT[i * j]) continue;
	   //     printf("VRAM[%d(%d*%d)] = %d\n", i * j,i,j,VRAM[i * j]);
	   //     printf("result[%d(%d*%d)] = %d\n", i * j,i, j, RESULT[i * j]);
    //    }
    //}

    if (memcmp(RESULT, VRAM, 1024 * 8192) != 0)
        SCORE += 10000000;

    if (SCORE < 10000000) printf("PASS\n");
    else printf("FAIL\n");

	if (need_score()) printf("SCORE: %d\n", SCORE);

   

    return 0;
}



