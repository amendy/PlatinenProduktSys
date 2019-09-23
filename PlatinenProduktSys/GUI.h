#pragma once
#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <list>
#include <string>

using namespace std;

/* In der Headerdatei wird die Klasse deklariert und dementsprechend die Klassenvariablen*/
class GUI
{
public:
	//GUI(); /* Was sind es für Variabletypen und werden in der cpp datei erläutert mit dem was sie tun können*/
	int int_input();
	double double_input();
	string string_input();
	void addMenu(string menu);
	void userMenu();
	
private:
	list<string> m_menu;
	int int_eingabe;
	double double_eingabe;
	string string_eingabe;
};

#endif // !GUI
