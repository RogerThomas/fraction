#include "fraction.h"

fraction::fraction(int64_t n, int64_t d) : defaultMaxDen(1000) {
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

fraction & fraction::setNumerator(int64_t n) {
	numerator = n;
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
		int64_t n1 = numerator * f.denominator;
		int64_t n2 = f.numerator * denominator;
		return fraction(n1 - n2, denominator * f.denominator).reduce();
	}
}

fraction fraction::operator * (const double d) const {
	return (*this * getBestRA(d, defaultMaxDen));
}

fraction fraction::operator / (const double d) const {
	return (*this / getBestRA(d, defaultMaxDen));
}

fraction fraction::operator + (const double d) const {
	return (*this + getBestRA(d, defaultMaxDen));
}

fraction fraction::operator - (const double d) const {
	return (*this - getBestRA(d, defaultMaxDen));
}

fraction fraction::getBestRA(double x, const int64_t maxDen) {
	int8_t multiplier = 1;
	if (x < 0) {
		x = -x;
		multiplier = -1;
	}
	if (x > 1) {
		int64_t add = floor(x);
		x = x - add;
		fraction ret = bestRA(x, maxDen);
		return ret.setNumerator(multiplier * (ret.numerator + ret.denominator * add));
	} else {
		return bestRA(x, maxDen);
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
		return (numerator > f.numerator);
	} else {
		int64_t n1 = numerator * f.denominator;
		int64_t n2 = f.numerator * denominator;
		return (n1 > n2);
	}
}

bool fraction::operator < (const fraction &f) const {
	if (denominator == f.denominator) {
		return (numerator < f.numerator);
	} else {
		int64_t n1 = numerator * f.denominator;
		int64_t n2 = f.numerator * denominator;
		return (n1 < n2);
	}
}

bool fraction::operator >= (const fraction &f) const {
	if (denominator == f.denominator) {
		return (numerator >= f.numerator);
	} else {
		int64_t n1 = numerator * f.denominator;
		int64_t n2 = f.numerator * denominator;
		return (n1 >= n2);
	}
}

bool fraction::operator <= (const fraction &f) const {
	if (denominator == f.denominator) {
		return (numerator <= f.numerator);
	} else {
		int64_t n1 = numerator * f.denominator;
		int64_t n2 = f.numerator * denominator;
		return (n1 <= n2);
	}
}

double fraction::toDouble() const {
	return ((double) numerator / (double) denominator);
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

/*
* ----------------------------Private methods---------------------------------
*/

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

fraction fraction::bestRA(const double x, const int64_t maxDen) {
	fraction a(0, 1);
	fraction b(1, 1);
	fraction temp;

	double mid = 0.0;

	while ((a.denominator <= maxDen) && (b.denominator <= maxDen)) {
		temp = fraction(a.numerator + b.numerator, a.denominator + b.denominator);
		mid = temp.toDouble();
		if (x == mid) {
			if (temp.denominator <= maxDen) {
				return temp;
			} else if (b.denominator > a.denominator) {
				return b;
			} else {
				return a;
			}
		} else if (x > mid) {
			a = temp;
		} else {
			b = temp;
		}
	}
	if (a.denominator > maxDen) {
		return b;
	} else {
		return a;
	}
}
