#include <iostream>
#include <array>
using namespace std;

int main() {

	int wrong = 0;
	char input;
	char letter[7] = { '_','_','_','_','_','_','_' };
	char answer[7] = { 'f','r','i','e','n','d','s' };
while (7>wrong){
		cout << "Riddle me this: the less you have of me, the more valuable i become. what am i?" << endl;
	    
		for (int i = 0; i < 10; i++) {
			cout << letter[i] << "";
		}
		cout << "take a guess what is yo letta" << endl;
		//FRIENDS
		cin >> input;
		for (int i = 0; i < 10; i++) {
			if (input == answer[i]) {
				letter[i] = input;

			}
		}
		
	}

}