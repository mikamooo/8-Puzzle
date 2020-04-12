#include "graph.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iterator>
#include <stack>
#include <map>
#include <stdlib.h>
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
    if (v.puzzle.at(0) == 0) // If the empty slot is the top left corner, the moves are RIGHT and DOWN
    {   
        MOVE(v, 0, 1); // RIGHT
        MOVE(v, 0, 3); // DOWN
        
    }
    else if (v.puzzle.at(1) == 0) // If the empty slot is the middle of the first row, the moves are LEFT, RIGHT, and DOWN
    {   
        MOVE(v, 1, 0); // LEFT
        MOVE(v, 1, 2); // RIGHT
        MOVE(v, 1, 4); // DOWN
    }
    else if (v.puzzle.at(2) == 0) // If the empty slot is the top left corner, the moves are LEFT and DOWN
    {   
        MOVE(v, 2, 1); // LEFT
        MOVE(v, 2, 5); // DOWN
    }
    else if (v.puzzle.at(3) == 0) // If the empty slot is the left of the second row, the moves are UP, RIGHT, and DOWN
    {   
        MOVE(v, 3, 0); // UP
        MOVE(v, 3, 4); // RIGHT
        MOVE(v, 3, 6); // DOWN
    }
    else if (v.puzzle.at(4) == 0) // If the empty slot is the middle of the second row, the moves are LEFT, UP, RIGHT, and DOWN
    {   
        MOVE(v, 4, 3); // LEFT
        MOVE(v, 4, 1); // UP
        MOVE(v, 4, 5); // RIGHT
        MOVE(v, 4, 7); // DOWN
    }
    else if (v.puzzle.at(5) == 0) // If the empty slot is the right of the second row, the moves are LEFT, UP, and DOWN
    {   
        MOVE(v, 5, 4); // LEFT
        MOVE(v, 5, 2); // UP
        MOVE(v, 5, 8); // DOWN
    }
    else if (v.puzzle.at(6) == 0) // If the empty slot is the left of the third row, the moves are UP, and RIGHT
    {    
        MOVE(v, 6, 3); // UP
        MOVE(v, 6, 7); // RIGHT
    }
    else if (v.puzzle.at(7) == 0) // If the empty slot is the middle of the third row, the moves are LEFT, UP and RIGHT
    {   
        MOVE(v, 7, 6); // LEFT
        MOVE(v, 7, 4); // UP
        MOVE(v, 7, 8); // RIGHT
    }
    else if (v.puzzle.at(8) == 0) // If the empty slot is the right of the third row, the moves are LEFT, and UP
    {   
        MOVE(v, 8, 7); // LEFT
        MOVE(v, 8, 5); // UP
    }
}

void Graph::MOVE(vertex& v, int empty, int tile) // Function to create a vertex for moving the empty slot
{
    vertex MOVE; // Create a vertex for moving
    MOVE.label = ++label; // Increment the label
    MOVE.puzzle = v.puzzle; // Initialize MOVE's puzzle to it's parent's puzzle
    MOVE.g = MOVE.puzzle.at(tile); // i think this is equivalent to e.weight but im not sure, its also == to label i think
    MOVE.puzzle.at(empty) = MOVE.puzzle.at(tile); // Then move the empty slot left, up, right, or down
    MOVE.puzzle.at(tile) = 0;

    edge e; // Create an edge between the two vertices
    e.pairV = make_pair(v.label, MOVE.label);
    if (algo == "D") // If the algorithm being used is Dijkstra 
        e.weight = MOVE.puzzle.at(empty); // Then the weight of the edge is the number of the moved tile
    else 
        e.weight = 1; // Otherwise it's just 1

    vertices.push_back(MOVE);
    edges.push_back(e);
    exists.emplace(make_pair(v.puzzle, true));
    v.adjList.push_back(make_pair(MOVE, e.weight)); // Update v and MOVE's adjacency lists
    MOVE.adjList.push_back(make_pair(v, e.weight));
}

