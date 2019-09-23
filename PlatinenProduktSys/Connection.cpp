#include <iostream>
#include <string>
#include "Edge.h"
#include "Connection.h"

using namespace std;

int Connection::Platinenanzahl = 0; /* Platinenanzahl was a static variable at connection.h so it can be used again*/

/* Set connection with a constructor with everything which is there*/ 

Connection::Connection(Firma* Src, Firma* Dst, int ab_ein, int ab_hundert, int ab_tausend):Edge(*Src,*Dst) {

	m_Src = Src;
	m_Dst = Dst;
	m_ab_ein = ab_ein;
	m_ab_hundert = ab_hundert;
	m_ab_tausend= ab_tausend;
	m_name = Src->getName() + " -> " + Dst->getName();
}
double Connection::getWeight() {

	if (Platinenanzahl < 100) {
		return m_ab_ein;
	}
	else if (Platinenanzahl > 100 && Platinenanzahl < 1000) {
		return m_ab_hundert;
	}
	else
	{
		return m_ab_tausend;
	}
}
