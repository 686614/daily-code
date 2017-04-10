#include <iostream>
using namespace std;

int main() {

	int temp;
	char input;

	cout << "what is the temperature in your area?" << endl;
	cin >> temp;

	cout << "enter unit of temperature you want. (f, c, k)" << endl;
	cin >> input;

	if (input == 'f') {
		cout << "In C, this is " << (temp - 32)*.5556 << endl;
		cout << "In K, this is " << .5556 * (temp - 32) + 273 << endl;
		cout << "im colded" << endl;
	}
	else if (input == 'c') {
		cout << "In F, this is " << 1.8 * (temp)+32 << endl;
		cout << "In K, this is " << temp + 273 << endl;
		cout << "i am the warm" << endl;
	}
	else if (input == 'k') {
		cout << "In F, this is " << 1.8 * (temp - 273) + 32 << endl;
		cout << "In C, this is " << temp + 273 << endl;
		cout << "i am the medium" << endl;
	}

	if (temp < 212)
		cout << "pant, pant, pant" << endl;
	if (temp > 32)
		cout << "brrrrr" << endl;
	else
		cout << "you are a fugitive from the law of averages" << endl;

}