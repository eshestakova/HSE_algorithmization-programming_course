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
	private:
		T value;
		Node *next, *prev;

	public:
		Node() { next = nullptr; prev = nullptr; }
		Node(const Node &orig) : value(orig.value), next(orig.next), prev(orig.prev) {}
		~Node() { delete this; }

		Node* getnext() { return next; }
		Node* getprev() { return prev; }
		T getvalue() { return value; }

		void setprev(Node* pr) { prev = pr; }
		void setnext(Node* nx) { next = nx; }
		void setvalue(T v) { value = v; }
	};

	int len;
	Node *head, *tail, *ptr;

public:
	class iter : public iterator<bidirectional_iterator_tag, T>
	{
	private:
		Node *ptr;
	public:
		iter() : ptr(0) {}
		iter(Node* p) : ptr(p) {}

		iter& operator++ (int) { ptr = ptr->getnext();	return *this; }
		iter& operator-- (int) { ptr = ptr->getprev();	return *this; }
		T&  operator* () { return ptr->getvalue(); }
		T&  operator-> () { return ptr->getvalue(); }
		bool operator== (iter &right) { return ptr == right.ptr; }
		bool operator!= (iter &right) { return ptr != right.ptr; }

		T operator()() const { return ptr->getvalue(); }
	};
	typedef iter iterator;

	List() { head = tail = NULL; len = 0; }
	List(const List &orig) : len(orig.len), head(orig.head), tail(orig.tail), ptr(orig.tail) {}
	~List() {}

	iterator begin() const { return iterator(head); }
	iterator end() const { return iterator(tail); }

	int getLen() { return len; }

	void addHead(int val)
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

	void addTail(int val)
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

	void insert(T val, int pos)
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

	void print()
	{
		if (len != 0)
		{
			iterator its = begin();
			iterator ite = end();

			while (its != ite)
			{
				cout << its() << " ";
				its++;
			}
			cout << ite() << endl;
		}
	}

};
