#include "list.h"
#include <list>
using namespace std;

//int main() {
//	list<int> lt;
//	lt.push_back(1);
//	lt.push_back(2);
//	lt.push_back(3);
//
//	for (auto x : lt) {
//		cout << x << " ";
//	}
//	cout << endl;
//
//	list<int>::iterator it = lt.begin();
//	while (it != lt.end()) {
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//	return 0;
//}

//int main() {
//	/*new_list::Test_1();*/
//	/*new_list::Test_2();*/
//	/*new_list::Test_3();*/
//	new_list::Test_4();
//	return 0;
//}

int main() {
	new_list::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);

	new_list::list<int>::reverse_iterator it = lt.rbegin();
	while (it != lt.rend()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
	return 0;
}
