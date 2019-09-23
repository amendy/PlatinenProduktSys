#include "Graph.h"
#include <list>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iostream>
#include <deque>
#include <map>

//---------------------------------------------------------------------------------------------------------------------

Node* Graph::findNode(const std::string& id)
{
	// - soll einen Node mit der gegebenen id in m_nodes suchen
	// - gibt den Pointer auf den Node zurück, wenn er gefunden wurde.
	// - gibt NULL zurück, falls kein Node mit der id gefunden wurde.

	//std::list<Node*>::iterator findTer = std::find(m_nodes.begin(), m_nodes.end(), );
	for (auto v : m_nodes) {
		if (v->getID() == id) {
			return v;
		}
	}

	return NULL;

	
}


//---------------------------------------------------------------------------------------------------------------------

Node& Graph::addNode(Node* pNewNode)
{
	if (findNode(pNewNode->getID()) != NULL) {
		throw std::string("Node already in Graph");
	}
	else {
		m_nodes.push_back(pNewNode);
	}

	return *pNewNode;
	// bitte diese Zeile entfernen, wenn Sie die Funktion implementieren:
	//return *new Node("");

	// Überprüfen Sie, ob schon ein Node mit der gegeben id im Graph vorhanden ist!
	// Falls ja:
	//  - Exception werfen
	// Falls nein:
	//  - den neuen Node 'pNewNode' in m_nodes einfügen
	//  - Referenz auf den neuen Node zurück geben

	
}


//---------------------------------------------------------------------------------------------------------------------

Edge& Graph::addEdge(Edge* pNewEdge)
{
	m_edges.push_back(pNewEdge);

	if (findNode(pNewEdge->getDstNode().getID()) == false) {
		addNode(&pNewEdge->getDstNode());
	}

	if (findNode(pNewEdge->getSrcNode().getID()) == false) {
		addNode(&pNewEdge->getSrcNode());
	}

	return *pNewEdge;

	// bitte diese Zeile entfernen, wenn Sie die Funktion implementieren:
	//return *new Edge(*new Node(), *new Node());

	// - die neue Edge 'pNewEdge' in m_edges einfügen
	// - Referenz auf die neue Edge zurück geben

	// - Testen Sie ob der Source- und Destination-Node von 'pNewEdge' schon im Graph vorhanden ist.
	// -> fügen Sie diese Nodes hinzu, falls nicht (nutzen Sie dafür Graph::addNode)

	
}


//---------------------------------------------------------------------------------------------------------------------

Graph::~Graph()
{

	// - soll alle Edges im Graph löschen (delete)
	// - soll alle Nodes im Graph löschen (delete)
	try {
		for (std::list<Edge*>::const_iterator it = m_edges.begin(); it != m_edges.end(); ++it)
		{
			delete *it;
		}
		m_edges.clear();

		for (std::list<Node*>::const_iterator it = m_nodes.begin(); it != m_nodes.end(); ++it)
		{
			delete *it;
		}
		m_nodes.clear();
	}
	catch (...) {
		// already cleared
		//std::cout << "Empty" << std::endl;
	}




}


//---------------------------------------------------------------------------------------------------------------------

