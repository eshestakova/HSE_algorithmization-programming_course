#include <iostream>
#include <exception>

using namespace std;

class ex : public exception
{
	virtual const char* what() const throw() { return "Exception happened"; }
} ex;

class Int
{
	int i_;

public:
	Int(int i) noexcept	: i_(i)	{}
	int get() const noexcept { return i_; }

	void Exceptor()
	{
		try
		{
			throw ex;
		}
		catch (exception& e)
		{	
			cout << "Exception N" << i_ << endl;
			throw;
		}
	}
};

void terminator() {	cout << "I'll be back" << endl; }

int main()
{
	set_terminate(terminator);

	Int a(77);
	try
	{
		a.Exceptor();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
		
	return 0;
}