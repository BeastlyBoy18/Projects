#include <iostream>
using namespace std;
#include <ctime>

int main() {

	srand(time(NULL));

	int num = rand() % 5;
	char PI;
	char comp;
	if (num == 1) 
		comp = 'r';
	if (num == 2)
		comp = 'p';
	if (num == 3)
		comp = 's';
	if (num == 4)
		comp = 'k';
	if (num == 5)
		comp = 'l';
	cout << "Choose a sign r for rock s for scissors p for paper k for spock and l for lizard" << endl;
	cin >> PI;
	cout << comp << endl;
	if (PI == 's') {
		if (comp == 'p' || 'l')
			cout << "Player Wins" << endl;
		else if (comp = 's')
			cout << "tie!" << endl;
		else
			cout << "Player loses,Computer Wins" << endl;
	}

	if (PI == 'r') {
		if (comp == 's' || 'l')
			cout << "Player Wins" << endl;
		else if (comp = 'r')
			cout << "tie!" << endl;
		else
			cout << "Player loses,Computer Wins" << endl;
	}
	if (PI == 'p') {
		if (comp == 'k' || 'r')
			cout << "Player Wins" << endl;
		else if (comp = 'p')
			cout << "tie!" << endl;
		else
			cout << "Player loses,Computer Wins" << endl;
	}
	if (PI == 'k') {
		if (comp == 's' || 'r')
			cout << "Player Wins" << endl;
		else if (comp = 'k')
			cout << "tie!" << endl;
		else
			cout << "Player loses,Computer Wins" << endl;
	}
	if (PI == 'l') {
		if (comp == 'k' || 'p')
			cout << "Player Wins" << endl;
		else if (comp = 'l')
			cout << "tie!" << endl;
		else
			cout << "Player loses,Computer Wins" << endl;
	}
}