void Graph::removeNode(Node& rNode)
{
	std::list<Edge*>::iterator i = m_edges.begin();
	while (i != m_edges.end()) {
		if ((*i)->isConnectedTo(rNode) == true) {
			i = m_edges.erase(i);
			
		}
		else {
			i++;
		}

	}


	m_nodes.remove(&rNode);
	delete &rNode;std::cout << "eraser is called" << std::endl;

	// - alle Edges, die mit rNode verbunden sind, müssen entfernt werden!
	// - finden sie den Pointer mit der Adresse von 'rNode' in m_nodes.
	// 		- der Pointer auf rNode soll aus m_nodes entfernt werden!
	// 		- der Pointer auf rNode muss mit 'delete' freigegeben werden!

	
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::removeEdge(Edge& rEdge)
{
	m_edges.remove(&rEdge);
	delete &rEdge;
	// - der Pointer auf rEdge muss aus m_edges entfernt werden!
	// - der Pointer auf rEdge muss mit 'delete' freigegeben werden!
}

	


//---------------------------------------------------------------------------------------------------------------------

	std::vector<Edge*> Graph::findEdges(const Node& rSrc, const Node& rDst)
	{
		std::vector<Edge*> ret;

		for (auto v : m_edges) {
			if (&v->getDstNode() == &rDst && &v->getSrcNode() == &rSrc) {
				ret.push_back(v);
			}
		}

		// - findet alle edges, mit rSrc als Source-Node und rDst als Destination-Node.
		// - füge die Zeiger der Edges in den vector 'ret' ein.

		return ret;
	}
	


//---------------------------------------------------------------------------------------------------------------------

// zeyed
double Graph::distance(const Node *rSrc, const Node *rDst)
{
	// return distance between two directly connected nodes or infinity if not connected (Helpful for Dijkstra)
	for (auto v : m_edges) {
		if (&v->getDstNode() == rDst && &v->getSrcNode() == rSrc) {
			return v->getWeight();
		}
	}
	return std::numeric_limits<double>::infinity();
}

Edge* Graph::findEdge(const Node *rSrc, const Node *rDst)
{
	// return first found edge between two connected nodes (Helpful for Dijkstra)
	for (auto v : m_edges) {
		if (&v->getDstNode() == rDst && &v->getSrcNode() == rSrc) {
			return v;
		}
	}
	return NULL; // should not happen todo fix
}

void Graph::saveAsDot(const std::string& rFilename, bool final)
{
	/*
	Kopieren Sie den Ordner ‚Peters\C23_Algorithmen_Programmierung\Tools\graphviz‘ im Dozentenserver auf ein lokales Laufwerk.

	Graphiz ist ein Tool, welches Graphen aus einer textuellen Beschreibung erzeugen kann.
	Betrachten Sie die Datei graph.dot.
	Formal ist die Datei folgendermaßen aufgebaut :

	digraph {
	concentrate = true
	<NODE_ID>;
	<NODE_ID>;
	<NODE_ID>;
	<EDGE_1>;
	<EDGE_2>;
	<EDGE_N>;
	}

	Starten Sie die Datei make.bat, damit Graphiz ein Bild des Graphen erstellt.
	Spielen Sie mit der Datei graph.dot herum und lassen Sie sich den Graph dazu generieren.


	Implementieren Sie nun die Funktion 'Graph::saveAsDot', damit sie eine Dot-Datei im angegebenen Dateipfad erzeugt!

	Hilfestellung:
	- Dateien speichern mit C++: http://www.cplusplus.com/reference/fstream/fstream/open/
	- Verwenden Sie die Funktionen Node::getID() und Edge::toString(), um die Einträge für die Nodes und Edges in der dot - Datei zu generieren.


	TEST:
	Testen Sie die Funktion, indem Sie indem Sie einen Graph in mit ein paar Nodes und Edges in main.cpp erstellen
	und anschließend eine dot-Datei generieren. Erstellen Sie ein Bild des Graphen mit Graphviz.

	*/
	std::fstream fs;
	fs.open(rFilename, std::fstream::out | std::fstream::trunc);
	fs << "digraph {" << std::endl;
	fs << "concentrate=true" << std::endl;
	fs << "rankdir = LR" << std::endl; // horizontal diagram for better visibility
	fs << "overlap = \"scale\"" << std::endl;
	fs << "labelfloat = true" << std::endl;
	fs << "splines = true" << std::endl;
	for (auto v : m_nodes) {
		fs << "\"" << v->getID() << "\"" << ";" << std::endl;
	}
	for (auto v : m_edges) {
		fs << "\"" << v->getSrcNode().getID() << "\"" << " -> " << "\"" << v->getDstNode().getID() << "\"" << " [label=\"" << v->getWeight() << "\"]; " << std::endl;
	}
	fs << "}" << std::endl;

	fs.close();


}


//---------------------------------------------------------------------------------------------------------------------

void Graph::findShortestPathDijkstra(double *gesamt, std::deque<Edge*>& rPath, const Node& rSrcNode, const Node& rDstNode)
{
	/*
	Ein häufiges Anwendungsproblem für Graphen-Anwendungen besteht darin,
	den Pfad zwischen verschiedenen Nodes zu finden, die direkt oder indirekt über Edges miteinander verbunden sind.
	Um den optimalsten Pfad(den mit den geringsten Kantengewichten) zu finden, gibt es den Dijkstra-Algorithmus!
	Pseudocode (Quelle: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
	>>>
	function Dijkstra(Graph, source):

	create vertex set Q

	for each vertex v in Graph:             // Initialization
	dist[v] ← INFINITY                  // Unknown distance from source to v
	prev[v] ← UNDEFINED                 // Previous node in optimal path from source
	add v to Q                          // All nodes initially in Q (unvisited nodes)

	dist[source] ← 0                        // Distance from source to source

	while Q is not empty:
	u ← vertex in Q with min dist[u]    // Source node will be selected first
	remove u from Q

	for each neighbor v of u:           // where v is still in Q.
	alt ← dist[u] + length(u, v)
	if alt < dist[v]:               // A shorter path to v has been found
	dist[v] ← alt
	prev[v] ← u

	return dist[], prev[]
	<<<

	Betrachten Sie den Pseudocode und setzen Sie ihn in C++ um.
	Sortieren Sie am Ende das Ergebnis in die richtige Reihenfolge um
	und geben sie die kürzeste Route zwischen rSrcNode und rDstNode als Liste von Edges zurück.

	
	*/
	std::list<const Node*> Q;
	std::map<const Node*, double> dist;
	std::map<const Node*, const Node*> prev;
	for (auto v : m_nodes) {
		dist.insert(std::pair<const Node*, double>(v, std::numeric_limits<double>::infinity()));
		prev.insert(std::pair<const Node*, const Node*>(v, NULL));
		Q.push_back(v);
	}

	const Node *src = &rSrcNode;
	const Node *dst = &rDstNode;

	dist[src] = 0;

	while (!Q.empty()) {
		const Node *u = NULL;
		double tmpdist = std::numeric_limits<double>::infinity();
		for (auto mindist : Q) {
			if (dist[mindist] < tmpdist) {
				u = mindist;
				tmpdist = dist[u];
			}
		}

		if (u == NULL) {
			if (dist[dst] == std::numeric_limits<double>::infinity()) {
				// we're done and no path was found
				return;
			}
			else {
				// a way was found
				break;
			}

		}
		//std::cout << "Selected u = " << u->getID() << std::endl;
		Q.remove(u);

		Node* test = const_cast<Node*>(u);
		for (auto tmp : test->getOutEdges()) { // get all neighbours of u
			const Node *v = nullptr;
			try {
				v = findNode(tmp->getDstNode().getID()); 
			}
			catch (...) {
				// node deleted and can't be proccesed
				std::cout << "Error deleted" << std::endl;
			}

			if ((std::find(Q.begin(), Q.end(), v) != Q.end())) { // if v still in q
				if (v != u) {
					//std::cout << "v: " << v->getID() << "| u: " << u->getID() << std::endl;
					double alt = dist[u] + distance(u, v);
					if (alt <= dist[v]) {
						dist[v] = alt;
						prev[v] = u;
						std::cout << "New Distance : " << alt << " | v: " << v->getID() << " | u: " << u->getID() << std::endl;
					}
				}
			}
		}



	}
	const Node *t1 = dst;
	const Node *t2 = prev[dst];
	rPath.push_front(findEdge(t2, t1));
	while (t2 != src) {
		std::swap(t1, t2);
		t2 = prev[t1];
		if (t2 == NULL) {
			t2 = src;
		}
		rPath.push_front(findEdge(t2, t1));
	}

	*gesamt = dist[dst];

	//std::cout << "Done doing things" << std::endl;



}


//---------------------------------------------------------------------------------------------------------------------

