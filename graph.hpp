#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include <utility>
#include <vector>
using namespace std;

struct vertex // Structure to hold a node of the graph
{
    int label; // The name of the node (int value from 0 - n)
    vector<int> puzzle; // Array holding the puzzle -> First 3 elements = first row of 8 puzzle, etc.
    list<pair<vertex, unsigned long> > adjList; // Adjacency list to find adjacent nodes
};

struct edge // Structure to hold an edge between nodes
{
    pair<int, int> pairV; // The two nodes the edge is between
    unsigned long weight; // The weight of the edge
};

class Graph
{
    private:
        vector<vertex> vertices; // Vector to store all the vertices
        vector<edge> edges; // Vector to store all the edges
        int cost; // The total cost of to find the solution
        vector<int> solution;
        string algo;
        int label;
    public:
        Graph();
        ~Graph();
        bool alreadySolved(vertex);
        void findEmptySlot(vertex&);
        void UP(vertex&, int, int);
        void DOWN(vertex&, int, int);
        void LEFT(vertex&, int, int);
        void RIGHT(vertex&, int, int);
        bool existingVertex(vector<int>); // Checks whether a vertex has been regenerated
        bool visited(vector<vertex>, vertex);
        void BFS(vector<int>, int); // Breadth First Search
        void DFS(vector<int>, int); // Depth First Search
        void Dijkstra(vector<int>, int); // Dijkstra's Algorithm
        void print(vector<int>); // Print the solution and the total cost 
};

#endif 
