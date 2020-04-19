# 8-Puzzle
Program to solve an 8-puzzle using BFS, DFS, and Dijkstra's.

Source for BFS pseudocode: https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/tutorial/

Source for DFS pseudocode: https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/tutorial/

Source for Dijkstras: https://www.youtube.com/watch?v=GuCzYxHa7iA

## Compilation and Execution Instructions

To compile all files, use the command: make all

***Driver***

Running the driver version allows you to enter your own puzzle to be solved by any of the three algorithms. The driver provides a debug mode, which prints the path taken by the chosen algorithm, and a quiet mode, which only prints the initial along with the minimum cost and minimum number of moves.

When entering the puzzle to be solved, please enter the puzzle row by row with the element of each row separated by spaces.

To execute, use the command: ./driver

***NOTE:*** This program assumes that the puzzles to be solved are solvable so do not enter unsolvable puzzles. Also, some puzzles may result in very large minimum costs which may result in a seemingly infinite loop since the total possible moves for an 8-puzzle is over 180,000. If this occurs, the puzzle may be unsolvable or you may have to wait a while until the solution can be found.


***Tester***

Running the tester version uses the text file, test_puzzles.txt, and runs each puzzle in the file against BFS, DFS, and Dijkstra's algorithm then prints the minimum cost and number of moves for each.

To execute, use the command: ./tester

***IMPORTANT NOTE:*** A couple of puzzles in the test_puzzle.txt file result in large costs which causes a slight pause while the results are printing. This is not an error or sign of infinite loop, it just takes a little longer to calculate the large cost. Please let the program finish printing.
