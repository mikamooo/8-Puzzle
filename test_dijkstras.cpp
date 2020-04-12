#include "graph.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iterator>
#include <stack>
using namespace std; 

int main()
{
    Graph g;
    vector<int> puzzle;
    int algo, mode;
    bool valid = false;

    //test start case
    // puzzle.push_back(1); puzzle.push_back(2); puzzle.push_back(3);
    // puzzle.push_back(8); puzzle.push_back(0); puzzle.push_back(4);
    // puzzle.push_back(7); puzzle.push_back(6); puzzle.push_back(5);

    // simple case
    // puzzle.push_back(1); puzzle.push_back(2); puzzle.push_back(3);
    // puzzle.push_back(8); puzzle.push_back(6); puzzle.push_back(4);
    // puzzle.push_back(7); puzzle.push_back(0); puzzle.push_back(5);

    // still an easy case 
    // puzzle.push_back(1); puzzle.push_back(2); puzzle.push_back(3);
    // puzzle.push_back(8); puzzle.push_back(6); puzzle.push_back(4);
    // puzzle.push_back(7); puzzle.push_back(5); puzzle.push_back(0);

    // somewhat harder
    // puzzle.push_back(1); puzzle.push_back(0); puzzle.push_back(2);
    // puzzle.push_back(8); puzzle.push_back(8); puzzle.push_back(3);
    // puzzle.push_back(7); puzzle.push_back(5); puzzle.push_back(4);

    // somewhat harder
    puzzle.push_back(1); puzzle.push_back(2); puzzle.push_back(3);
    puzzle.push_back(7); puzzle.push_back(8); puzzle.push_back(4);
    puzzle.push_back(0); puzzle.push_back(6); puzzle.push_back(5);


    vertex start;
    start.puzzle = puzzle;
    start.label = 0;

    g.Dijkstra(start.puzzle, 0);

    return 0;
}