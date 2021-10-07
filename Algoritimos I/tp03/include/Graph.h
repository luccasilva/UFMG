#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>  

using namespace std;

class Edge {

public:
    bool visited;
    int x;
    int y;
};

class Graph {

public:
    Graph(int V, int E);
    void AddEdge(int v, int w);
    void PrintEdge();
    void minimalVertexCover();
    void aproxMinimalVertexCover();

private:
    int V;
    int E;
    list<int> *adj;
    vector<Edge> edgesList;
    void dfs(vector<int> decisionVector[], int src,int par);
};
#endif

