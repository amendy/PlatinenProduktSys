#include <iostream>
#include <list>
#include <string>
#include <ctype.h>
#include "GUI.h"

using namespace std;
 /*  Hier werden Klassen von der GUI deklarieert werden, um zu zeigen was sie alles enthalten dürfen
   Klassen deklarieren*/

/* Standard für eine Klasse ist void Name::Name2() {} */
void GUI::userMenu() {
	int count = 1;
	cout << "***********************" << endl;

	for (auto i :m_menu)
	{
		cout << count << "." << i << endl;
		count++;
	}
	cout << "***********************" << endl;
}
double GUI::double_input()
{
	cout << "> ";
	if (cin >> double_eingabe) { /*wartet hier auf eine Eingabe cin >>*/
		cin.clear();
		cin.ignore(1000, '\n');
		return double_eingabe;
	}
	else
	{
		cout << "Fehler Falsche Eingabe" << endl;
		cin.clear();
		std::cin.ignore(1000, '\n');
		return -1;
	}
}
string GUI::string_input()
{
	cout << "> ";
	if (cin >> string_eingabe) {
		return string_eingabe;
	}
	else
	{
		cout << "Fehler Falsche Eingabe" << endl;
		return "error";
	}
}

int GUI::int_input()
{
	cout << "> ";
	if (cin >> int_eingabe) {
		cin.clear();
		cin.ignore(1000, '\n');
		return int_eingabe;
	}
	else
	{
		cout << "Fehler Falsche Eingabe" << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		return -1;
	}
}
void GUI::addMenu(string menu) {

	m_menu.push_back(menu);
	//cout << menu << " hinzugefuegt." << endl;
}