void Graph::BFS(vector<int> pzl, int mode) // Breadth first search algorithm
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
    
    int current = 1; // Create a counter to access the weight of the current edge
    queue <vertex> Q; // Create a queue for performing a BFS
    map<int, bool> discovered; // Create a map to hold all the discovered nodes

    Q.push(initial); // Add the vertex containing the initial puzzle to the queue
    exists.emplace(make_pair(initial.puzzle, true)); // Add it to the existing puzzle states
    discovered.emplace(make_pair(initial.label, true)); // And mark it as discovered

    while(!Q.empty()) // Continue traversing the graph until the queue is empty
    {   
        vertex v = Q.front(); // Remove the vertex from queue whose neighbor will be visited now
        Q.pop();

        if (v.label != 0) // If the vertex isn't the initial puzzle, increment the cost
        {
            if (exists.count(v.puzzle) != 0) // Check if the puzzle state has been generated before
            {   
                v = Q.front(); // If it has remove the vertex from the queue
                Q.pop();
            }

            cost += edges.at(current).weight; // Increment the cost 
            current++;
        }

        if(alreadySolved(v)) // Check if v contains the solution 
        {
            solved = true; // If it contains the solution set solved to true
            cout << endl << "Puzzle solved!" << endl; // Print out the final result
            print(v.puzzle); 
        }
        else if (mode == 1 && v.label != 0) // If it doesn't contain the solution and we are in debug mode
        {
            cout << endl << "Move " << current - 1 << ":" << endl; // Print the current puzzle state
            print(v.puzzle);
        }

        findEmptySlot(v); // Then find the next possible moves and add them as children nodes 

        list<pair<vertex, unsigned long> >::iterator it; // Create an iterator to iterate through v's neighbors

        for (it = v.adjList.begin(); it != v.adjList.end(); it++) // Process each of v's neighbors
        {   
            if (discovered.count((*it).first.label) == 0) // Check if a neighbor node has been discovered yet
            { 
                Q.push((*it).first); // Push the neighbor node into the queue
                discovered.emplace(make_pair((*it).first.label, true)); // And mark the neighbor node as discovered
            }
        }
        
        if (solved) // If the puzzle has been solved break out of the while loop
            break;
    }
}

void Graph::DFS(vector<int> pzl, int mode)
{
    algo = "DFS";
    bool solved = false;

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

    int current = 1; // Create a counter to access the weight of the current edge
    stack <vertex> S; // Create a stack for performing a DFS
    map<int, bool> discovered; // Create a map to hold all the discovered nodes

    S.push(initial); // Add the vertex containing the initial puzzle to the stack
    exists.emplace(make_pair(initial.puzzle, true)); // Add it to the existing puzzle states
    discovered.emplace(make_pair(initial.label, true)); // And mark it as discovered

    while(!S.empty()) // Continue traversing the graph until the stack is empty
    {   
        vertex v = S.top(); // Remove the vertex from stack whose neighbor will be visited now
        S.pop();

       if (v.label != 0) // If the vertex isn't the initial puzzle, increment the cost
        {
            if (exists.count(v.puzzle) != 0) // Check if the puzzle state has been generated before
            {   
                v = S.top(); // If it has remove the vertex from the stack
                S.pop();
            }

            cost += edges.at(current).weight; // Increment the cost 
            current++;
        }

        if(alreadySolved(v)) // Check if v contains the solution 
        {
            solved = true; // If it contains the solution set solved to true
            cout << endl << "Puzzle solved!" << endl; // Print out the final result
            print(v.puzzle); 
        }
        else if (mode == 1 && v.label != 0) // If it doesn't contain the solution and we are in debug mode
        {
            cout << endl << "Move " << current - 1 << ":" << endl; // Print the current puzzle state
            print(v.puzzle);
        }

        findEmptySlot(v); // Then find the next possible moves and add them as children nodes 

        list<pair<vertex, unsigned long> >::reverse_iterator it; // Create an iterator to iterate through v's neighbors

        for (it = v.adjList.rbegin(); it != v.adjList.rend(); it++) // Process each of v's neighbors
        {   
            if (discovered.count((*it).first.label) == 0) // Check if a neighbor node has been discovered yet
            {
                S.push((*it).first); // Push the neighbor node onto the stack
                discovered.emplace(make_pair((*it).first.label, true)); // And mark the neighbor node as discovered
            }
        }
        
        if (solved) // If the puzzle has been solved break out of the while loop
            break;
    }
}

