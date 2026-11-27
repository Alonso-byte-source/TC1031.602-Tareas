/*
*  autor: Benjamin Valdes Aguirre
*  fecha: Diciembre 2020
*  programa: act 4.1 Implementacion Grafos
*  desc: estos programas son solciones parciales a algunos de
*  las actividades planteadas en el curso TC1031
*
*		Nota: Esta imlpementación es Top Down, no divide al árbol para la operacións
*		de barrado
*/

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>


using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    vector<int> *adjList;
		int *adjMatrix;
		//vector<Type> *vect = new vector<Type>

public:
		Graph(int);
		Graph();
		void addEdgeAdjList(int, int);
		void addEdgeAdjMatrix(int, int);
		string printAdjList();
		string printAdjMat();
		string printAdjMat_clean();
		string DFS(int, int);
		string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
		string BFS(int, int);
		string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
		string print_visited(list<int>);
		string print_path(vector<vector<int>>&,int ,int);
		bool contains(list<int>, int);
		void sortAdjList();
		void loadGraphList(string, int);
		void loadGraphMat(string, int, int);
};


void Graph::loadGraphList(string name, int a) {
    adjList = new vector<int>[a];
    nodes = a;
    edgesList = 0;

    stringstream ss(name);

    char c1, comma, c2;
    int u, v;

    while (ss >> c1 >> u >> comma >> v >> c2) {
        addEdgeAdjList(u, v);
    }

    sortAdjList();
}

void Graph::loadGraphMat(string name, int a, int b) {
    adjMatrix = new int[a * b];
    nodes = a;
    edgesMat = 0;

    for (int i = 0; i < a * b; i++) {
        adjMatrix[i] = 0;
    }

    stringstream ss(name);

    char c1, comma, c2;
    int u, v;

    while (ss >> c1 >> u >> comma >> v >> c2) {
        addEdgeAdjMatrix(u, v);
    }
}

Graph::Graph() {
    edgesList = 0;
    edgesMat = 0;
    nodes = 0;
    adjList = nullptr;
    adjMatrix = nullptr;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(),adjList[i].end());
}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}


string Graph::DFS(int start, int goal) {
    // Verificar que los vertices sean validos
    if (start < 0 || start >= nodes ||
        goal < 0 || goal >= nodes) {
        return "Invalid node";
    }

    stack<int> st;
    list<int> visited;
    vector<vector<int>> paths(nodes);

    // El nodo inicial es su propio padre
    paths[start].push_back(start);

    // Iniciar la busqueda
    return depthHelper(start, goal, st, visited, paths);
}

string Graph::depthHelper(int current, int goal,
                          stack<int>& st,
                          list<int>& visited,
                          vector<vector<int>>& paths) {

    vector<bool> discovered(nodes, false);
    vector<int> nextNeighbor(nodes, 0);

    st.push(current);
    discovered[current] = true;
    visited.push_back(current);

    int start = current;

    while(!st.empty()){
        current = st.top();
        if(current == goal){
            return print_visited(visited) + print_path(paths, start, goal);
        }

        if(nextNeighbor[current] >= adjList[current].size()){
            st.pop();
            continue;
        }

        int neighbor = adjList[current][nextNeighbor[current]];

        nextNeighbor[current]++;

        if(!discovered[neighbor]){
            discovered[neighbor] = true;
            visited.push_back(neighbor);
            paths[neighbor].push_back(current);
            st.push(neighbor);
        }
    }

    return print_visited(visited) + "node not found";
}



string Graph::BFS(int start, int goal) {

    // Verificar que los vertices sean validos
    if (start < 0 || start >= nodes ||
        goal < 0 || goal >= nodes) {
        return "Invalid node";
    }

    queue<int> qu;
    list<int> visited;
    vector<vector<int>> paths(nodes);

    // El nodo inicial es su propio padre
    paths[start].push_back(start);

    // Iniciar la busqueda
    return breadthHelper(start, goal, qu, visited, paths);
}



string Graph::breadthHelper(int current, int goal,
                            queue<int>& qu,
                            list<int>& visited,
                            vector<vector<int>>& paths) {

    qu.push(current);

    while(!qu.empty()){

        current = qu.front();
        qu.pop();

        visited.push_back(current);

        if(current == goal){
            int start = current;

            while(paths[start][0] != start){
                start = paths[start][0];
            }

            return print_visited(visited) +
                   print_path(paths, start, goal);
        }

        for(int neighbor : adjList[current]){

            if(paths[neighbor].empty()){

                paths[neighbor].push_back(current);

                qu.push(neighbor);
            }
        }
    }

    return print_visited(visited) + "node not found";
}

bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
  }
	return aux.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
  }
	return aux.str();
}
#endif /* Graph_H_ */
