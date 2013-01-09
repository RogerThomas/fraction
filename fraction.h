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
		fraction() : numerator(1), denominator(1) {};
		fraction(int64_t n, int64_t d);
		~fraction();

		fraction & reduce();

		fraction getReduced() const;

		fraction operator * (const fraction &f) const;
		fraction operator / (const fraction &f) const;
		const fraction operator + (const fraction &f) const;
		fraction operator - (const fraction &f) const;
		
		fraction & multiplyBy(int64_t val);
		fraction & multiplyBy(const fraction &val);

		bool operator == (const fraction &f) const;
		bool operator != (const fraction &f) const;

		bool operator > (const fraction &f) const;
		bool operator < (const fraction &f) const;
		
		bool operator >= (const fraction &f) const;
		bool operator <= (const fraction &f) const;

		string toText() const;

		double toDouble() const;

		void display() const;

		friend ostream & operator << (ostream &out, const fraction &f);

	private:
		static int64_t getGcd(int64_t n, int64_t d);

		int64_t numerator;
		int64_t denominator;
};

#endif
