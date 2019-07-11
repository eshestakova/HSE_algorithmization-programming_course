#include <vector> 
#include <iterator> 
#include <iostream>

using namespace std;

//----------------------------- ADT -----------------------------------

class ADT
{
public:
	void* a;
	int t;

	ADT() { t = 0; a = NULL; }
	ADT(void* q, int t1=0) { t = t1; a = q; }

	virtual ~ADT() {}

	bool operator> (ADT A) { return (a > A.a); }
	bool operator< (ADT A) { return (a < A.a); }
	bool operator>= (ADT A) { return (a >= A.a); }
	bool operator<= (ADT A) { return (a <= A.a); }

	friend ostream& operator<< (ostream& out, ADT A);
	friend istream& operator>> (istream& in, ADT A);
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

//------------------------------- Sparse-Matrix ---------------------------------

struct Elem
{
	int x;
	int y;
	float value;

	friend ostream& operator<< (ostream& out, const Elem e)
	{
		out << e.value << " { " << e.x << ", " << e.y << " } ";
		return out;
	}

	Elem() : x(-1), y(-1), value(0) {}
	Elem(int v) : x(-1), y(-1), value(0) {}
	Elem(int x_, int y_, float v_) : x(x_), y(y_), value(v_) {}
};

class SparseM : public ADT
{
	int N;
	int M;

	int size;
	Elem* Elements;

public:

	SparseM() : N(0), M(0), size(0), ADT(this, 1) { Elements = new Elem; }
	SparseM(int n, int m, int s, Elem* elems) : N(n), M(m), size(s), Elements(elems), ADT(this, 1) {}
	SparseM(SparseM* m) : ADT(this, 1) { N = m->N; M = m->M; size = m->size; Elements = m->Elements; }
	~SparseM() { }

	//------------------------------	

	int getN() { return N; }
	int getM() { return M; }
	int getSize() { return size; }
	Elem* getElements() { return Elements; }

	void setN(int N_) { N = N_; }
	void setM(int M_) { M = M_; }
	void setSize(int s_) { size = s_; }
	void setElements(Elem* e) { Elements = e; }

	//-------------------------------

	float getElem(int x_, int y_) const;
	float operator() (int x_, int y_) const;
	void addElem(int x_, int y_, float v_);
	void changeElem(int x, int y, float new_value);

	//------------------------------	

	void PrintElems();
	void Print();

	friend ostream& operator<< (ostream& out, SparseM m);
	friend istream& operator>> (istream& in, SparseM& m);

	SparseM& operator= (SparseM& m);
	SparseM operator+ (SparseM& m);
	SparseM operator- (SparseM& m);
	SparseM operator* (SparseM& m);

	float operator~ (); //приведение к базовому типу данных

};

//--------------ADT--------------------

ostream& operator<< (ostream& out, ADT A)
{
	switch (A.t)
	{
	case 0:
		out << *static_cast<int*>(A.a) << '\n';
		break;
	case 1:
		static_cast<SparseM*>(A.a)->Print();
		out << endl;
		break;
	}
	return out;
}

istream& operator>> (istream& in, ADT A)
{
	switch (A.t)
	{
	case 0:
		in >> *static_cast<int*>(A.a);
		break;
	case 1:
		in >> *static_cast<SparseM*>(A.a);
		break;
	}
	return in;
}

//--------------SparseM-----------------

float SparseM::getElem(int x_, int y_) const
{
	for (int i = 0; i < size; i++)
	{
		if (Elements[i].x == x_ && Elements[i].y == y_)
			return Elements[i].value;
	}
	return 0;
}

float SparseM::operator() (int x_, int y_) const
{
	for (int i = 0; i < size; i++)
	{
		if (Elements[i].x == x_ && Elements[i].y == y_)
			return Elements[i].value;
	}
	return 0;
}

void SparseM::addElem(int x_, int y_, float v_)
{
	if (x_ > N || y_ > M)
	{
		cout << "ERROR: Can't add, wrong element position";
		return;
	}

	Elem* temp = new Elem[size + 1];
	for (int i = 0; i < size; i++) temp[i] = Elements[i];
	temp[size] = Elem(x_, y_, v_);
	delete[] Elements;
	Elements = temp;
	size++;

	//ADT(this, sizeof(SparseM));
}

void SparseM::changeElem(int x, int y, float new_value)
{
	if (x > N || y > M)
	{
		cout << "ERROR: Can't change, wrong element position";
		return;
	}
	for (int i = 0; i < size; i++)
	{
		if (Elements[i].x == x && Elements[i].y == y)
		{
			Elements[i].value = new_value;
			return;
		}
	}
	addElem(x, y, new_value);
}

void SparseM::PrintElems()
{
	cout << endl << "------ Elements of matrix (" << N << "x" << M << ") ------" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << Elements[i].value << " (" << Elements[i].x << ", " << Elements[i].y << ")" << endl;
	}
	cout << endl;
}

