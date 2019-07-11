
#include <vector> 
#include <iterator> 
#include <iostream>

using namespace std;

class ADT
{
public:
	void* a;
	int t;

	ADT() { t = 0; a = NULL; }
	ADT(void* q, int t1 = 0) { t = t1; a = q; }

	virtual ~ADT() {}

	bool operator> (ADT A) { return (a > A.a); }
	bool operator< (ADT A) { return (a < A.a); }
	bool operator>= (ADT A) { return (a >= A.a); }
	bool operator<= (ADT A) { return (a <= A.a); }

	friend ostream& operator<< (ostream & out, ADT A);
	friend istream& operator>> (istream & in, ADT A);
};

//------------------------------ Int ----------------------------------

class Int : public ADT
{
	int n;
public:
	Int() : n(0), ADT(&n) {};
	Int(int a_) : n(a_), ADT(&n) {};

	friend ostream& operator<< (ostream& out, Int i) { out << *static_cast<int*>(i.a); return out; }
	friend istream& operator>> (istream& in, Int& i) { in >> *static_cast<int*>(i.a); return in; }
};

//------------------------------- Polynom ---------------------------------

struct Element
{
	double coeff;
	int pow;

	Element() : coeff(0), pow(0) {}
	Element(double c, int p) : coeff(c), pow(p) {}

	friend istream& operator>> (istream& in, Element& e);
};

class Polynom : public ADT
{
public:
	Element elem;
	Polynom* next;

	Polynom() : elem(Element()), ADT(this, 1) { next = NULL; }
	Polynom(Element e) : elem(e), ADT(this, 1) { next = NULL; }
	Polynom(Polynom* p) : elem(p->elem), ADT(this, 1) { if (p->next) next = p->next; else next = NULL; }
	~Polynom() {}

	void print();

	void addElem(double coeff_, int pow_);
	void changeCoeff(double coeff_, int pow_);

	int maxPow(int thismax);

	double getCoeff(int pow_) const;
	double operator() (int pow_) const;

	double operator~ (); //приведение к базовому типу данных

	friend ostream& operator<< (ostream& out, Polynom& p);
	friend istream& operator>> (istream& in, Polynom& p);

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

double Polynom::getCoeff(int pow_) const
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

ostream& operator<< (ostream & out, Polynom & p)
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

istream& operator>> (istream & in, Element & e)
{
	cout << endl << "input new element:" << endl << "\tcoeff: ";
	in >> e.coeff;
	cout << "\tpower: ";
	in >> e.pow;
	return in;
}

istream& operator>> (istream & in, Polynom & p)
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

Polynom& Polynom::operator= (Polynom & p)
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

Polynom& Polynom::operator+ (Polynom & p)
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

Polynom& Polynom::operator- (Polynom & p)
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

//-------- ADT ---------

ostream& operator<< (ostream & out, ADT A)
{
	switch (A.t)
	{
	case 0:
		out << *static_cast<int*>(A.a) << '\n';
		break;
	case 1:
		(static_cast<Polynom*>(A.a))->print();
		out << "\n";
		break;
	}
	return out;
}

istream& operator>> (istream & in, ADT A)
{
	switch (A.t)
	{
	case 0:
		in >> *static_cast<int*>(A.a);
		break;
	case 1:
		in >> *static_cast<Polynom*>(A.a);
		break;
	}
	return in;
}

//------------------------- List -------------------------

class List
{
	class Node
	{
	private:
		ADT value;
		Node* next;

	public:

		Node() { next = nullptr; value = ADT(); }
		Node(const Node& orig) : value(orig.value), next(orig.next) {}
		~Node() { delete& next; }

		Node* getprev(Node* h)
		{
			Node* ptr = h;
			while (ptr->getnext() != this)
			{
				ptr = ptr->getnext();
			}
			return ptr;
		}
		Node* getnext() { if (this) return next; else return NULL; }
		ADT getvalue() { if (this) return value; else return NULL; }

		void setprev(Node* pr, Node* h)
		{
			Node* ptr = h;
			while (ptr->getnext() != this)
			{
				ptr = ptr->getnext();
			}
			ptr = pr;
		}
		void setnext(Node* nx) { next = nx; }
		void setvalue(ADT v) { value = v; }
	};

	int len;
	Node* head, * tail, * ptr;

public:
	class iter : public iterator<bidirectional_iterator_tag, ADT>
	{
	public:

		Node* ptr;

		iter() : ptr(0) {}
		iter(Node* p) : ptr(p) {}

		iter& operator++ (int) { ptr = ptr->getnext();	return *this; }
		iter& operator++ () { ptr = ptr->getnext();	return *this; }
		iter& operator+ (int a) { for (int i = 0; i < a; i++) { ptr = ptr->getnext(); }	return *this; }
		Node& operator* () { return *ptr; }
		ADT operator-> () { return ptr->getvalue(); }
		bool operator== (iter& right) { return ptr == right.ptr; }
		bool operator!= (iter& right) { return ptr != right.ptr; }

