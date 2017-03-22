#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;

int main() {

	srand(time(NULL));
	int sum = 0;
	int num;
	int max = 0;

	for (int i = 0; i < 100; i++) {

		num = rand() % 1000 + 1;
		cout << num << endl;

		sum = sum + num;

		if (num > max) {
			max = num;

		}

	}
	cout << "the max is " << max << endl;
	cout << "the average is " << sum / 100 << endl;
}