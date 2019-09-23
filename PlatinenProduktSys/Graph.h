#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <deque>
#include <string>
#include "Node.h"
#include "Edge.h"


	class Graph
{

public:

	virtual ~Graph();

	


	Node& addNode(Node* pNewNode);

	Edge& addEdge(Edge* pNewEdge);

	void removeNode(Node& rNode);

	void removeEdge(Edge& rEdge);


	const std::list<Node*>& getNodes() { return m_nodes; }

	const std::list<Edge*>& getEdges() { return m_edges; }

	Node* findNode(const std::string& id);


	std::vector<Edge*> findEdges(const Node & rSrc, const Node & rDst);

	double distance(const Node *rSrc, const Node *rDst);

	std::string line(const Node *rSrc, const Node *rDst);

	Edge* findEdge(const Node *rSrc, const Node *rDst);


	void saveAsDot(const std::string& rFilename, bool final = false);

	void findShortestPathDijkstra(double *gesamt, std::deque<Edge*>& rPath, const Node& rSrcNode, const Node& rDstNode);


protected:

	std::list<Node*> m_nodes;
	std::list<Edge*> m_edges;

};

#endif