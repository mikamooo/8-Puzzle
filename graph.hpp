#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include <utility>
#include <vector>
#include <map>
using namespace std;

struct vertex // Structure to hold a node of the graph
{
    int label; // The name of the node (int value from 0 - n)
    vector<int> puzzle; // Array holding the puzzle -> First 3 elements = first row of 8 puzzle, etc.
    list<pair<vertex, unsigned long> > adjList; // Adjacency list to find adjacent nodes

    int g; //the cost or penalty of making this MOVE
    int sumGH; // the current cost and manhattDistance used in Dijkstra's
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
        vector<vertex> path;
    public:
        Graph();
        ~Graph();
        bool alreadySolved(vertex);
        void findEmptySlot(vertex&);
        void MOVE(vertex&, int, int);
        bool existingPuzzle(vertex); // Checks whether a puzzle has been regenerated
        bool visited(vector<vertex>, vertex);
        void BFS(vector<int>, int); // Breadth First Search
        void DFS(vector<int>, int); // Depth First Search
        void Dijkstra(vector<int>, int); // Dijkstra's Algorithm
        void print(vector<int>, int isDijkstras = 0); // Print the solution and the total cost 
        int getCost() {return cost;}
};

#endif 
