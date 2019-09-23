#pragma once
#ifndef FIRMA_H
#define FIRMA_H

#include <iostream>
#include "Node.h"

using namespace std;

class Firma : public Node /* die Klasse Firma wird hier deklariert und ist mit Node verlinkt*/
{
public:
	Firma(string name,string dienstleistung); 
	//~Firma();
  /* Access the values we created*/
	string getName()const { return m_name; }
	string getDienstleistung()const { return m_dienstleistung; }
	double getUmsatz()const { return m_umsatz; }
	void setUmsatz(double umsatz); /* Der Umsatz kann sich verändern deswegen auf set und als Typ void*/

private:
	string m_name;
	string m_dienstleistung;
	double m_umsatz;
};
#endif // !FIRMA_H
