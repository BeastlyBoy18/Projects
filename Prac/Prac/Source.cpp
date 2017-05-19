#include <iostream>
using namespace std;
#include <Windows.h>
#include <string>
#include<cstdlib>
#include<ctime>
void monster();
void Sicktoons();
string inv[4];
int health = 100;
int main() {
	srand(static_cast<unsigned int>(time(0)));//seed
	int rooms = 1;
	string input;
	getchar();//clears buffer (memory)
	cout << "Welcome to No End In Sight" << endl << endl << endl;

	cout << "Several months ago a mysterious disease rocked the world and wiped out" << endl << "2/3rds of the earths population." << endl
		<< "Those that survived would soon find themselves at odds with " << endl << "the parasitic effects of the disease," << endl
		<< "The parasite warped those who fell victim to it into mutated insectizoids bent on feasting on any living creatures" << endl << "they came across." << endl
		<< "You happened to be one of the sole survivors" << endl << "living in this apocalyptic wasteland." << endl;
	cout << "During a recon of a mall you are knocked unconcious" << endl << " and see a figure drag you away before" << endl << "you blackout." << endl << endl;

	system("pause");
	while (input.compare("quit") != 0 && health > 0) {

		cout << "|Type items to see inventory and current health|" << endl << endl;

		switch (rooms) {
			//----------------------------------------------
		case 1:
			cout << "You wake up in a prison cell on top of a uncomfortable cot." << endl << "There appears to be dried blood on the cot" << endl;
			cout << "The only things you can see are a small barred window to your north" << endl << "and a giant hole to the west of you" << endl;
			cout << "Where would you like to go?" << endl;
			getline(cin, input);
			if (input.compare("west") == 0)
				rooms = 2;
			if (input.compare("north") == 0)
				cout << "You peer out the small window into the darkness" << endl << "You can make out faint outlines of trees and the beady eyes of some kind of creature" << endl << endl;
			cout << "" << endl;

			if (!input.compare("items")) {
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				for (int i = 0; i < 4; i++) {
					cout << " Item " << i << " - " << inv[i];
					cout << endl;
					cout << "+++++++++++" << endl;
					cout << "Your health is " << health << endl;
					cout << "+++++++++++" << endl;
				} //IIC1
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			} //I C1
			break;

			//-----------------------------------------------
		case 2:
			cout << "You enter through the hole in the wall" << endl << "You notice the cot in this room is mangled beyond recognition and" << endl << "there is dried blood splattered everywhere" << endl;
			cout << "The door to this cell is pretty banged up," << endl << "if you (push) hard enough you might be able to slide through" << endl;
			getline(cin, input);
			if (input.compare("push") == 0)
				rooms = 3;
			else if (input.compare("east") == 0)
				rooms = 1;
			break;
			//--------------------------------------------------
		case 3:
			cout << "You slip through the cell door and head quickly to the guard station." << endl << " The door is cracked and the light is on." << endl << endl;
			system("pause");
			cout << "Peeking into the room you come across a grisly sight," << endl << "On the floor is the body of a dead person," << endl << "his chest is ripped open and something is pulsing." << endl;
			cout << " You may not want to linger here for much longer" << endl << "You can go south through the door" << endl;
			getline(cin, input);
			if (!input.compare("items")) {
				cout << "+++++++++++" << endl;
				cout << "Your health is " << health << endl;
				cout << "+++++++++++" << endl;

				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				for (int i = 0; i < 4; i++) {
					cout << " Item " << i << " - " << inv[i];
					cout << endl;

				}//Items c3
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			}// II C3
			if (input.compare("south") == 0)
				cout << "You briskly walk to the door and shut it close behind you, you wont be going back there." << endl;
			rooms = 4;

			break;
			//-------------------------------------------------------
		case 4:
			monster();
			cout << "You enter an area full of desk," << endl << " some of which have been flipped over and obviously searched for goods." << endl;
			if (input.compare("knife") == 0);
			cout << "You must be in some kind of police station, but why were you brought here?" << endl;
			system("pause");
			cout << "There seems to be a hallway that goes northeast and southeast" << endl;
			cout << "There is also a southern door way leading to the front of the station" << endl;
			getline(cin, input);

			if (!input.compare("items")) {
				cout << "+++++++++++" << endl;
				cout << "Your health is " << health << endl;
				cout << "+++++++++++" << endl;

				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				for (int i = 0; i < 4; i++) {
					cout << " Item " << i << " - " << inv[i];
					cout << endl;
				} // Items inner
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
			}// Items

			if (input.compare("northeast") == 0)
				rooms = 6;

			if (input.compare("southeast") == 0)
				rooms = 7;
			if (input.compare("south") == 0)
				rooms = 5;
			if (input.compare("north") == 0)
				cout << "As tempting as it is you're gonna pass" << endl << endl;
			break;
			//-------------------------------------------------------
		case 5:
			cout << "You see the front doors of the police station however their appears to be a pile of rubble blocking the doors." << endl;
			cout << " It appears you aren't getting out of here through this door your going to have" << endl << "to find another way out of the station" << endl;
			cout << "You can go back north." << endl;

			if (inv[0].compare("knife") != 0) {
				cout << "The front desk is lodged in the corner and a few of the drawers seem to be open" << endl;
				cout << "The Top, Middle, Side and Bottom drawer are all slightly open." << endl;
			}
			getline(cin, input);
			if (input.compare("Top") == 0) {

				cout << "There are a few old food wrappers" << endl;
			}
			if (input.compare("Middle") == 0) {
				cout << "You find a severed hand with a bite mark in the drawer" << endl;
			}
			if (input.compare("Side") == 0) {
				cout << " a small creature jumps out and bites your hand you don't feel very good as it scurries away" << endl;
			}
			if (input.compare("Bottom") == 0) {
				cout << "You find a survival knife in the bottom drawer" << endl;
				inv[0] = "knife";
			}//Knife get
			if (!input.compare("items")) {
				cout << "+++++++++++" << endl;
				cout << "Your health is " << health << endl;
				cout << "+++++++++++" << endl;

				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				for (int i = 0; i < 4; i++) {
					cout << " Item " << i << " - " << inv[i];
					cout << endl;
				}// Items
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

			}// Items
			if (input.compare("north") == 0)
				rooms = 4;
			break;
			//-------------------------------------------------------
		case 6:
			cout << "You walk into a hallway full of rooms in each rooms is a desk and chair" << endl;
			cout << "You hear moaning coming from some of the rooms, its best to avoid them." << endl;
			cout << "You can go south toward a breakroom," << endl << "southwest toward a closed door, west toward some lockers or southwest toward the closed door." << endl;
			monster();
			getline(cin, input);
			if (input.compare("south") == 0)
				rooms = 7;
			if (input.compare("southwest") == 0)
				rooms = 4;
			if (input.compare("west") == 0)
				rooms = 8;
			if (input.compare("southwest") == 0 && inv[2].compare("keys") == 0)
				rooms = 11;
			else
				cout << "Cant Go there." << endl;
			if (!input.compare("items")) {
				cout << "+++++++++++" << endl;
				cout << "Your health is " << health << endl;
				cout << "+++++++++++" << endl;

				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				for (int i = 0; i < 4; i++) {
					cout << " Item " << i << " - " << inv[i];
					cout << endl;
				}// items
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			}// items


			break;
			//-------------------------------------------------------
		case 7:
			cout << "You enter a break room and are surprised to see that it is in relatively good condition" << endl;
			cout << "There is a box of cookies on the table" << endl;
			cout << "You can see a fridge in the corner of the break room, there seems to be a paper with a magnet holding it up." << endl;
			cout << "You can go northwest to the desk area, north toward a bunch of rooms or east." << endl;
			getline(cin, input);
			if (input.compare("cookies") == 0 && health < 100)
				health += 50;
			if (input.compare("paper") == 0) {
				cout << "You look at the paper and find the numbers 2143 and  the word LC 12" << endl;
				system("pause");
			}
			if (input.compare("north") == 0)
				rooms = 6;
			if (input.compare("northwest") == 0)
				rooms = 4;
			if (input.compare("east") == 0 && inv[1].compare("keys"))
				rooms = 11;
			if (!input.compare("items")) {
				cout << "+++++++++++" << endl;
				cout << "Your health is " << health << endl;
				cout << "+++++++++++" << endl;

				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				for (int i = 0; i < 4; i++) {
					cout << " Item " << i << " - " << inv[i];
					cout << endl;
				} // items
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			}// items
			break;
			//-------------------------------------------------------
		case 8:
			cout << "There are rows of lockers on both sides of the room." << endl;
			cout << "Most of the lockers have been damaged severly and you won't be able to open them except a few" << endl;
			cout << "Looking closely locker 22 seems to be slightly open and what you can only assume is locker 5 has no door " << endl;
			if (inv[1].compare("keys") != 0) {
				cout << "locker 12 seems to be intact but the lock is still on" << endl;
			}
			else if (inv[1].compare("keys") == 0)
				cout << "You've already looked at locker 12." << endl;
			cout << "You can head back toward the interrogation rooms or west toward a large area" << endl;

			getline(cin, input);
			if (input.compare("locker 12") == 0) {
				cout << "You head for the only locker that still has its lock maybe you can put in a code";
				getline(cin, input);
				if (input.compare("2143") == 0) {
					cout << "The lock pops open and you can see keys hanging from on of the hooks" << endl;
					inv[1] = "keys";
					cout << "You take the keys now you just need a door." << endl;
				}
				else cout << "That isn't right" << endl;
				rooms = 8;
			}
			if (input.compare("locker 5") == 0)
				cout << "There is a lot of blood trailing away from the locker and claw marks on the door next to your foot." << endl;

			if (input.compare("locker 22") == 0)
				cout << "You open the locker and find a few pictures of someone's family, it makes you wonder if they made it out ok." << endl;

			if (input.compare("west") == 0)
				rooms = 9;
			if (input.compare("east") == 0) {
				cout << "You walk through the interrogation room and head toward the break room," << endl << "there's no telling if the body is fully dead or not and you aren't taking any chances" << endl;
				rooms = 7;
			}
			if (!input.compare("items")) {
				cout << "+++++++++++" << endl;
				cout << "Your health is " << health << endl;
				cout << "+++++++++++" << endl;

				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				for (int i = 0; i < 4; i++) {
					cout << " Item " << i << " - " << inv[i];
					cout << endl;
				}// items
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			} // items
			break;
			//-------------------------------------------------------
		case 9:
			cout << "You enter what appears to be a firing range." << endl;
			cout << "On the opposite side of the room there are targets hanging from the last session";
			cout << "near the far right end of the range you can see a (door), this could be you chance to escape!" << endl;
			getline(cin, input);
			if (input.compare("door") == 0)
				cout << "You climb over one of the firing stalls and head toward the door" << endl;
			cout << "It wouldn't be smart to turn your back in a place where people fire guns. You reach the door and find it needs a code to open." << endl;
			getline(cin, input);
			if (input.compare("2143") == 0) {
				cout << "The code was accepted you're free!" << endl;
				rooms = 12;
			}
			else
				cout << "That isn't right." << endl;
			if (!input.compare("items")) {
				cout << "+++++++++++" << endl;
				cout << "Your health is " << health << endl;
				cout << "+++++++++++" << endl;

				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				for (int i = 0; i < 4; i++) {
					cout << " Item " << i << " - " << inv[i];
					cout << endl;
				}// items
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				/// items
			}
			break;
			//-------------------------------------------------------
		case 10:
			cout << "The keys open the door" << endl;
			cout << "You step into a small office on the desk is a plaque that says SHERRIF" << endl;
			cout << "There doesn't seem to be anything out of the ordinary about the room just some pictures and awards on the walls" << endl;
			cout << "One of the awards on the (wall) seems to be moving slightly" << endl;
			getline(cin, input);
			if (input.compare("wall") == 0)
				cout << "You lift the award from the wall and notice a small hole." << endl;
			cout << "You reach your hand into the wall and feel some kind of lever and pull it up." << endl;
			cout << "You hear something click and see a small hatch open under the desk. Will you climb down?" << endl;
			getline(cin, input);
			if (input.compare("yes") == 0)
				rooms = 11;

			if (!input.compare("items")) {
				cout << "+++++++++++" << endl;
				cout << "Your health is " << health << endl;
				cout << "+++++++++++" << endl;

				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				for (int i = 0; i < 4; i++) {
					cout << " Item " << i << " - " << inv[i];
					cout << endl;
				} // items
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			} // items
			break;
			//-------------------------------------------------------
		case 11:
			cout << "You climb down the ladder and find yourself in a small hallway." << endl;
			system("pause");
			cout << "You walk to the end of the hallway and find steps leading up to a door." << endl;
			system("pause");
			cout << "You push the door open and find you are outside" << endl;
			system("pause");
			cout << "CONGRADUATIOnS YOU HAVE ESCAPED" << endl;
			system("Color 27");
			break;
		case 12:
			system("Color 47");
			cout << "You enter the forest thinking you have escaped when in fact you have written your death sentence" << endl << "You hear a screech behind you before everything fades to black." << endl;
			system("pause");
			(health = 0);
			break;
		}
		if (health == 0)
			cout << "You have died" << endl;
	}


}
/*void monster() {
	//-------------------------------------------------------
	int num = rand() % 100 + 1;//generates random #
							   //-------------------------------------------------------
	if (num < 40 && (inv[0].compare("knife") != 0)) {
		cout << "You've come across a Ravenous it jumps toward you!" << endl;
		health -= 20;
		PlaySound(TEXT("Mummy.wav"), NULL, SND_FILENAME);

	}
	else if (num < 40 && (inv[0].compare("knife") == 0)) {
		cout << "You come across a Ravenous, you slash at it with your knife running it off." << endl;

	}
	//---------------------------------------------------------------------------------------------
	if (num > 40 && num < 50 && (inv[0].compare("knife") != 0)) {
		cout << "You encounter a Terrosect it overpowers you and bites your shoulder" << endl;
		health -= 40;

	}
	else if (num > 40 && num < 50 && (inv[0].compare("knife") == 0)) {
		cout << "You encounter a Terrosect you slash at it when it charges and you exchange wounds before escaping" << endl;
		health -= 20;
		PlaySound(TEXT("horror005.wav"), NULL, SND_FILENAME);

	}
	//---------------------------------------------------------------------------------------------
	else {
		cout << "There doesn't seem to be any immediate danger" << endl;
	}
}
void sicktoons() {
	int num2 = rand() % 100 + 1;

	if (num2 > 1)
		PlaySound(TEXT("horror005.wav"), NULL, SND_FILENAME);
	system("pause");


}
*/