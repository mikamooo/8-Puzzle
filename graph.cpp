#include "graph.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iterator>
using namespace std;

Graph::Graph()
{
    cost = 0; // The cost starts at 0
    label = 0; // Label starts at 0
    solution.push_back(1); solution.push_back(2); solution.push_back(3);// The final solution to all 8-puzzles
    solution.push_back(8); solution.push_back(0); solution.push_back(4);
    solution.push_back(7); solution.push_back(6); solution.push_back(5);
}
Graph::~Graph()
{
    vertices.clear();
    edges.clear();
    solution.clear();
}

bool Graph::alreadySolved(vertex v) // Function to check if the initial puzzle is already solved
{
    if (v.puzzle == solution)
        return true;
    else
        return false;
}

void Graph::findEmptySlot(vertex& v) // Function to find the possible moves given the location of the empty slot
{
    if (v.puzzle.at(0) == 0) // If the empty slot is the top left corner, the moves are LEFT and UP
    {   
        LEFT(v, 0, 1);
        UP(v, 0, 3);
        
    }
    else if (v.puzzle.at(1) == 0) // If the empty slot is the middle of the first row, the moves are LEFT, UP, and RIGHT
    {   
        LEFT(v, 1, 2);
        UP(v, 1, 4);
        RIGHT(v, 1, 0);
    }
    else if (v.puzzle.at(2) == 0) // If the empty slot is the top left corner, the moves are RIGHT and UP
    {   
        UP(v, 2, 5);
        RIGHT(v, 2, 1);
    }
    else if (v.puzzle.at(3) == 0) // If the empty slot is the left of the second row, the moves are LEFT, UP, and DOWN
    {   
        LEFT(v, 3, 4);
        UP(v, 3, 6);
        DOWN(v, 3, 0);
    }
    else if (v.puzzle.at(4) == 0) // If the empty slot is the middle of the second row, the moves are LEFT, UP, RIGHT, and DOWN
    {   
        LEFT(v, 4, 5);
        UP(v, 4, 7);
        RIGHT(v, 4, 3);
        DOWN(v, 4, 1);
    }
    else if (v.puzzle.at(5) == 0) // If the empty slot is the right of the second row, the moves are UP, RIGHT, and DOWN
    {   
        UP(v, 5, 8);
        RIGHT(v, 5, 4);
        DOWN(v, 5, 2);
    }
    else if (v.puzzle.at(6) == 0) // If the empty slot is the left of the third row, the moves are LEFT, and DOWN
    {   
        LEFT(v, 6, 7);
        DOWN(v, 6, 3);
    }
    else if (v.puzzle.at(7) == 0) // If the empty slot is the middle of the third row, the moves are LEFT, RIGHT and DOWN
    {   
        LEFT(v, 7, 8);
        RIGHT(v, 7, 6);
        DOWN(v, 7, 4);
    }
    else if (v.puzzle.at(8) == 0) // If the empty slot is the right of the third row, the moves are RIGHT, and DOWN
    {   
        RIGHT(v, 8, 7);
        DOWN(v, 8, 5);
    }
}

void Graph::UP(vertex& v, int empty, int tile) // Function to create a vertex that shifts a tile up
{
    vertex UP; // Create a vertex for moving up
    UP.label = ++label; // Increment the label
    UP.puzzle = v.puzzle; // Initialize UP's puzzle to it's parent's puzzle
    UP.puzzle.at(empty) = UP.puzzle.at(tile); // Then move the tile below the empty slot up
    UP.puzzle.at(tile) = 0;

    edge e; // Create an edge between the two vertices
    e.pairV = make_pair(v.label, UP.label);
    if (algo == "D") // If the algorithm being used is Dijkstra 
        e.weight = UP.puzzle.at(empty); // Then the weight of the edge is the number of the moved tile
    else 
        e.weight = 1; // Otherwise it's just 1

    vertices.push_back(UP);
    edges.push_back(e);
    v.adjList.push_back(make_pair(UP, e.weight)); // Update v and UP's adjacency lists
    UP.adjList.push_back(make_pair(v, e.weight));
}

