#include<algorithm>
#include<iostream>
#include<vector>
#include<ctime>
#include<string>
#include<numeric>

using namespace std;

int sum(int n)
{
	int i = 0;
	vector<int> v(n++);
	generate(v.begin(), v.end(), [&i]()->int {return i * i++; });
	int res = accumulate(v.begin(), v.end(), 0);
	return res;
}

void task10()
{
	cout << "Input n: ";
	int n;
	cin >> n;
	cout << "Result: " << sum(n);
}

void task12()
{
	srand(time(NULL));
	vector<int> mas(20);
	generate(mas.begin(), mas.end(), []()->int {return 1 + rand() % 100; });
	cout << "Old vector:\t" << endl;
	for_each(mas.begin(), mas.end(), [](const int& x) {cout << x << " "; });
	cout << endl << "New vector:\t" << endl;
	mas.erase(remove_if(mas.begin(), mas.end(), [](const int& x) {return x % 6 != 0; }), mas.end());
	for_each(mas.begin(), mas.end(), [](const int& x) {cout << x << " "; });
}

void task14()
{
	string a, b;
	int cur;
	cout << "Input num: ";
	cin >> cur;
	a = to_string(cur);
	b = a;
	reverse(b.begin(), b.end());
	if (cur <= 15951 || a != b)
		cout << "Incorrect input!";
	else {
		double speed = (cur - 15951) / 2.0;
		cout << "Mean speed = " << speed << " km/h";
	}
}

int main()
{
	cout << "---------- TASK 10 ----------" << endl << endl;
	task10();
	cout << endl << endl << "---------- TASK 12 ----------" << endl << endl;
	task12();
	cout << endl << endl << "---------- TASK 14 ----------" << endl << endl;
	task14();

	return 0;
}