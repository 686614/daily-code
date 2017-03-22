#include <iostream>
using namespace std;
int main() {

	int big = 0;
	int input;
	for (int i = 0; i < 3; i++) {
		cout << "enter a your number" << endl;
		cin >> input;
		if (input > big)
			big = input;

	}
	cout << "the biggest number is" << big << endl;

}