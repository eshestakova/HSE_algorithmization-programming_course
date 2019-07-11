#include <vector> 
#include <iterator> 
#include <iostream>
#include <stack>

using namespace std;

template <class T>
class Node
{
private:
	T value;
	Node *parent, *left, *right;
public:
	Node() { value = 0; parent = nullptr; left = nullptr; right = nullptr; }
	Node(T v, Node* p, Node* l, Node* r) { value = v; parent = p; left = l; right = r; }
	Node(const Node &orig) : value(orig.value), parent(orig.parent), left(orig.left), right(orig.right) {}
	~Node() { delete this; }

	Node* getparent() { return parent; }
	Node* getleft() { return left; }
	Node* getright() { return right; }
	T getvalue() { return value; }

	void setparent(Node* p) { parent = p; }
	void setleft(Node* l) { left = l; }
	void setright(Node* r) { right = r; }
	void setvalue(T v) { value = v; }

	class iter : public iterator<forward_iterator_tag, T>
	{
	private:
		Node *ptr;
		stack<Node*> stack;
	public:
		iter() : ptr(0) {}
		iter(Node* p) : ptr(p)
		{
			Node* cur = ptr;
			while (cur)
			{
				stack.push(cur);
				cur = cur->left;
			}
			if (!stack.empty())
			{
				ptr = stack.top();
				stack.pop();
			}
		}

		int&  operator* () { return ptr->getvalue(); }
		int&  operator-> () { return ptr->getvalue(); }
		bool operator== (iter &right) { return ptr == right.ptr; }
		bool operator!= (iter &right) { return ptr != right.ptr; }

		T operator()() const { if (ptr) return ptr->getvalue(); }

		iter& operator++(int)
		{
			if (!stack.empty())
			{
				Node *cur = stack.top();
				ptr = cur;
				stack.pop();
				if (cur->right)
				{
					cur = cur->right;
					while (cur)
					{
						stack.push(cur);
						cur = cur->left;
					}
				}
				return *this;
			}
			ptr = nullptr;
			return *this;
		}
	};
	typedef iter iterator;

	iterator begin() { return iterator(this); }
	iterator end() { return iterator(nullptr); }

	void print()
	{
		cout << endl << "Binary Tree:" << endl;
		iterator its = begin();
		iterator ite = end();
		while (its != ite)
		{
			cout << its() << " ";
			its++;
		}
	}
};

template <class T>
Node<T>* addnode(int val, Node<T> *tree) {
	if (!tree)
		tree = new Node<T>(val, nullptr, nullptr, nullptr);

	else
	{
		if (val < tree->getvalue())
		{
			tree->setleft(addnode(val, tree->getleft()));
			tree->getleft()->setparent(tree);
		}
		if (val > tree->getvalue())
		{
			tree->setright(addnode(val, tree->getright()));
			tree->getright()->setparent(tree);
		}
	}
	return(tree);
}


