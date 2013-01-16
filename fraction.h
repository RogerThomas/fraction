#ifndef _H_FRACTION
#define _H_FRACTION

#include <iostream>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

class fraction {
	public:
		fraction() : numerator(1), denominator(1), defaultMaxDen(1000) {};
		fraction(int64_t n, int64_t d);
		~fraction();

		fraction & reduce();
		fraction & setNumerator(int64_t n);

		fraction getReduced() const;
	
		//Fraction fraction operations
		fraction operator * (const fraction &f) const;
		fraction operator / (const fraction &f) const;
		fraction operator + (const fraction &f) const;
		fraction operator - (const fraction &f) const;

		//Fraction double operations
		fraction operator * (const double d) const;
		fraction operator / (const double d) const;
		fraction operator + (const double d) const;
		fraction operator - (const double d) const;

		static fraction getBestRA(double x, const int64_t maxDen);
		
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

		static fraction bestRA(const double x, const int64_t maxDen);

		int64_t numerator;
		int64_t denominator;
		int64_t defaultMaxDen;
};

#endif
