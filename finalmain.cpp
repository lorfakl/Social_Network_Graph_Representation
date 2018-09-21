#include "graph.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>

using namespace std;
struct Tup
{
	double num;
	int id;
};

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void findCloseFriends(Vertex* v, vector<Vertex*> e, int top);
void recommendFriends(Vertex* v, vector<Vertex*> e, int m);
double findIntersections(Vertex* vt, Vertex* other);
bool compareByNum(const Tup &a, const Tup &b);
int main(int argc, char** argv) {
	clock_t tStart = clock();
	
	srand(time(NULL));
	
	ifstream infile("facebook_combined.txt");
	Graph fbFriends(true, infile);
	//cout << fbFriends.getNumEdges() << endl;
	int vertNum = rand() % fbFriends.getNumVertices() + 1;
	int topFriends = rand() % 12 + 1;
	int recommendations = rand() % 15 + 1;
	cout << "Random Vertex Number: " << vertNum << endl;
	cout << "Random Top Number: " << topFriends << endl;
	cout << "Random Recommendation Number: " << recommendations << endl;
	vector<Vertex*> allVerts = fbFriends.BFS(vertNum);

	Vertex* v = fbFriends.getVertex(vertNum);
	findCloseFriends(v, allVerts, topFriends);
	recommendFriends(v, allVerts, recommendations);
	cout << "Time taken: " << (double)((clock() - tStart)) << "ms";
	return 0;
}

void findCloseFriends(Vertex* v, vector<Vertex*> all, int top)
{
	vector<Vertex*> targetFriends;
	
	for(int i =0; i<all.size(); i++) //find all vertices with v as a friend
	{
		for(int index = 0; index < all[i]->edge_list.size(); index++)
		{
			if(all[i]->edge_list[index]->target_vertex == v->vertex_id)
			{
				targetFriends.push_back(all[i]);
			}
		}
		
	}
	
	for(int i = 0; i < targetFriends.size(); i++)//Remove friends of V with more than 150 friends
	{
		//cout << "Friend #" << i << " has " << targetFriends[i]->edge_list.size() << " friends" << endl;
		
		if(targetFriends[i]->edge_list.size() > 150)//Dunbar's Number
		{
			targetFriends.erase(remove(targetFriends.begin(), targetFriends.end(), targetFriends[i]), targetFriends.end());
		}
	}
	
	
	if(top > targetFriends.size())
	{
		cout << "User does not have that many friends to rank" << endl;
		return;
	}
	else if(top == targetFriends.size())
	{
		cout << "User #:" << v->vertex_id << "'s top " << top << " friends are:" << endl;
		for(int i=0; i< targetFriends.size(); i++)
		{
			cout << "User#:" << targetFriends[i]->vertex_id << endl;
		}
		return;
	}
	
	vector<Tup> score;
	for(int i = 0; i< targetFriends.size(); i++)//Find Common Friends amoung V and V's friends
	{
		double s = findIntersections(v, targetFriends[i]);
		Tup t;
		t.id = targetFriends[i]->vertex_id;
		t.num = s;
		score.push_back(t);
		
	}
	
	sort(score.begin(), score.end(), compareByNum);
	cout << "User#:" << v->vertex_id << "'s top " << top << " friends are " <<endl;
	for(int i = 0; i < top; i++)
	{
		cout << "User#:" << score[score.size() - (i+1)].id << endl;
	}
}

void recommendFriends(Vertex* v, vector<Vertex*> all, int m)
{
	vector<Vertex*> targetFriends;
	int count = 0;
	for(int i =0; i<all.size(); i++) //find all vertices with v as a friend
	{
		for(int index = 0; index < v->edge_list.size(); index++)
		{	
			if(v->edge_list[index]->target_vertex == all[i]->vertex_id)
			{
				count++;
				all.erase(remove(all.begin(), all.end(), all[i]), all.end());
			}
		}
		
	}
	targetFriends = all;
		
	for(int i = 0; i < targetFriends.size(); i++)//Remove potential friends of V with more than 150 friends
	{	
		if(targetFriends[i]->edge_list.size() > 150)//Dunbar's Number
		{
			targetFriends.erase(remove(targetFriends.begin(), targetFriends.end(), targetFriends[i]), targetFriends.end());
		}
	}
	
	
	vector<Tup> score;
	for(int i = 0; i< targetFriends.size(); i++)//Find Common Friends amoung V and potential friends
	{
		double s = findIntersections(v, targetFriends[i]);
		Tup t;
		t.id = targetFriends[i]->vertex_id;
		t.num = s;
		score.push_back(t);
		
	}
	
	sort(score.begin(), score.end(), compareByNum);
	cout << "User#:" << v->vertex_id << "'s top " << m << " friend recommendations are " <<endl;
	for(int i = 0; i < m; i++)
	{
		cout << "User#:" << score[score.size() - (i+1)].id << endl;
	}
}

double findIntersections(Vertex* vt, Vertex* other)
{
	unordered_map<int, int> hashMap;
	vector<int> sameFriend;
	for(int i =0; i< vt->edge_list.size(); i++) //Find duplicates Assignment 7 strat
	{
		hashMap[vt->edge_list[i]->target_vertex] = 1;
	}
	
	for(int i=0; i < other->edge_list.size(); i++)
	{
		if(hashMap.count(other->edge_list[i]->target_vertex))
		{
			sameFriend.push_back(other->edge_list[i]->target_vertex);
		}
	}

	double n = sameFriend.size();
	double d = vt->edge_list.size();
	double percent = n/d * 100;
	
	
	return n/d;
}

bool compareByNum(const Tup &a, const Tup &b)
{
	return a.num < b.num;
}
