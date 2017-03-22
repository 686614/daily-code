#include <iostream>   
using namespace std;
#include <string>
int main() {
	string game[5];
	cout << "What's your favorite game?" << endl;
	for (int i = 0; i < 5; i++) {
		getline(cin, game[i]);
		if (game[i].compare("battlefield") == 0)
			cout << "somebody get this man an oscar" << endl;
		else if (game[i].compare("Overwatch") == 0)
			cout << "this is why you don't have any friends" << endl;
	}
	cout << "So, your favorite games are..." << endl;
	for (int i = 0; i < 5; i++) {
		cout << game[i] << endl;

	}
	system("Pause");
}