void Graph::DOWN(vertex& v, int empty, int tile) // Function to create a vertex that shifts a tile down
{
    vertex DOWN; // Create a vertex for moving up
    DOWN.label = ++label; // Increment the label
    DOWN.puzzle = v.puzzle; // Initialize UP's puzzle to it's parent's puzzle
    DOWN.puzzle.at(empty) = DOWN.puzzle.at(tile); // Then move the tile below the empty slot up
    DOWN.puzzle.at(tile) = 0;

    edge e; // Create an edge between the two vertices
    e.pairV = make_pair(v.label, DOWN.label);
    if (algo == "D") // If the algorithm being used is Dijkstra 
        e.weight = DOWN.puzzle.at(empty); // Then the weight of the edge is the number of the moved tile
    else 
        e.weight = 1; // Otherwise it's just 1

    vertices.push_back(DOWN);
    edges.push_back(e);
    v.adjList.push_back(make_pair(DOWN, e.weight)); // Update v and UP's adjacency lists
    DOWN.adjList.push_back(make_pair(v, e.weight));
}

void Graph::LEFT(vertex& v, int empty, int tile) // Function to create a vertex that shifts a tile left
{
    vertex LEFT; // Create a vertex for moving left
    LEFT.label = ++label; // Increment the label
    LEFT.puzzle = v.puzzle; // Initialize LEFT's puzzle to it's parent's puzzle
    LEFT.puzzle.at(empty) = LEFT.puzzle.at(tile); // Then move the tile to the right of empty slot left
    LEFT.puzzle.at(tile) = 0;

    edge e; // Create an edge between the two vertices
    e.pairV = make_pair(v.label, LEFT.label);
    if (algo == "D") // If the algorithm being used is Dijkstra 
        e.weight = LEFT.puzzle.at(empty); // Then the weight of the edge is the number of the moved tile
    else 
        e.weight = 1; // Otherwise it's just 1

    vertices.push_back(LEFT);
    edges.push_back(e);
    v.adjList.push_back(make_pair(LEFT, e.weight)); // Update v and UP's adjacency lists
    LEFT.adjList.push_back(make_pair(v, e.weight));
}

void Graph::RIGHT(vertex& v, int empty, int tile) // Function to create a vertex that shifts a tile right
{
    vertex RIGHT; // Create a vertex for moving left
    RIGHT.label = ++label; // Increment the label
    RIGHT.puzzle = v.puzzle; // Initialize LEFT's puzzle to it's parent's puzzle
    RIGHT.puzzle.at(empty) = RIGHT.puzzle.at(tile); // Then move the tile to the right of empty slot left
    RIGHT.puzzle.at(tile) = 0;

    edge e; // Create an edge between the two vertices
    e.pairV = make_pair(v.label, RIGHT.label);
    if (algo == "D") // If the algorithm being used is Dijkstra 
        e.weight = RIGHT.puzzle.at(empty); // Then the weight of the edge is the number of the moved tile
    else 
        e.weight = 1; // Otherwise it's just 1

    vertices.push_back(RIGHT);
    edges.push_back(e);
    v.adjList.push_back(make_pair(RIGHT, e.weight)); // Update v and UP's adjacency lists
    RIGHT.adjList.push_back(make_pair(v, e.weight));
}

bool Graph::visited(vector <vertex> visit, vertex v)
{
    for (int i = 0; i < visit.size(); i++)
    {
        if (visit.at(i).label == v.label)
            return true;
    }

    return false;
}