// the estimate cost taken from current state to the solution state 
//if 1 is at puzzle[0] then its 0 steps
//if 2 is at puzzle[3] then it is 2 steps away from goal --> 2*2 for the way it costs in our case
//sum of these steps away from goal is the manhattan distance
int manhattanDistance(vector<int> pzl){
    int count = 0;  //converting the vector into a matrix for calculations
    vector<vector<int>> board {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    // cout << "checking conversion to matrix" << endl;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            board[i][j] = pzl[count];
            count++;
            // cout << board[i][j] << " ";
        }
    }

    int sum = 0;

    div_t result;
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            if(board[i][j] != 0){   //i guess we dont count the displacement of 0???
                // int i_ = i;
                // int j_ = j;
                int value = 0;
                int spaces = 0;
                if(board[i][j] == 4||board[i][j] == 6||board[i][j] == 8){ //consider our arrangement for solution
                    switch(board[i][j]) {// these values treated as their parallel in other solution arrangement
                        case 4: value = 6; 
                                break;
                        case 6: value = 8;
                                break;
                        case 8: value = 4;
                                break;
                        default: cout << "some glitch in manhattabDistance()" << endl;
                    } // end switch
                    result = div(value-1, 3);
                    spaces = abs(result.quot - i) + abs(result.rem - j);    

                    cout << "value at board[i][j]: " << board[i][j] << endl;
                    cout << "num of spaces til correct place: " << spaces << endl; 
                } else if (board[i][j] == 5){
                    spaces = 4-i-j;
                    cout << "value at board[i][j]: " << board[i][j] << endl;
                    cout << "num of spaces til correct place: " << spaces << endl;
                } else {    
                    value = board[i][j]; // these values unchanged
                    result = div(value-1, 3);
                    spaces = abs(result.quot - i) + abs(result.rem - j);    

                    cout << "value at board[i][j]: " << board[i][j] << endl;
                    cout << "num of spaces til correct place: " << spaces << endl;
                }
                sum += spaces*value;    // because the cost of each move is not 1, but the value of the tile
            }
    return sum;
}

//G = current cost of steps taken to get t0 current state from initial
//H = manhattanDistance is cost remaining from current to reach goal

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



    
    // BFS-style search for next minimum step
    map<vector<int>, bool> seen;    //check if a node's puzzle has already been seen to avoid loops 
    vector<vertex> path;            // the shortest path
    vertex v = initial;
    int currCost = 0;

    seen.emplace(make_pair(v.puzzle, true));    // we have seen this initial vertex
    path.push_back(v);                          // we also agree it is the start of the path

    while(!alreadySolved(v)){   // while the node we are at is NOT the solution
        findEmptySlot(v);       // fill v.adjList where v.adjList[i] = (adjVertex, edgeweight)
        vertex minU;            // holds the u in N(v) that has the min sumGH
        minU.sumGH = INT_MAX;


        list<pair<vertex, unsigned long> >::iterator it; // Create an iterator to iterate through v's neighbors

        for(it = v.adjList.begin(); it != v.adjList.end(); ++it){  // for each u in N(v)
            vertex u = (*it).first;
            // cout << "u.g: " << u.g << endl; // check that we're adding the correct penalty for this move
            if(seen.count(u.puzzle) == 0){  //if this adjacent puzzle has not been generated yet
                cout << "solution has NOT been generated before" << endl;
                print(u.puzzle);
                seen.emplace(make_pair(u.puzzle, true));  // add to seen bc its been discovered
                // calculate G+H --> G will have to be the cost of this move U.g +currCost + manhattanDistance();
                u.sumGH = u.g + currCost + manhattanDistance(u.puzzle);
                // cout << "u.g: " << u.g << endl;
                // cout << "currCost: " << currCost << endl; 
                // cout << "manhattanDist: " << manhattanDistance(u.puzzle) << endl;
                if(u.sumGH < minU.sumGH){ // we need to keep track of which neighbor has the least sum
                    minU = u;
                }
            } else {
                cout << "solution has been generated before" << endl;
                print(u.puzzle);          
            }
        } // end for all u in N(v)

        path.push_back(minU); // add this min neighbor as next node in solution path
        currCost += minU.g; // curr cost is the addition of the tile value we just moved
        v = minU; // now we evaluate new node we chose
    } // end while


    //print the path
    for(int i = 0; i < path.size(); ++i){
        cout << endl << "Move " << i << ": " << endl;
        print(path[i].puzzle);
        cout << endl;
    }
    //print the final cost
    cout << "Minimum cost: " << currCost << endl;
}

void Graph::print(vector<int> pzl) // Function to print out the puzzle and cost
{
    cout << endl;
    cout << pzl.at(0) << " " << pzl.at(1) << " " << pzl.at(2) << endl;
    cout << pzl.at(3) << " " << pzl.at(4) << " " << pzl.at(5) << endl;
    cout << pzl.at(6) << " " << pzl.at(7) << " " << pzl.at(8) << endl << endl;
    cout << "Total cost: " << cost << endl;
}

