#include<algorithm>
#include<iostream>
#include<string>
#include<numeric>

using namespace std;

//-----------------------------------------------------------

bool Palindrom(string s1, string s2)
{
	string rev1, rev2;
	rev1 = s1;
	reverse(rev1.begin(), rev1.end());
	rev2 = s2;
	reverse(rev2.begin(), rev2.end());

	if (s1 == rev1 && s2 == rev2)
		return true;
	return false;
}

void PrintSubstrings(string s1, string s2)
{
	cout << "All common substrings:" << endl;

	char *buffer = new char[s1.size() + 1];
	int length = s1.size();
	int found;

	for (int i = 0; i < length; i++) // перебор всех возможных подстрок
	{
		for (int k = length - i; k > 0; k--)
		{
			s1.copy(buffer, k, i);
			buffer[k] = '\0';
			found = s2.find(buffer);
			if (found != string::npos)
				cout << "\t" << buffer << endl;
		}
	}
}

void Task7()
/* Написать функцию, определяющую, что две введенные строки являются палиндромами.
   Если строки не являются палиндромами, определить общие подстроки. */
{
	string s1, s2;
	cout << "Input string 1: ";
	cin >> s1;
	cout << "Input string 2: ";
	cin >> s2;

	if (Palindrom(s1, s2))
		cout << "\"" << s1 << "\" and \"" << s2 << "\" are palindroms";
	else
		PrintSubstrings(s1, s2);
}

//-----------------------------------------------------------

void Task6()
/* Ввести произвольную строку и символ с клавиатуры.
   Вывести число раз, которое заданный символ встречается в строке.
   Определить первую и последнюю позицию, когда символ встречается в строке. */
{
	string s;
	cout << "Input string: ";
	cin >> s;
	string sym;
	cout << "Input symbol: ";
	cin >> sym;

	int num = 0;
	for (int i = 0; i < s.length(); i++)
		if (s[i] == sym[0])
			if (s.substr(i, 1) == sym)
				num++;
	cout << "Number of occurances: " << num << endl;
	cout << "First occurance pos: " << s.find(sym) << endl;
	reverse(s.begin(), s.end());
	cout << "Last occurance pos:  " << s.length() - s.find(sym) - 1 << endl;
}

//-----------------------------------------------------------

void Task14()
/* На одометре (прибор для измерения пробега автомобиля) число 15951.
   Через 2 часа езды он показывает другое число палиндром.
   Какова средняя скорость? Написать программу, позволяющую задать новое значение на одометре
   (новое число должно быть больше начального (15951) и быть палиндромом) и вычисляющую среднюю скорость. */
{
	int n;
	cout << "Input number: ";
	cin >> n;

	string s, rev_s;
	s = to_string(n);
	rev_s = s;
	reverse(rev_s.begin(), rev_s.end());

	if (n <= 15951 || s != rev_s)
		cout << "Incorrect";
	else
	{
		double speed = (n - 15951) / 2.0;
		cout << "Average speed: " << speed;
	}
}

//-----------------------------------------------------------

int main()
{
	cout << endl << endl << "---------- TASK 7 ----------" << endl << endl;
	Task7();
	cout << endl << endl << "---------- TASK 6 ----------" << endl << endl;
	Task6();
	cout << endl << endl << "---------- TASK 14 ----------" << endl << endl;
	Task14();

	return 0;
}