void SparseM::Print()
{
	cout << "Matrix (" << N << "x" << M << ")";
	for (int a = 0; a < N; a++)
	{
		cout << endl << "  ";
		for (int b = 0; b < M; b++)
		{
			float this_el = getElem(a, b);
			cout << this_el << " ";
		}
	}
}

ostream& operator<< (ostream & out, SparseM m)
{
	out << endl << "Matrix (" << m.N << "x" << m.M << ")" << endl;
	for (int a = 0; a < m.N; a++)
	{
		for (int b = 0; b < m.M; b++)
		{
			float this_el = m(a, b);
			out << this_el << " ";
		}
		out << endl;
	}
	return out;
}

istream& operator>> (istream & in, SparseM & m)
{
	int N_, M_, x_, y_, size_;
	float value_;
	cout << endl << "Input x-size of the matrix: N = ";
	in >> N_;
	m.setN(N_);
	cout << endl << "Input y-size of the matrix: M = ";
	in >> M_;
	m.setM(M_);
	cout << endl << "Input number of non-zero elements: ";
	in >> size_;
	m.setSize(size_);

	Elem* el = new Elem[size_];
	for (int i = 0; i < size_; i++)
	{
		cout << endl << "Input non-zero element:" << endl;
		cout << "\tx-coord: ";
		in >> x_;
		cout << "\ty-coord: ";
		in >> y_;
		cout << "\tvalue: ";
		in >> value_;

		el[i] = Elem(x_, y_, value_);
	}
	m.setElements(el);

	return in;
}

SparseM& SparseM::operator= (SparseM & m)
{
	N = m.N;
	M = m.M;
	size = m.size;
	Elements = m.Elements;
	return *this;
}

SparseM SparseM::operator+ (SparseM & m)
{
	SparseM m_ = new SparseM;
	if (N == m.N && M == m.M)
	{
		m_.setN(N);
		m_.setM(M);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				float el_1 = getElem(i, j);
				float el_2 = m(i, j);

				if (el_1 + el_2 != 0)
					m_.addElem(i, j, el_1 + el_2);
			}
		}
	}
	else cout << "ERROR: Can't sum, sizes are not equal";
	return m_;
}

SparseM SparseM::operator- (SparseM & m)
{
	SparseM m_ = new SparseM;
	if (N == m.N && M == m.M)
	{
		m_.setN(N);
		m_.setM(M);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				float el_1 = getElem(i, j);
				float el_2 = m(i, j);

				if (el_1 - el_2 != 0)
					m_.addElem(i, j, el_1 - el_2);
			}
		}
	}
	else cout << "ERROR: Can't sum, sizes are not equal";
	return m_;
}

SparseM SparseM::operator* (SparseM & m)
{
	SparseM m_ = new SparseM;
	if (N == m.M)
	{
		int n = N;
		m_.setN(M);
		m_.setM(m.N);

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < m.M; j++)
			{
				float c = 0;
				for (int k = 0; k < M; k++)
					c += getElem(i, k) * m(k, j);

				if (c != 0)
					m_.addElem(i, j, c);
			}
		}
	}
	else cout << "ERROR: Can't multiply, sizes are wrong";
	return m_;
}

float SparseM::operator~ ()
{
	float res = 0;
	for (int a = 0; a < N; a++)
	{
		for (int b = 0; b < M; b++)
			res += getElem(a, b);
	}
	return res;
}

//---------------------------- 2-linked-list ------------------------------------------------

class List
{
	class Node
	{
	private:
		ADT value;
		Node* next, * prev;

	public:

		Node() { next = nullptr; prev = nullptr; value = ADT(); }
		Node(const Node& orig) : value(orig.value), next(orig.next), prev(orig.prev) {}
		~Node() { delete& next; delete& prev; }

		Node* getnext() { return next; }
		Node* getprev() { return prev; }
		ADT& getvalue() { return value; }

		void setprev(Node* pr) { prev = pr; }
		void setnext(Node* nx) { next = nx; }
		void setvalue(ADT v) { value = v; }
	};

