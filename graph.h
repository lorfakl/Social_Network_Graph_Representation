/* 
Graph class with directed/undirected graphs represented using adjacency lists. 
A hashtable maps vertex ID to pointers to vertex objects. Vertices are assumed to be numbered by integers. 
Each vertex object is a struct with a vertex ID, pointer to Data, and a vector of pointers to edge objects. 
Each edge object is a struct with the fields target vertex and edge weight.
Methods are the different graph operations. 
An undirected graph is represented as two edges with each source and target nodes exchanged. The constructor 
can be specified to create an undirected graph by automattically putting edges in both directions 
The graph is constructed from a text file of edges one per line.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

typedef struct {
    bool visited; // Add other fields if needed
}Data;

typedef struct {
	int target_vertex;
	int weight; 
}Edge;

typedef struct {
	int vertex_id;
	Data* data;
	vector<Edge *> edge_list;
}Vertex;

class Graph {
	private:
		unordered_map<int, Vertex *> vertex_list;
		int num_edges;
		void addEdge(int vs, int vt);
	public:
		Graph():num_edges(0) {}; 
		Graph(bool insertReverseEdge, ifstream& ifs); // Reads the graph from a text file of edges one per line.
		~Graph();
		int getNumVertices() { return vertex_list.size();}
		int getNumEdges() { return num_edges;}
		void printGraph(); // For each vertex, print all the vertices it is connected to
		vector<Vertex*> BFS(int vs); // Visits nodes breadth first
		void DFS(int vs); // Visits nodes depth first
		Vertex* getVertex(int vt);
};

#endif
