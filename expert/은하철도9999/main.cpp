#include <stdio.h>
#include <time.h>
#include <string.h>
#define PASS (5000)

// solution - start

#include <malloc.h>

#define PASSENGER_NAME_SIZE 512
char* train[100005];
int size;
// debug 22 sec

class TRAIN {
	char *passenger;
	T *prev, next;

	TRAIN() {
		passenger = new char[PASSENGER_NAME_SIZE];
		prev = next = nullptr;
	}

	~TRAIN
};



void strcpys(char* dst, char* src) {
	while (*src) {
		*dst = *src;
		dst++;
		src++;
	}
	*dst = 0;
}

void append_train(char* passenger_name) {
	// 열차끝에 새 열차 칸을 추가한다.
	train[size] = (char*)malloc(sizeof(char) * 512);
	strcpys(train[size], passenger_name);
	size++;
}

void insert_train(int lineToInsert, char* passenger_name) {
	// 특정 위치에 열차 칸을 삽입한다.
	for (register int i = size - 1; i >= lineToInsert; i--) {
		train[i + 1] = train[i];
	}
	train[lineToInsert] = (char*)malloc(sizeof(char) * 512);
	strcpys(train[lineToInsert], passenger_name);
	size++;
}

void erase_train(int lineToErase) {
	// 특정 위치의 열차 칸을 삭제 한다.
	free(train[lineToErase]);
	for (register int i = lineToErase; i < size - 1; i++) {
		train[i] = train[i + 1];
	}
	size--;
}

char* getTrainPassengerName(int line) {
	// 특정 위치의 열차 탑승 승객 이름을 return한다
	return train[line];
}

void swapPassenger(int lineSwapA, int lineSwapB) {
	// 특정한 2위치의 열차칸의 탑승자를 교환한다.
	char* tmp = train[lineSwapA];
	train[lineSwapA] = train[lineSwapB];
	train[lineSwapB] = tmp;
}

void changePassengerName(int lineToChange, char* passenger_name) {
	// 특정한 열차 칸에 타고 있는 탑승자의 이름을 바꾼다
	strcpys(train[lineToChange], passenger_name);
}

// end - end



const char* ANS = "NANWILSDNUDWQUBSRWWEWFZGGNEOFLISRYKWVVJWZWTSZUWOXDJWJCXNOVGUDCXLNXOLSEVESQGDUSFGQWFWGSFQDYYUVCBRZVBIFSPIRUYLBQVADHUYUINDOGSFALCIEMBKVVPXUDVKGLDRDUTWATTGJIOVJHAYLAMNUEYXICEDAOHZQQGVJISRRDBIWJCVWBMJTZRQUUSURGBNRKWNACBJDCSLYGVTCXGCVJFZTHLBWYEVUQWWRDNDVSXGYBIKABYRMXIOKFIIILCJDRBERFNGSPVBXQZPQBUEWBBRRCXIAPUSYHBOMHLSCOCAAESCDEMGZPSJQVNQEBVBCVHEVKIQRCYMRPYTHBCUAWQGMIVEMVEWCHDTTPRKGDEPAMCFYNGJIDJWMFOHRWWJGTJFJWCODQMZZKSWUHUCKQTFHMJMPZYOZKQMAXIXKSPRAAMHGACUMZWCOIZOQFQFVMZSTNJTSWDBAHHJUMGIIWOOVQZDZMBEBTGAOIFWNUVTBAZ";
static inline int rnd(void)
{
	static unsigned long long seed = 127;
	seed = (seed * 25214903917ULL + 11ULL);
	return (seed >> 16) & 0x7FFFFFFF;
}

char* rndstr() {
	static char str[512] = { 0 };
	if (str[0] == 0) {
		for (int i = 0; i < 511; i++) {
			str[i] = 'A' + rnd() % 26;
		}
	}
	char c = 'A' + rnd() % 26;
	str[rnd() % 511] = c;
	return str;
}

int main() {
	int RESULT = 0;
	clock_t st, ed;
	st = clock();
	for (register int i = 0; i < 1000; i++) {
		append_train(rndstr());
	}
	int size = 1000;
	while (size < 99999) {
		if ((rnd() % 10) == 0) {
			append_train(rndstr());
			size++;
		}
		if ((rnd() % 2) == 0) {
			insert_train(rnd() % size, getTrainPassengerName(rnd() % size));
			size++;
		}
		else {
			erase_train(rnd() % size);
			size--;
		}
		if ((rnd() % 2 == 0)) {
			swapPassenger(rnd() % size, rnd() % size);
		}
		else {
			changePassengerName(rnd() % size, rndstr());
		}
	}
	char* ret = getTrainPassengerName(rnd() % size);
	ed = clock();
	RESULT += ((double)(ed - st) / (double)CLOCKS_PER_SEC) * 1000;
	
	// printf("%s\n", ret);

	if (strcmp(ret,ANS))
		RESULT += 1000000000;
	if (RESULT <= PASS) {
		printf("PASS\n", RESULT);
		printf("SCORE: %d ", RESULT);
	}
	else
		printf("FAIL: %d ", RESULT);
}





