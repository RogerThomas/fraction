#include <iostream>
#include "fraction.h"
#include <sys/time.h>
#include <time.h>

using namespace std;

int genRand(int max) {
	return ((double)rand() / (double)RAND_MAX) * max + 1;
}
//sda
int main() {
	//srand(time(NULL));
	srand(42);

	fraction a(genRand(100), genRand(100));
	fraction b(genRand(100), genRand(100));
	cout << "a = " << a.toText() << ", b = " << b.toText() << endl;

	clock_t t1, t2;
	int amount = 1000000;
	t1 = clock();
	for(int i = 0; i < amount; i++) {a * b;}
	t2 = clock();

	cout << "Operator took " << (double)(t2 - t1) / ((double)CLOCKS_PER_SEC) << endl;

	t1 = clock();
	for(int i = 0; i < amount; i++) {a.multiply(b);}
	t2 = clock();

	cout << "Function took " << (double)(t2 - t1) / ((double)CLOCKS_PER_SEC) << endl;

	cout << "Value = " << a.multiply(b).toText() << endl;
	cout << "Value = " << (a * b).toText() << endl;
	cout << "Value = " << a * b << endl;
	return 1;
}
