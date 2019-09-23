#include <iostream>
#include <list>
#include <string>
#include "Node.h"
#include "Firma.h"

using namespace std;

Firma::Firma(string name, string dienstleistung):Node(name) { /* deklariere hier alles */

	m_name = name;
	m_dienstleistung = dienstleistung;

}
void Firma::setUmsatz(double umsatz){
	
	m_umsatz = m_umsatz + umsatz;
}
