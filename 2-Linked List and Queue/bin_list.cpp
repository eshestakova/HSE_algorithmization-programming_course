#include <vector> 
#include <iterator> 
#include <iostream> 

using namespace std;

template <class T>
class List
{
private:
	class Node
	{
	public:
		Node() { Next = nullptr; Prev = nullptr; }
		Node(const Node &Other) : Value(Other.Value), Next(Other.Next), Prev(Other.Prev) {}
		~Node() { delete this; }

		Node* getNext() { return Next; }
		Node* getPrev() { return Prev; }
		T getValue() { return Value; }

		void setPrev(Node* pr) { Prev = pr; }
		void setNext(Node* nx) { Next = nx; }
		void setValue(T v) { Value = v; }
	private:
		T Value;
		Node *Next, *Prev;
	};

	int Length;
	Node *Head, *Tail, *This;

public:
	class my_iterator : public iterator<bidirectional_iterator_tag, T>
	{
	private:
		Node *This;
	public:
		my_iterator() { This = 0;  }
		my_iterator(Node* p) { This = p; }

		my_iterator& operator++ (int) { This = This->getNext(); return *this; }
		my_iterator& operator-- (int) { This = This->getPrev(); return *this; }
		int&  operator* () { return This->getValue(); }
		int&  operator-> () { return This->getValue(); }
		bool operator== (my_iterator &right) { return This == right.This; }
		bool operator!= (my_iterator &right) { return This != right.This; }
		int operator()() const { return This->getValue(); }
	};
	typedef my_iterator iterator;

	List()
	{
		Head = NULL;
		Tail = NULL;
		Length = 0;
	}
	List(const List &Other)
	{
		Length = Other.Length;
		Head = Other.Head;
		Tail = Other.Tail;
		This = Other.This;
	}
	~List() {}

	iterator Begin() const { return iterator(Head); }
	iterator End() const { return iterator(Tail); }

	int getLength() { return Length; }

	void addHead(int val)
	{
		Node* Tmp = new Node;
		Tmp->setPrev(0);
		Tmp->setValue(val);
		Tmp->setNext(Head);
		if (Head != 0)
			Head->setPrev(Tmp);
		if (Length == 0)
			Head = Tail = Tmp;
		else
			Head = Tmp;
		Length++;
	}

	void addTail(int val)
	{
		Node* Tmp = new Node;
		Tmp->setNext(0);
		Tmp->setValue(val);
		Tmp->setPrev(Tail);
		if (Tail != 0)
			Tail->setNext(Tmp);
		if (Length == 0)
			Head = Tail = Tmp;
		else
			Tail = Tmp;
		Length++;
	}

	void insert(T val, int pos)
	{
		if (pos == Length + 1)
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
		Node* Ins = Head;
		while (i < pos)
		{
			Ins = Ins->getNext();
			i++;
		}
		Node* PrevIns = Ins->getPrev();
		Node* Tmp = new Node;

		if (PrevIns != 0 && Length != 1)
			PrevIns->setNext(Tmp);

		Tmp->setNext(Ins);
		Tmp->setPrev(PrevIns);
		Tmp->setValue(val);
		Ins->setPrev(Tmp);
		Length++;
	}

	void print()
	{
		if (Length != 0)
		{
			iterator start = Begin();
			iterator end = End();
			cout << "\t";
			while (start != end)
			{
				cout << start() << endl << "\t";
				start++;
			}
			cout << end() << endl;
		}
	}

};