#include "graph.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    Graph g;
    vector<int> puzzle (9, 0);
    int algo, mode;
    bool valid = false;

    cout << "Enter the 8-puzzle to be solved row by row. Use 0 to indicate the empty slot." << endl;
    cout << "For each row, enter each element separated by a space." << endl << endl;
    cout << "Enter the first row of elements in the 8-puzzle: ";
    cin >> puzzle.at(0) >> puzzle.at(1) >> puzzle.at(2);
    cout << "Enter the second row of elements in the 8-puzzle: ";
    cin >> puzzle.at(3) >> puzzle.at(4) >> puzzle.at(5);
    cout << "Enter the last row of elements in the 8-puzzle: ";
    cin >> puzzle.at(6) >> puzzle.at(7) >> puzzle.at(8);

    cout << endl << "Select mode: " << endl <<
                    "1) Debug: prints out each step of solving the puzzle." << endl << 
                    "2) Quiet: only prints the initial puzzle, final puzzle, and total cost." << endl;
    cin >> mode;

    while (!valid)
    {
        cout << endl << "Please select an algorithm:" << endl << 
                        "1) Breadth First Search" << endl <<
                        "2) Depth First Search" << endl <<
                        "3) Dijkstra's Algorirthm" << endl << endl;
        cin >> algo;

        if (algo == 1)
        {
            g.BFS(puzzle, mode);
            valid = true;
        }
        else if (algo == 2)
        {
            g.DFS(puzzle, mode);
            valid = true;
        }
        else if (algo == 3)
        {
            g.Dijkstra(puzzle, mode);
            valid = true;
        }
        else 
            cout << "Invalid option. Please select a valid option." << endl;
    }

    return 0;
}
