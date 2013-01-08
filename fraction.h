#ifndef _H_FRACTION
#define _H_FRACTION

#include <iostream>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class fraction {
	public:
		fraction(int64_t n, int64_t d);

		int64_t get_gcd(int64_t n, int64_t d) const;
		int64_t get_lcm(int64_t d1, int64_t d2) const;

		fraction multiply(const fraction &f) const;
		fraction operator*(const fraction &f) const;

		fraction divide(const fraction &f) const;
		fraction add(const fraction &f) const;
		fraction subtract(const fraction &f) const;
		fraction reduce();

		fraction getReduced() const;

		bool isEqual(const fraction &f) const;
		bool notEqual(const fraction &f) const;

		bool isGreater(const fraction &f) const;
		bool isLess(const fraction &f) const;
		
		string toText() const;
		double toDouble() const;

		void display() const;

		friend ostream& operator<<(ostream& out, const fraction& f);
	private:
		void ensureMax(int64_t &, int64_t &) const;

		int64_t numerator;
		int64_t denominator;
};

#endif