#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string reverseNumbers(string s) {
	int start = 0, end = 0;
	string sub, res;
	stringstream stream;
	stream << s;
	while (stream >> sub) {
		//------
		sub = string (s.substr(start, end - start)); // for new word
		if (atoi(sub.c_str()) != 0) reverse(sub.begin(), sub.end()); // reverse if number
		res.append(sub); 
		res.append(" ");
		start = end+1;
	}

	return res;
}

string incrementSingles(string s) {
	int start = 0, end = 0, n;
	string sub, res;
	stringstream stream;
	stream << s;
	while (stream >> sub) {
		//sub = string(s.substr(start, end - start)); // for new word

		int freq = 0;
		for (int i = 0; (i = s.find(sub, i)) != string::npos; i++) freq++; // find freqency

		n = atoi(sub.c_str());
		if (n != 0 && freq == 1) sub = to_string(n+1); // if single increment

		res.append(sub);
		res.append(" ");
		start = end + 1;
	}

	return res;
}


int main() {

	std::cout << "Reverse Numbers:\n" << "12 abc 3 defg 456\n" << reverseNumbers("12 abc 3 defg 456") << endl << endl;
	std::cout << "Increment Singles:\n" << "111 abc 2 de 3 f gh 2 ij\n" << incrementSingles("111 abc 2 de 3 f gh 2 ij");

	return 0;
}
