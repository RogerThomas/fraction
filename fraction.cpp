#include "fraction.h"

fraction::fraction(int64_t n, int64_t d) {
	if (d <= 0) {
		fprintf(stderr, "Error: Please ensure denominator is non-zero and positive\n");
		fprintf(stderr, "To indicate negation please use numerator\n");
		exit(EXIT_FAILURE);
	}
	numerator = n;
	denominator = d;
}

fraction::~fraction() {

}

inline void fraction::ensureMax(int64_t &n, int64_t &d) {
	if(d > n) {
		int64_t temp = n;
		n = d;
		d = temp;
	}
}

int64_t fraction::getGcd(int64_t n, int64_t d) {
	ensureMax(n, d);
	uint64_t r;
	while(d != 0) {
		r = n % d;
		n = d;
		d = r;
	}
	return n;
}

int64_t fraction::getLcm(int64_t d1, int64_t d2) {
	return d1 * d2 / getGcd(d1, d2);
}

fraction fraction::operator * (const fraction &f) const {
	return fraction(numerator * f.numerator, denominator * f.denominator).reduce();
}

fraction fraction::operator / (const fraction &f) const {
	if (f.numerator < 0) {
		//Multiply above and below by -1 to ensure resulting minus is expressed in nuerator
		return fraction(numerator * -f.denominator, denominator * -f.numerator).reduce();
	} else {
		return fraction(numerator * f.denominator, denominator * f.numerator).reduce();
	}
}

fraction fraction::operator + (const fraction &f) const {
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
		int64_t lcm = getLcm(denominator, f.denominator);
		int64_t n1 = numerator * (lcm / denominator);
		int64_t n2 = f.numerator * (lcm / f.denominator);
		return fraction(n1 - n2, lcm).reduce();
	}
}

fraction & fraction::reduce() {
	int64_t gcd= getGcd((numerator < 0) ? -numerator : numerator, denominator);
	numerator /= gcd;
	denominator /= gcd;
	return *this;
}

fraction fraction::getReduced() const {
	int64_t gcd = getGcd((numerator < 0) ? -numerator : numerator, denominator);
	return fraction(numerator / gcd, denominator / gcd);
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
		int64_t lcm = getLcm(denominator, f.denominator);
		int64_t n1 = numerator * (lcm / denominator);
		int64_t n2 = f.numerator * (lcm / f.denominator);
		return n1 > n2;
	}
}

bool fraction::operator < (const fraction &f) const {
	if (denominator == f.denominator) {
		return numerator < f.numerator;
	} else {
		int64_t lcm = getLcm(denominator, f.denominator);
		int64_t n1 = numerator * (lcm / denominator);
		int64_t n2 = f.numerator * (lcm / f.denominator);
		return n1 < n2;
	}
}

bool fraction::operator >= (const fraction &f) const {
	if (denominator == f.denominator) {
		return numerator >= f.numerator;
	} else {
		int64_t lcm = getLcm(denominator, f.denominator);
		int64_t n1 = numerator * (lcm / denominator);
		int64_t n2 = f.numerator * (lcm / f.denominator);
		return n1 >= n2;
	}
}

bool fraction::operator <= (const fraction &f) const {
	if (denominator == f.denominator) {
		return numerator <= f.numerator;
	} else {
		int64_t lcm = getLcm(denominator, f.denominator);
		int64_t n1 = numerator * (lcm / denominator);
		int64_t n2 = f.numerator * (lcm / f.denominator);
		return n1 <= n2;
	}
}

double fraction::toDouble() const {
	return (double) numerator / (double) denominator;
}

ostream& operator << (ostream &out, const fraction &f) {
	out << f.numerator << " / " << f.denominator;
	return out;
}

string fraction::toText() const {
	ostringstream out;
	out << numerator << " / " << denominator;
	return out.str();
}

void fraction::display() const {
	cout << toText();
}