	int len;
	Node* head, * tail, * ptr;

public:

	//-------------------------------

	class iter : public iterator<bidirectional_iterator_tag, ADT>
	{
	public:

		Node* ptr;

		iter() : ptr(0) {}
		iter(Node* p) : ptr(p) {}

		iter& operator++ (int) { ptr = ptr->getnext();	return *this; }
		iter& operator-- (int) { ptr = ptr->getprev();	return *this; }
		iter& operator++ () { ptr = ptr->getnext();	return *this; }
		iter& operator-- () { ptr = ptr->getprev();	return *this; }
		iter& operator+ (int a) { for (int i = 0; i < a; i++) { ptr = ptr->getnext(); }	return *this; }
		iter& operator- (int a) { for (int i = 0; i < a; i++) { ptr = ptr->getprev(); }	return *this; }
		Node& operator* () { return *ptr; }
		ADT& operator-> () { return ptr->getvalue(); }
		bool operator== (iter& right) { return ptr == right.ptr; }
		bool operator!= (iter& right) { return ptr != right.ptr; }

		ADT operator()() const { return ptr->getvalue(); }
	};

	iter begin() { return iter(head); }
	iter end() { return iter(tail); }

	//--------------------------------

	List() : head(nullptr), tail(nullptr), ptr(nullptr), len(0) {}
	List(const List& orig) : len(orig.len), head(orig.head), tail(orig.tail), ptr(orig.tail) {}
	~List() { }

	int getLen() { return len; }

	void addHead(ADT val);
	void addTail(ADT val);
	void insert_pos(ADT val, int pos);
	void insert_node_pos(Node* n, int pos);
	void insert(ADT val);
	void del(Node* n);

	void sort(iter first, iter last);

	void print();
	friend istream& operator>> (istream& in, List& L);
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
};

void List::addHead(ADT val)
{
	Node* temp = new Node;
	temp->setprev(0);
	temp->setvalue(val);
	temp->setnext(head);
	if (head != 0)
		head->setprev(temp);
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
	temp->setprev(tail);
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
	Node* PrevIns = Ins->getprev();
	Node* temp = new Node;

	if (PrevIns != 0 && len != 1)
		PrevIns->setnext(temp);

	temp->setnext(Ins);
	temp->setprev(PrevIns);
	temp->setvalue(val);
	Ins->setprev(temp);
	len++;
}

void List::insert_node_pos(Node * n, int pos)
{
	insert_pos(n->getvalue(), pos);
}


void List::del(Node * n)
{
	if (len == 1) { len = 0; return; }

	Node* Prev = n->getprev();
	Node* Next = n->getnext();

	if (Prev && Next)
	{
		n->getnext()->setprev(Prev);
		n->getprev()->setnext(Next);
	}
	else
	{
		if (Prev) n->getprev()->setnext(nullptr);
		if (Next) n->getnext()->setprev(nullptr);
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
	Node* PrevIns = Ins->getprev();
	Node* temp = new Node;

	if (PrevIns != 0 && len != 1)
		PrevIns->setnext(temp);

	temp->setnext(Ins);
	temp->setprev(PrevIns);
	temp->setvalue(val);
	Ins->setprev(temp);
	len++;
}

void List::sort(iter first, iter last)
{
	iter i = begin();
	iter e = end();
	while (i != e)
	{
		Node* prev_i = i.ptr->getprev();
		Node* next_i = i.ptr->getnext();
		ADT val_i = i();

		Node* prev_e = end().ptr->getprev();
		Node* next_e = end().ptr->getnext();
		ADT val_e = end()();

		if (i() > end()())
		{
			i.ptr->setvalue(val_e);
			end().ptr->setvalue(val_i);
		}
		i = iter(next_i);
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

//------------------------------- Main ---------------------------------------

int main()
{
	List L;

	// add Int:
	L.insert_pos(Int(20), 1);
	L.insert_pos(Int(40), 2);
	L.insert_pos(Int(30), 3);

	// add SparseM:
	int size = 3;
	Elem* el1 = new Elem[size];
	el1[0] = Elem(1, 1, 1);
	el1[1] = Elem(4, 1, 2);
	el1[2] = Elem(2, 2, 3);
	SparseM m1(5, 5, size, el1);

	L.insert_pos(m1, 2);

	cout << endl << "List (" << L.getLen() << " elements):" << endl << endl;
	L.print();
	cout << endl;

	return 0;
}