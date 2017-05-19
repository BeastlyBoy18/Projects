#include<iostream>
void Badguy();
using namespace std;
int main() {
	while (100==100) {
		Badguy();
		system("pause");

	}
	
}

void Badguy() {
	int num = rand() % 100 + 1;
	if (num <= 50) {
		cout << "Goomba!" << endl;
	}
	else if (num > 50 && num < 80) {
		cout << "Koopa!" << endl;
	}
	else  {
		cout << "Shy Guy" << endl;
	}
}