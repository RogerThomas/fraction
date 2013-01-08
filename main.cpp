#include <iostream>
#include "fraction.h"
#include <sys/time.h>
#include <time.h>

using namespace std;

int genRand(int max) {
	return ((double)rand() / (double)RAND_MAX) * max + 1;
}
int main() {
	//srand(time(NULL));
	srand(42);

	fraction a(genRand(100), genRand(100));
	fraction b(genRand(100), genRand(100));

	fraction f1(2, 6);
	fraction f2(4, 12);

	cout << "a = " << a << ", b = " << b << endl;
	cout << "f1 = " << f1 << ", f2 = " << f2 << endl;

	cout << "a + b = " << a + b << endl;
	cout << "a - b = " << a - b << endl;
	cout << "a * b = " << a * b << endl;
	cout << "a / b = " << a / b << endl;

	if (f1 == f2) 
		cout << "f1 does equal f2\n";
	
	if (a != b) 
		cout << "a does not equal b\n";

	if (a > b)
		cout << "a is greater than b\n";

	if (b < a)
		cout << "b is less than a\n";

	if (f1 <= f2)
		cout << "f1 is less than or equal to f2\n";

	if (f1 >= f2)
		cout << "f1 is greater than or equal to f2\n";

	clock_t t1, t2;
	int amount = 1000000;
	t1 = clock();
	for(int i = 0; i < amount; i++) {a * b;}
	t2 = clock();

	cout << "Operator took " << (double)(t2 - t1) / ((double)CLOCKS_PER_SEC) << endl;

	cout << "Value = " << a * b << endl;
	return 1;
}
