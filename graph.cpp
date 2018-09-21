#include "graph.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

Graph::Graph(bool insertReverseEdge, ifstream& ifs)
{
	int num;
	int num2;
	vector<vector<int>> edgeTups;
	
	while(ifs >> num >> num2)
	{
		vector<int> verts;
		verts.push_back(num);
		verts.push_back(num2);
		edgeTups.push_back(verts);	
	}
	
	num_edges = edgeTups.size();
	Vertex* vertPtr;
	for(int index = 0; index < edgeTups.size(); index++)
	{
		for(int i =0; i < 2; i++)
		{
			int vertID = edgeTups[index][i];
			if(!(vertex_list.count(vertID))) //if the vertex is not in the hashmap make it
			{	
				vertPtr = new Vertex;
				vertPtr->vertex_id = vertID;
				Data* d = new Data;	//create Data pointer
				d->visited = false; //set visited value
				vertPtr->data = d;  //set data pointer to vertex
				
				vertex_list[vertPtr->vertex_id] = vertPtr;
			}
		}			
	}
	
	for(int i = 0; i < edgeTups.size(); i++)
	{
		Vertex* vertStart = vertex_list[edgeTups[i][0]];
		Vertex* vertEnd = vertex_list[edgeTups[i][1]];
		addEdge(vertStart->vertex_id, vertEnd->vertex_id);
		
		if(insertReverseEdge)
		{
			addEdge(vertEnd->vertex_id, vertStart->vertex_id);	
		}
	}
	//cout << "Hashmap Size: ";
	//cout  << vertex_list.size() << endl;
		
}

void Graph::addEdge(int vs, int ve)
{
	Vertex* vertStart = vertex_list[vs];
	Vertex* vertEnd = vertex_list[ve];
	
	Edge* e = new Edge;
	e->target_vertex = ve;
	e->weight = 0;
	
	vertStart->edge_list.push_back(e);
	//num_edges++;
}

vector<Vertex*> Graph::BFS(int vs)
{
	vector<Vertex*> verts;
	if(vertex_list.count(vs))
	{	
		cout << vs << endl;
		queue <Vertex*> vertExplored;
		
		Vertex* vertPtr = vertex_list[vs];
		vertExplored.push(vertPtr);
		vertPtr->data->visited = true;
		
		while(!vertExplored.empty())
		{
			vertPtr = vertExplored.front();
			vertExplored.pop();
			 
			for(int i =0; i < vertPtr->edge_list.size(); i++)
			{
				Vertex* destVertPtr = vertex_list[vertPtr->edge_list[i]->target_vertex]; //get the target vertex of the ith 
				if(!destVertPtr->data->visited)										     //edge in vertPtr's edge vector
				{
					destVertPtr->data->visited = true;
					vertExplored.push(destVertPtr);
					verts.push_back(destVertPtr);
					//cout << destVertPtr->vertex_id << endl;
				}																	 
			}
		}
		
		for(int i = 0; i < vertex_list.size(); i++) //reset the vertex to non-explored
		{
			if(vertex_list.count(i))
			{
				Vertex* restoreVertPtr = vertex_list[i];
				restoreVertPtr->data->visited = false;
			}
		}
		
		return verts;
	}
	else
	{
		return verts;
	}
}


void Graph::DFS(int vs)
{
	if(vertex_list.count(vs))
	{
		cout << vs << endl;
		stack<Vertex*> vertExplored;
		
		Vertex* vertPtr = vertex_list[vs];
		vertExplored.push(vertPtr);
		while(!vertExplored.empty())
		{
			vertPtr = vertExplored.top();
			if(!vertPtr->edge_list.empty())
			{
				for(int i =0; i < vertPtr->edge_list.size(); i++)
				{
					Vertex* destVertPtr = vertex_list[vertPtr->edge_list[i]->target_vertex];
					if(!destVertPtr->data->visited)
					{
						vertExplored.push(destVertPtr);
						destVertPtr->data->visited = true;
						vertPtr = vertExplored.top();
						cout << destVertPtr->vertex_id << endl;
					}
					else
					{	
						if(!vertExplored.empty())
						{
							vertExplored.pop();
							if(vertExplored.empty())
							{
								break;
							}
							vertPtr = vertExplored.top();
						}
					}
				}
			}
			else
			{
				vertExplored.pop();
			}
		}
		
		for(int i = 0; i < vertex_list.size(); i++) //reset the vertex to non-explored
		{
			if(vertex_list.count(i))
			{
				Vertex* restoreVertPtr = vertex_list[i];
				restoreVertPtr->data->visited = false;
			}
		}	
	}
	else
	{
		return;
	}
}


void Graph::printGraph()
{
	int size = vertex_list.size();
	
	for(int i = 0; i<size; i++)
	{
		if(vertex_list.count(i))
		{
			Vertex* vertPtr = vertex_list[i];
			for(int index = 0; index < vertPtr->edge_list.size(); index++)
			{
				cout << vertPtr->vertex_id << " " << vertPtr->edge_list[index]->target_vertex << endl;
			}
		}
	}
}
Vertex* Graph::getVertex(int vt)
{
	if(vertex_list.count(vt))
	{
		Vertex* v = vertex_list[vt];
		return v;
	}
	else
	{
		return new Vertex;
	}
	
}


Graph::~Graph()
{
	vertex_list.erase(vertex_list.begin());
}

