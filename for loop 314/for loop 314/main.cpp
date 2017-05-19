#include <iostream>
using namespace std;
int main() {
	int input;
	int ugh = 0;
	for (int i = 0; i < 10; i++) {
		cin >> input;
		if (input > ugh) {
			ugh = input;
		
		}
	}
	cout << ugh;
}