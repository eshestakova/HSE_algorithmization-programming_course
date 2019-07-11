#include<iostream>

using namespace std;

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
	Elem(int x_, int y_, float v_) : x(x_), y(y_), value(v_) {}
};

class SparseM
{
	int N;
	int M;

	int size;
	Elem* Elements;

public:

	SparseM() : N(0), M(0), size(0) { Elements = new Elem; }
	SparseM(int n, int m, int s, Elem* elems) : N(n), M(m), size(s), Elements(elems) {}
	SparseM(SparseM* m)	{ N = m->N; M = m->M; size = m->size; Elements = m->Elements; }
	~SparseM() { }

	//-----------------------------------------------------------------------------------------	
	
	int getN() { return N; }
	int getM() { return M; }
	int getSize() { return size; }
	Elem* getElements() { return Elements; }

	void setN(int N_) { N = N_; }
	void setM(int M_) { M = M_; }
	void setSize(int s_) { size = s_; }
	void setElements(Elem* e) { Elements = e; }

	//-----------------------------------------------------------------------------------------	

	float getElem(int x_, int y_) const;
	float operator() (int x_, int y_) const;
	void addElem(int x_, int y_, float v_);
	void changeElem(int x, int y, float new_value);

	//-----------------------------------------------------------------------------------------	

	void PrintElems();
	void Print();

	friend ostream& operator<< (ostream& out, SparseM m);
	friend istream& operator>> (istream& in, SparseM& m);

	SparseM& operator= (SparseM& m);
	SparseM& operator+ (SparseM& m);
	SparseM& operator- (SparseM& m);
	SparseM& operator* (SparseM& m);

	float operator~ (); //приведение к базовому типу данных

};

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
	cout << endl << "------ Matrix (" << N << "x" << M << ") ------" << endl;
	for (int a = 0; a < N; a++)
	{
		for (int b = 0; b < M; b++)
		{
			float this_el = getElem(a, b);
			cout << this_el << " ";
		}
		cout << endl;
	}
}

ostream& operator<< (ostream& out, SparseM m)
{
	out << endl << "------ Matrix (" << m.N << "x" << m.M << ") ------" << endl;
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

istream& operator>> (istream& in, SparseM& m)
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

SparseM& SparseM::operator= (SparseM& m)
{
	N = m.N;
	M = m.M;
	size = m.size;
	Elements = m.Elements;
	return *this;
}

SparseM& SparseM::operator+ (SparseM& m)
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

SparseM& SparseM::operator- (SparseM& m)
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

SparseM& SparseM::operator* (SparseM& m)
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
					c += getElem(i,k) * m(k,j);

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

int main()
{
	// create matrix m1:
	int size = 3;
	Elem* el1 = new Elem[size];
	el1[0] = Elem(1, 1, 1);
	el1[1] = Elem(4, 1, 2);
	el1[2] = Elem(2, 2, 3);
	SparseM m1(5, 5, size, el1);

	// create matrix m2:
	Elem* el2 = new Elem[size];
	el2[0] = Elem(1, 2, 4);
	el2[1] = Elem(4, 1, 5);
	el2[2] = Elem(2, 2, 6);
	SparseM m2(5, 5, size, el2);

	cout << m1 << m2 << endl;

	// test methods:
	cout << "Characteristics (base data type): m1->" << ~m1 << "; m2->" << ~m2 << endl << endl;
	SparseM sum = SparseM(m1 + m2);
	SparseM dif = SparseM(m1 - m2);
	SparseM prd = SparseM(m1 * m2);
	cout << "Sum:\n" << sum << "\nDifference:\n" << dif << "\nProduct:\n" << prd;

	return 0;
}