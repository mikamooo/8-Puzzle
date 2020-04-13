#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream in("test_puzzles.txt");
    int pzl = 1;

    if(!in.is_open())
    {
        cout << "Unable to open file." << endl;
        return 1;
    }

    while(!in.eof())
    {
        Graph g1, g2, g3;
        string row1, row2, row3, bfs, dfs, dijkstra, line;
        vector<int> puzzle (9, 0);

        getline(in, row1);
        getline(in, row2);
        getline(in, row3);

        puzzle.at(0) = stoi(row1.substr(0,1)); puzzle.at(1) = stoi(row1.substr(1,1)); puzzle.at(2) = stoi(row1.substr(2,1));
        puzzle.at(3) = stoi(row2.substr(0,1)); puzzle.at(4) = stoi(row2.substr(1,1)); puzzle.at(5) = stoi(row2.substr(2,1));
        puzzle.at(6) = stoi(row3.substr(0,1)); puzzle.at(7) = stoi(row3.substr(1,1)); puzzle.at(8) = stoi(row3.substr(2,1));

        getline(in, bfs);
        getline(in, dfs);
        getline(in, dijkstra);

        cout << "\e[1m*******TEST " << pzl << "*******\e[0m" << endl << endl;

        cout << "--------------------" << endl;
        cout << "\e[1mBreadth First Search\e[0m" << endl;
        cout << "--------------------" << endl << endl;
        g1.BFS(puzzle, 2);
        cout << "Expected cost: " << bfs << endl << endl;

        cout << "------------------" << endl;
        cout << "\e[1mDepth First Search\e[0m" << endl;
        cout << "------------------" << endl << endl;
        g2.DFS(puzzle, 2);
        cout << "Expected cost: " << dfs << endl << endl;
    
        cout << "--------" << endl;
        cout << "\e[1mDijkstra\e[0m" << endl;
        cout << "--------" << endl << endl;
        g3.Dijkstra(puzzle, 2);
        cout << "Expected cost: " << dijkstra << endl << endl;

        getline(in, line);
        pzl++;
    }

    return 0;
}