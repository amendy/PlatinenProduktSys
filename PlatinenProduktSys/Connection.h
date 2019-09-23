#pragma once
#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <iomanip>
#include <string>
#include "Edge.h"
#include "Firma.h"

/* deklariere die Klasse Connection, die greift auf Edge zu*/
class Connection : public Edge
{
public:

	static int Platinenanzahl; /* statische Variable Platinenzahl, this variable will be share by every type of class*/
 
	Connection(Firma* Src, Firma* Dst, int ab_ein, int ab_hundert, int ab_tausend);
	
//~Connection();
/* Access to values we created with get and set the values which are supposed to be changed*/

	int getEin()const { return m_ab_ein; }
	int getHundert()const { return m_ab_hundert; }
	int getTausend()const { return m_ab_tausend; }
	Firma* getSrc()const { return m_Src; }
	Firma* getDst()const { return m_Dst; }
	double getWeight();

private:
	string m_name;
	int m_ab_ein, m_ab_hundert, m_ab_tausend;
	Firma* m_Src;
	Firma* m_Dst;
};
#endif
