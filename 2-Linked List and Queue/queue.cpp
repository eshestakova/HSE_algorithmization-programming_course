#include <vector> 
#include <iterator> 
#include <iostream> 


using namespace std;

template <class T>
class queue
{
public:
	class my_iterator : public iterator<forward_iterator_tag, T>
	{
	private:
		int ElemNumber;
	public:
		my_iterator()
		{
			ElemNumber = 0;
		}
		my_iterator(my_iterator &&Other)
		{
			this->ElemNumber = Other.ElemNumber;
		}
		my_iterator(my_iterator &Other)
		{
			this->ElemNumber = Other.ElemNumber;
		}
		my_iterator(int ElemNumber)
		{
			this->ElemNumber = ElemNumber;
		}

		my_iterator& operator=(my_iterator &Other) { this->ElemNumber = Other.ElemNumber; return *this; }
		my_iterator& operator=(my_iterator &&Other)	{ this->ElemNumber = Other.ElemNumber; return *this; }
		bool operator==(my_iterator &Other) const { return this->ElemNumber == Other.ElemNumber; }
		bool operator!=(my_iterator &Other) const { return this->ElemNumber != Other.ElemNumber; }
		my_iterator& operator++(int) { ElemNumber++; return *this; }
		int operator()() const { return ElemNumber; }
		~my_iterator() {}
	};
	typedef my_iterator iterator;

	iterator begin() { return iterator(0); }
	iterator end() { return iterator(ElementsNum - 1); }

	queue(vector<T> &Elements)
	{
		this->Elements = Elements;
		ElementsNum = this->Elements.size();
	}
	queue(queue<T> &Other)
	{
		this->Elements = Other.Elements;
		this->ElementsNum = Other.ElementsNum;
	}

	void add_elem(T Value)
	{
		Elements.push_back(Value);
		ElementsNum++;
	}
	void delete_elem()
	{
		Elements.erase(Elements.begin());
		ElementsNum--;
	}
	int size() const { return ElementsNum; }
	T get(iterator &cur_iter) const	{ return Elements.at(cur_iter()); }
	~queue() {}

private:
	vector<T> Elements;
	int ElementsNum;

};