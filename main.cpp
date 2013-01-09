#include <iostream>
#include "fraction.h"
#include <sys/time.h>
#include <time.h>

using namespace std;

int genRand(int max) {
	return ((double)rand() / (double)RAND_MAX) * max + 1;
}

double iterate(char op, int64_t iters, const fraction &f1, const fraction &f2) {
	struct timeval timer1, timer2;
	gettimeofday(&timer1, NULL);
	switch (op) {
		case '*':
			for(int64_t i = 0; i < iters; i++) 
				f1 * f2;		
			break;
		case '-':
			for(int64_t i = 0; i < iters; i++) 
				f1 - f2;		
			break;
		case '/':
			for(int64_t i = 0; i < iters; i++) 
				f1 / f2;		
			break;
		case '+':
			for(int64_t i = 0; i < iters; i++) 
				f1 + f2;		
			break;
		default:
			fprintf(stderr, "op %c not recognized\n", op);
	}
	gettimeofday(&timer2, NULL);
	int64_t elapsedSeconds = timer2.tv_sec - timer1.tv_sec;
	int64_t elapsedUSeconds = timer2.tv_usec - timer1.tv_usec;

	return (elapsedSeconds + elapsedUSeconds / 1000000.0);
}

void timeOperators(int64_t iters, const fraction &f1, const fraction &f2) {
	char ops[4] = {'*', '-', '/', '+'};
	for(int8_t i = 0; i < 4; i++) {
		cout << iters << " iterations of operator " << ops[i];
		cout << " took " << iterate(ops[i], iters, f1, f2);
		cout << " seconds\n";
	}
}

int main(int argc, char *argv[]) {
	srand(42);
	fraction f(84375, 100000);
	f.reduce();
	cout << "f === " << f << endl;
	return 1;
	fraction a(genRand(100), genRand(100));
	fraction b(genRand(100), genRand(100));

	fraction f1(2, 6);
	fraction f2(4, 12);

	cout << "a = " << a << ", b = " << b << endl;
	cout << "f1 = " << f1 << ", f2 = " << f2 << endl << endl;

	cout << "a + b = " << a + b << endl;
	cout << "a - b = " << a - b << endl;
	cout << "a * b = " << a * b << endl;
	cout << "a / b = " << a / b << endl << endl;

	cout << "f1 == f2 = " << (f1 == f2) << endl;
	cout << "f1 != f2 = " << (f1 != f2) << endl;
	
	cout << "a > b = " << (a > b) << endl;
	cout << "a < b = " << (a < b) << endl;

	cout << "b < a = " << (b < a) << endl;
	cout << "b > a = " << (b > a) << endl;

	cout << "f1 <= f2 = " << (f1 <= f2) << endl;

	cout << "f1 >= f2 = " << (f1 >= f2) << endl;

	
	cout << "Value = " << a * b << endl;
	cout << "f2 = " << f2 << endl;
	f2.reduce();
	cout << "f2 = " << f2 << endl << endl;
	cout << "_f1 = " << f1.toText() << endl << endl;
	timeOperators(argc > 1 ? atoi(argv[1]) : 1000000, a, b);
	return 1;
}