		ADT operator()() const { return ptr->getvalue(); }
	};

	List() : head(nullptr), tail(nullptr), ptr(nullptr), len(0) {}
	List(const List& orig) : len(orig.len), head(orig.head), tail(orig.tail), ptr(orig.tail) {}
	~List() { }

	iter begin() { return iter(head); }
	iter end() { return iter(tail); }

	int getLen() { return len; }
	Node* gethead() { return head; }
	Node* gettail() { return tail; }

	void addHead(ADT val);
	void addTail(ADT val);
	void insert_pos(ADT val, int pos);
	void insert_node_pos(Node* n, int pos);
	void insert(ADT val);
	void del(Node* n);

	void sort(iter first, iter last);

	void print();
	friend ostream& operator<< (ostream& out, List& L)
	{
		if (L.len != 0)
		{
			iter its = L.begin();
			iter ite = L.end();

			while (its != ite)
			{
				out << its() << ", ";
				its++;
			}
			out << ite() << endl;
		}
		return out;
	}
	friend istream& operator>> (istream& in, List& L);
};

void List::addHead(ADT val)
{
	Node* temp = new Node;
	temp->setvalue(val);
	temp->setnext(head);
	if (head != 0)
		head->setprev(temp, gethead());
	if (len == 0)
		head = tail = temp;
	else
		head = temp;
	len++;
}

void List::addTail(ADT val)
{
	Node* temp = new Node;
	temp->setnext(0);
	temp->setvalue(val);
	if (tail != 0)
		tail->setnext(temp);
	if (len == 0)
		head = tail = temp;
	else
		tail = temp;
	len++;
}

void List::insert_pos(ADT val, int pos)
{
	if (pos == len + 1)
	{
		addTail(val);
		return;
	}
	else if (pos == 1)
	{
		addHead(val);
		return;
	}

	int i = 1;
	Node* Ins = head;
	while (i < pos)
	{
		Ins = Ins->getnext();
		i++;
	}
	Node* PrevIns = Ins->getprev(head);
	Node* temp = new Node;

	if (PrevIns != 0 && len != 1)
		PrevIns->setnext(temp);

	temp->setnext(Ins);
	temp->setprev(PrevIns, gethead());
	temp->setvalue(val);
	Ins->setprev(temp, gethead());
	len++;
}

void List::insert_node_pos(Node * n, int pos)
{
	insert_pos(n->getvalue(), pos);
}


void List::del(Node * n)
{
	if (len == 1) { len = 0; return; }

	Node* Prev = n->getprev(gethead());
	Node* Next = n->getnext();

	if (Prev && Next)
	{
		n->getnext()->setprev(Prev, gethead());
		n->getprev(gethead())->setnext(Next);
	}
	else
	{
		if (Prev) n->getprev(gethead())->setnext(nullptr);
	}

	len--;
}

void List::insert(ADT val)
{
	if (val >= tail->getvalue())
	{
		addTail(val);
		return;
	}
	else if (val <= head->getvalue())
	{
		addHead(val);
		return;
	}

	int i = 1;
	Node* Ins = head;
	while (val < Ins->getvalue())
	{
		Ins = Ins->getnext();
		i++;
	}
	Node* PrevIns = Ins->getprev(gethead());
	Node* temp = new Node;

	if (PrevIns != 0 && len != 1)
		PrevIns->setnext(temp);

	temp->setnext(Ins);
	temp->setprev(PrevIns, gethead());
	temp->setvalue(val);
	Ins->setprev(temp, gethead());
	len++;
}

void List::sort(iter first, iter last)
{
	iter i = begin();
	iter e = end();
	while (i != e)
	{
		ADT val_i = i();
		ADT val_e = end()();

		if (i() > end()())
		{
			i.ptr->setvalue(val_e);
			end().ptr->setvalue(val_i);
		}
		i = iter(i.ptr->getnext());
	}
}

void List::print()
{
	if (len != 0)
	{
		iter its = begin();
		iter ite = end();

		while (its != ite)
		{
			cout << "~ " << its();
			its++;
		}
		cout << "~ " << ite() << endl;
	}
}

istream& operator>> (istream & in, List & L)
{
	List L1;
	cout << "\nHow many elements: ";
	int N;
	in >> N;
	for (int i = 1; i <= N; i++)
	{
		ADT el;
		cout << "\telement #" << i << ": ";
		cin >> el;
		L1.insert_pos(el, i);
	}
	L = L1;
	return in;
}

int main()
{
	List L;
	L.addHead(Int(20));
	L.addTail(Int(40));

	Polynom p1 = Polynom(Element(6, 7));
	p1.addElem(3, 3);
	L.insert_pos(p1, 3);

	L.insert_pos(Int(10), 4);

	cout << endl << "List (" << L.getLen() << " elements):\n";
	L.print();
	cout << endl;

	return 0;
}

