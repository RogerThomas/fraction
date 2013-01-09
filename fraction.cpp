#include "fraction.h"

fraction::fraction(int64_t n, int64_t d) {
	if (d == 0) {
		fprintf(stderr, "Error: Please ensure denominator is non-zero\n");
		exit(EXIT_FAILURE);
	} else if (d < 0) {
		//Multiply above and below by -1 to ensure denominator is non negative
		numerator = -n;
		denominator = -d;
	} else {
		numerator = n;
		denominator = d;
	}
}

fraction::~fraction() {

}

fraction & fraction::reduce() {
	int64_t gcd = getGcd((numerator < 0) ? -numerator : numerator, denominator);
	numerator /= gcd;
	denominator /= gcd;
	return *this;
}

fraction fraction::getReduced() const {
	int64_t gcd = getGcd((numerator < 0) ? -numerator : numerator, denominator);
	return fraction(numerator / gcd, denominator / gcd);
}

fraction fraction::operator * (const fraction &f) const {
	return fraction(numerator * f.numerator, denominator * f.denominator).reduce();
}

fraction fraction::operator / (const fraction &f) const {
	if (f.numerator < 0) {
		//Multiply above and below by -1 to ensure resulting minus is expressed in numerator
		return fraction(numerator * -f.denominator, denominator * -f.numerator).reduce();
	} else {
		return fraction(numerator * f.denominator, denominator * f.numerator).reduce();
	}
}

const fraction fraction::operator + (const fraction &f) const {
	if(denominator == f.denominator) {
		return fraction(numerator + f.numerator, denominator);
	} else {
		int64_t n1 = numerator * f.denominator;
		int64_t n2 = f.numerator * denominator;
		return fraction(n1 + n2, denominator * f.denominator).reduce();
	}
}

fraction fraction::operator - (const fraction &f) const {
	if(denominator == f.denominator) {
		return fraction(numerator - f.numerator, denominator);
	} else {
		int64_t n1 = numerator * f.denominator;
		int64_t n2 = f.numerator * denominator;
		return fraction(n1 - n2, denominator * f.denominator).reduce();
	}
}

bool fraction::operator == (const fraction &f) const {
	fraction f1 = this->getReduced();
	fraction f2 = f.getReduced();
	return (f1.numerator == f2.numerator && f1.denominator == f2.denominator);
}

bool fraction::operator != (const fraction &f) const {
	return !(*(this) == f);
}

bool fraction::operator > (const fraction &f) const {
	if (denominator == f.denominator) {
		return numerator > f.numerator;
	} else {
		int64_t n1 = numerator * f.denominator;
		int64_t n2 = f.numerator * denominator;
		return n1 > n2;
	}
}

bool fraction::operator < (const fraction &f) const {
	if (denominator == f.denominator) {
		return numerator < f.numerator;
	} else {
		int64_t n1 = numerator * f.denominator;
		int64_t n2 = f.numerator * denominator;
		return n1 < n2;
	}
}

bool fraction::operator >= (const fraction &f) const {
	if (denominator == f.denominator) {
		return numerator >= f.numerator;
	} else {
		int64_t n1 = numerator * f.denominator;
		int64_t n2 = f.numerator * denominator;
		return n1 >= n2;
	}
}

bool fraction::operator <= (const fraction &f) const {
	if (denominator == f.denominator) {
		return numerator <= f.numerator;
	} else {
		int64_t n1 = numerator * f.denominator;
		int64_t n2 = f.numerator * denominator;
		return n1 <= n2;
	}
}

double fraction::toDouble() const {
	return (double) numerator / (double) denominator;
}

ostream & operator << (ostream &out, const fraction &f) {
	out << f.numerator << " / " << f.denominator;
	return out;
}

string fraction::toText() const {
	ostringstream out;
	out << numerator << " / " << denominator;
	return out.str();
}

void fraction::display() const {
	cout << toText() << endl;
}

int64_t fraction::getGcd(int64_t n, int64_t d) {
	if(d > n) {
		int64_t temp = n;
		n = d;
		d = temp;
	}
	int64_t r;
	while(d != 0) {
		r = n % d;
		n = d;
		d = r;
	}
	return n;
}

