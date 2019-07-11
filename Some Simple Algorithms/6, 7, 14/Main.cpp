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

	for (int i = 0; i < length; i++) // ïåðåáîð âñåõ âîçìîæíûõ ïîäñòðîê
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
/* Íàïèñàòü ôóíêöèþ, îïðåäåëÿþùóþ, ÷òî äâå ââåäåííûå ñòðîêè ÿâëÿþòñÿ ïàëèíäðîìàìè.
   Åñëè ñòðîêè íå ÿâëÿþòñÿ ïàëèíäðîìàìè, îïðåäåëèòü îáùèå ïîäñòðîêè. */
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
/* Ââåñòè ïðîèçâîëüíóþ ñòðîêó è ñèìâîë ñ êëàâèàòóðû.
   Âûâåñòè ÷èñëî ðàç, êîòîðîå çàäàííûé ñèìâîë âñòðå÷àåòñÿ â ñòðîêå.
   Îïðåäåëèòü ïåðâóþ è ïîñëåäíþþ ïîçèöèþ, êîãäà ñèìâîë âñòðå÷àåòñÿ â ñòðîêå. */
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
/* Íà îäîìåòðå (ïðèáîð äëÿ èçìåðåíèÿ ïðîáåãà àâòîìîáèëÿ) ÷èñëî 15951.
   ×åðåç 2 ÷àñà åçäû îí ïîêàçûâàåò äðóãîå ÷èñëî ïàëèíäðîì.
   Êàêîâà ñðåäíÿÿ ñêîðîñòü? Íàïèñàòü ïðîãðàììó, ïîçâîëÿþùóþ çàäàòü íîâîå çíà÷åíèå íà îäîìåòðå
   (íîâîå ÷èñëî äîëæíî áûòü áîëüøå íà÷àëüíîãî (15951) è áûòü ïàëèíäðîìîì) è âû÷èñëÿþùóþ ñðåäíþþ ñêîðîñòü. */
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
