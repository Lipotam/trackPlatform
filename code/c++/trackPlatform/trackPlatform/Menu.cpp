#include "Menu.h"



Menu::Menu()
{
}

void Menu::show() {
	cout << "Menu:" << endl;
	cout << "1 - Move forward" << endl;
	cout << "2 - Turn left" << endl;
	cout << "3 - Turn right" << endl;
	cout << "4 - Move back" << endl;
	cout << "0 - Exit" << endl;
}

int Menu::choose() {
	int chooseMenuItem;
	cin >> chooseMenuItem;
	return chooseMenuItem;
}


Menu::~Menu()
{
}
