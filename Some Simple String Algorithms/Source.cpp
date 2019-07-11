#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>

using namespace std;

void parseString(const string &src, vector<set<string>> &dst) {
	int start = 0, end = 0;
	string sub;
	stringstream stream;
	stream << src;
	while (stream >> sub) { // new word
		int indicator = 0;
		for (auto it = dst.begin(); it != dst.end(); it++) { // looking for good set
			auto s = *it;
			auto elem = *(s.begin());
			if (elem.back() == sub.back()) { // if found good set - insert
				it->insert(sub); //!!!!
				indicator = 1;
				break;
			}
		}
		if (indicator == 0) { // if no existing good set
			auto pos = dst.end();
			for (auto it = dst.begin(); it != dst.end(); it++) {
				auto s = *it;
				auto elem = *(s.begin());
				if (elem.back() > sub.back()) { // find position for inserting
					set<string>s1(s);
					pos = find(dst.begin(), dst.end(), s1);
					break;
				}
			}
			//insert
			set<string>s2;
			s2.insert(sub);
			dst.insert(pos, s2);
		}
		start = end + 1;
	}
}

int main() {
	vector<set<string>> dst;
	string st = "this is the malt that lay in the house that jack built";
	cout << st << endl << endl;

	parseString(st, dst);

	for (set<string> &mySet : dst) {
		for (string s : mySet) {
			cout << s << " ";
		}
		cout << "\n";
	}

	return 0;
}