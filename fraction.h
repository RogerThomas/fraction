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

		fraction & reduce();

		fraction getReduced() const;

		fraction operator * (const fraction &f) const;
		fraction operator / (const fraction &f) const;
		fraction operator + (const fraction &f) const;
		fraction operator - (const fraction &f) const;

		bool operator == (const fraction &f) const;
		bool operator != (const fraction &f) const;

		bool operator > (const fraction &f) const;
		bool operator < (const fraction &f) const;
		
		bool operator >= (const fraction &f) const;
		bool operator <= (const fraction &f) const;

		string toText() const;

		double toDouble() const;

		void display() const;

		friend ostream& operator<<(ostream& out, const fraction& f);

		~fraction();
	private:
		static void ensureMax(int64_t &, int64_t &);

		static int64_t getGcd(int64_t n, int64_t d);
		static int64_t getLcm(int64_t d1, int64_t d2);

		int64_t numerator;
		int64_t denominator;
};

#endif
