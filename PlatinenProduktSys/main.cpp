#include <iostream>
#include "Graph.h"
#include <iomanip>
#include "GUI.h"
#include "Firma.h"
#include "Connection.h"

using namespace std;

vector<Firma*>firmen;
vector<Connection*>connection;
vector<string>abteilung;

void printUmsatz();

int main()
{

	Graph g;
	GUI	gui;

	Firma *SysEng = new Firma("SysEng", "HW/SW Entwicklung");
	Firma *Endos = new Firma("Endos", "LP-Herstellung");
	Firma *LightOff = new Firma("LightOff", "LP-Herstellung");
	Firma *LPBes = new Firma("LPBes", "Bestueckung");
	Firma *BP = new Firma("BP", "Bestueckung");
	Firma *HWTesting = new Firma("HWTesting", "HW-Test");

	//Lokal speichern
	firmen.push_back(SysEng);
	firmen.push_back(Endos);
	firmen.push_back(LightOff);
	firmen.push_back(LPBes);
	firmen.push_back(BP);
	firmen.push_back(HWTesting);

	//Global speichern
	g.addNode(SysEng);
	g.addNode(Endos);
	g.addNode(LightOff);
	g.addNode(LPBes);
	g.addNode(BP);
	g.addNode(HWTesting);

	Connection* SysEng_Endos = new Connection(SysEng, Endos, 200, 80, 20);
	Connection* SysEng_LightOff = new Connection(SysEng, LightOff, 160, 120, 70);
	Connection* Endos_LPBes = new Connection(Endos, LPBes, 180, 100, 30);
	Connection* LightOff_LPBes = new Connection(LightOff, LPBes, 160, 80, 20);
	Connection* LightOff_BP = new Connection(LightOff, BP, 170, 120, 20);
	Connection* LPBes_HWTest = new Connection(LPBes, HWTesting, 300, 260, 210);
	Connection* BP_HWTest = new Connection(BP, HWTesting, 290, 280, 200);

	connection.push_back(SysEng_Endos);
	connection.push_back(SysEng_LightOff);
	connection.push_back(Endos_LPBes);
	connection.push_back(LightOff_LPBes);
	connection.push_back(LightOff_BP);
	connection.push_back(LPBes_HWTest);
	connection.push_back(BP_HWTest);

	g.addEdge(SysEng_Endos);
	g.addEdge(SysEng_LightOff);
	g.addEdge(Endos_LPBes);
	g.addEdge(LightOff_LPBes);
	g.addEdge(LightOff_LPBes);
	g.addEdge(LightOff_BP);
	g.addEdge(LPBes_HWTest);
	g.addEdge(BP_HWTest);

	gui.addMenu("Neuer Auftrag");
	gui.addMenu("Ausgabe Umsatzliste");
	gui.addMenu("Beenden");


	abteilung.push_back("LP-Herstellung");
	abteilung.push_back("Bestueckung");
	abteilung.push_back("HW-Test");
	cout << "SysEng GmbH Klausur" << endl << endl;

	while (1) {

		gui.userMenu();

		//gui.int_input();
		switch (gui.int_input())
		{
		case 1:
		{
			cout << "Neuer Auftrag." << endl;
			cout << "Anzahl Platinen: " << endl;
			int anzahlPlatinen = gui.int_input();
			if (anzahlPlatinen < 0) { cout << "Error" << endl; }
			else
			{
				deque<Edge*>path;
				double gesamtkosten = 0;
				Connection::Platinenanzahl = anzahlPlatinen;
				g.findShortestPathDijkstra(path, *SysEng, *HWTesting);
				cout << "Strecke: " << endl;

				for (auto i : path) {

					for (auto j : firmen)
					{
						if (j->getID() == i->getDstNode().getID()) {

							j->setUmsatz((anzahlPlatinen*i->getWeight()));
							gesamtkosten = gesamtkosten + (anzahlPlatinen*i->getWeight());
							cout << setw(18) << i->toString() << " " << setw(6) << (anzahlPlatinen*i->getWeight()) << " Euro" << endl;
						}

					}
				}
				cout << endl << "Gesamtkosten: " << gesamtkosten << " Euro" << endl << endl << endl;
			}
			break;
		}
		case 2:
			printUmsatz();
			break;
		case 3:
			exit(0);
			break;
		default:
			cout << "Falsche Eingabe" << endl;
			break;
		}
	}
	return 0;
}

void printUmsatz() {
	int count = 1;
	cout << endl << "Umsatz:" << endl;
	for (auto i : firmen) {
		cout << count << ". " << setw(9) << i->getName() << ": " << setw(4) << i->getUmsatz() << " Euro" << endl;
		count++;
	}
	cout << endl;
}