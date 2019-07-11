#include<iostream>

using namespace std;

struct Element
{
	double coeff;
	int pow;

	Element() : coeff(0), pow(0) {}
	Element(double c, int p) : coeff(c), pow(p) {}

	friend istream& operator>> (istream& in, Element& e);
};

class Polynom
{
public:
	Element elem;
	Polynom* next;

	Polynom() : elem(Element()) { next = NULL; }
	Polynom(Element e) : elem(e) { next = NULL; }
	Polynom(Polynom* p) : elem(p->elem) { if (p->next) next = p->next; else next = NULL; }
	~Polynom() {}

	void print();

	void addElem(double coeff_, int pow_);
	void changeCoeff(double coeff_, int pow_);

	int maxPow(int thismax);

	double getCoeff(int pow_) const;
	double operator() (int pow_) const;

	double operator~ (); //приведение к базовому типу данных

	friend ostream& operator<< (ostream& out, Polynom& p);
	friend istream& operator>> (istream& in,  Polynom& p);

	Polynom& operator= (Polynom& p);
	Polynom& operator+ (Polynom& p);
	Polynom& operator- (Polynom& p);
};

void Polynom::print()
{
	if (elem.coeff != 0)
	{
		if (abs(elem.coeff) != 1) cout << abs(elem.coeff);
		cout << " (x^" << elem.pow << ")";
	}
	if (next)
	{
		if (next->elem.coeff > 0) cout << " + ";
		if (next->elem.coeff < 0) cout << " - ";
		next->print();
	}
}

void Polynom::addElem(double coeff_, int pow_)
{
	if (next)
		next->addElem(coeff_, pow_);
	else
	{
		Polynom* tmp = new Polynom(Element(coeff_, pow_));
		next = tmp;
	}
}

void Polynom::changeCoeff(double coeff_, int pow_)
{
	if (elem.pow == pow_)
		elem.coeff = coeff_;
	else
		next->changeCoeff(coeff_, pow_);
}

double Polynom::getCoeff (int pow_) const
{
	if (elem.pow == pow_)
	{
		if (elem.coeff)	return elem.coeff;
		else return 0;
	}
	else
	{
		if (next) return next->getCoeff(pow_);
		else return 0;
	}
}

double Polynom::operator() (int pow_) const
{
	return getCoeff(pow_);
}

double Polynom::operator~ ()
{
	return getCoeff(0);
}

ostream& operator<< (ostream& out, Polynom& p)
{
	if (p.elem.coeff != 0)
	{
		if (abs(p.elem.coeff) != 1) out << abs(p.elem.coeff);
		out << " (x^" << p.elem.pow << ")";

		if (p.next)
		{
			if (p.next->elem.coeff > 0) out << " + ";
			if (p.next->elem.coeff < 0) out << " - ";
		}
	}
	if (p.next)	out << *p.next;
	
	return out;
}

istream& operator>> (istream& in, Element& e)
{
	cout << endl << "input new element:" << endl << "\tcoeff: ";
	in >> e.coeff;
	cout << "\tpower: ";
	in >> e.pow;
	return in;
}

istream& operator>> (istream& in, Polynom& p)
{
	cout << endl << "\tAdd new element? (1 for 'yes' or 0 for 'no') ";
	int add;
	in >> add;

	if (add == 1)
	{
		int pow;
		double coeff;
		cout << endl << "\tinput new element:" << endl << "\t\tcoeff: ";
		in >> coeff;
		cout << "\t\tpower: ";
		in >> pow;
		p.addElem(coeff, pow);
		in >> p;
	}

	else return in;
}

Polynom& Polynom::operator= (Polynom& p)
{
	elem = p.elem;
	next = p.next;
	return *this;
}

int Polynom::maxPow(int thismax)
{
	if (elem.pow > thismax)
		if (next) return next->maxPow(elem.pow);
		else return elem.pow;
	else
		if (next) return next->maxPow(thismax);
		else return thismax;
}

Polynom& Polynom::operator+ (Polynom& p)
{
	Polynom res = Polynom(Element(0, 0));
	int pow1 = maxPow(0);
	int pow2 = p.maxPow(0);
	int maxpow = 0;
	if (pow1 > pow2) maxpow = pow1;
	else maxpow = pow2;

	for (int i = 0; i <= maxpow; i++)
	{
		double c1 = getCoeff(i);
		double c2 = p.getCoeff(i);
		if (c1 + c2 != 0) res.addElem(c1 + c2, i);
	}
	return res;
}

Polynom& Polynom::operator- (Polynom& p)
{
	Polynom res = Polynom(Element(0, 0));
	int pow1 = maxPow(0);
	int pow2 = p.maxPow(0);
	int maxpow = 0;
	if (pow1 > pow2) maxpow = pow1;
	else maxpow = pow2;

	for (int i = 0; i <= maxpow; i++)
	{
		double c1 = getCoeff(i);
		double c2 = p.getCoeff(i);
		if (c1 - c2 != 0) res.addElem(c1 - c2, i);
	}
	return res;
}

//----------------------------------------------------------------------

int main()
{
	cout << "Polynom 1:" << endl;
	Polynom p1 = Polynom(Element(6, 7));
	p1.addElem(3, 3);
	cout << p1;

	cout << endl << endl << "Input Polynom:" << endl;
	Polynom p2 = Polynom();
	cin >> p2;
	cout << endl << "Polynom 2:" << endl;
	cout << p2;

	Polynom sum = Polynom(p1 + p2);
	Polynom dif = Polynom(p1 - p2);
	cout << "\n\nSum:\n" << sum << "\nDifference:\n" << dif;

	return 0;
}