void Graph::BFS(vector<int> pzl, int mode)
{
    algo = "BFS";
    bool solved = false;

    vertex initial; // Create the root node that contains the initial state of the puzzle
    initial.label = label;
    initial.puzzle = pzl;

    cout << "Initial puzzle" << endl; // Print out the initial puzzle
    print(initial.puzzle);

    if(alreadySolved(initial)) // Check that the puzzle is not already solved
    {
        cout << "This puzzle is already solved." << endl;
        return;
    }

    vertices.push_back(initial); // Add the root to the list of vertices in our graph

    findEmptySlot(initial); // Find the next possible moves and add them as children nodes of initial
    
    int current = 1; // Create a counter to access the weight of the current edge
    queue <vertex> Q; // Create a queue for performing a BFS
    vector <vertex> discovered; // Create a vector to hold all the discovered nodes

    Q.push(initial); // Add the vertex containing the initial puzzle to the queue
    discovered.push_back(initial); // And mark it as discovered

    while(!Q.empty()) // Continue traversing the graph until the queue is empty
    {   
        vertex v = Q.front(); // Remove the vertex from queue whose neighbor will be visited now
        Q.pop();

        list<pair<vertex, unsigned long> >::iterator it; // Create an iterator to iterate through v's neighbors

        for (it = v.adjList.begin(); it != v.adjList.end(); it++) // Process each of v's neighbors
        {   
            cost += edges.at(current).weight; // Increment the cost 
            current++;

            if (!visited(discovered, (*it).first)) // Check if a neighbor node has been discovered yet
            {
                if(alreadySolved((*it).first)) // If it hasn't, check if it contains the solution 
                {
                    solved = true; // If it contains the solution set solved to true
                    cout << endl << "Puzzle solved!" << endl; // Print out the final result
                    print((*it).first.puzzle); 
                    break; // And break out of the for loop
                }
                else if (mode == 1) // If it doesn't contain the solution and we are in debug mode
                {
                    cout << endl << "Move " << (*it).first.label << ":" << endl; // Print the current puzzle state
                    print((*it).first.puzzle);
                }

                findEmptySlot((*it).first); // Then find the next possible moves and add them as children nodes 
                Q.push((*it).first); // Push the neighbor node into the queue
                discovered.push_back((*it).first); // And mark the neighbor node as discovered
            }
        }
        
        if (solved) // If the puzzle has been solved break out of the while loop
            break;
    }
/*  For debugging
    for (int i = 0; i < vertices.size(); i++)
    {
        cout << endl << vertices.at(i).label << endl << endl;
        cout << vertices.at(i).puzzle.at(0) << " " << vertices.at(i).puzzle.at(1) << " " << vertices.at(i).puzzle.at(2) << endl;
        cout << vertices.at(i).puzzle.at(3) << " " << vertices.at(i).puzzle.at(4) << " " << vertices.at(i).puzzle.at(5) << endl;
        cout << vertices.at(i).puzzle.at(6) << " " << vertices.at(i).puzzle.at(7) << " " << vertices.at(i).puzzle.at(8) << endl;
    } */
}

void Graph::DFS(vector<int> pzl, int mode)
{
    algo = "DFS";

    vertex initial; // Create the root node that contains the initial state of the puzzle
    initial.label = 0;
    initial.puzzle = pzl;

    cout << "Initial puzzle" << endl; // Print out the initial puzzle
    print(initial.puzzle);

    if(alreadySolved(initial)) // Check that the puzzle is not already solved
    {
        cout << "This puzzle is already solved." << endl;
        return;
    }

    vertices.push_back(initial); // Add the root to the list of vertices in our graph

}

void Graph::Dijkstra(vector<int> pzl, int mode)
{
    algo = "D";

    vertex initial; // Create the root node that contains the initial state of the puzzle
    initial.label = 0;
    initial.puzzle = pzl;

    cout << "Initial puzzle" << endl; // Print out the initial puzzle
    print(initial.puzzle);

    if(alreadySolved(initial)) // Check that the puzzle is not already solved
    {
        cout << "This puzzle is already solved." << endl;
        return;
    }

    vertices.push_back(initial); // Add the root to the list of vertices in our graph
}

void Graph::print(vector<int> pzl) // Function to print out the puzzle and cost
{
    cout << endl;
    cout << pzl.at(0) << " " << pzl.at(1) << " " << pzl.at(2) << endl;
    cout << pzl.at(3) << " " << pzl.at(4) << " " << pzl.at(5) << endl;
    cout << pzl.at(6) << " " << pzl.at(7) << " " << pzl.at(8) << endl << endl;
    cout << "Total cost: " << cost << endl;
}

