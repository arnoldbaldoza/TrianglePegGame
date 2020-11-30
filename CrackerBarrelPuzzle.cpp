/*
  CrackerBarrelPuzzle, a depth-first-search solver developed under C++

  CrackerBarrelPuzzle is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  CrackerBarrelPuzzle is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

 #include <iostream>
#include <ctime>
#include "PegBoard.h"
#include "PegBoardSolver.h"

/// <summary>
/// timeAllSolutionsOneBoard() is a helper function that executes and times the solution for a board with a specified starting vacancy.
/// /// This does not use Look Up tables containing previously identified unsolvable configurations.
/// </summary>
/// <param name="myBoard">Board to be Solved</param>
/// <param name="solver">Solver to Employ</param>
/// <param name="emptyPeg">Starting Vacancy</param>
void timeAllSolutionsOneBoard(PegBoard myBoard, PegBoardSolver solver, int emptyPeg) {
    std::clock_t c_start, c_end;
    double duration;

    myBoard.Initialize(emptyPeg);
    solver.ShowSolutions = false;   // don't show solution to avoid impacting the timing statistic

    c_start = std::clock();
    solver.DFS_AllSolutions(myBoard);
    c_end = std::clock();
    duration = ((double)c_end - (double)c_start) / (double CLOCKS_PER_SEC);
    std::cout << emptyPeg << " Duration: " << duration << "\n";
}

/// <summary>
/// timeAllSolutionsOneBoardWithLookUp() is a helper function that executes and times the solution for a board with a specified starting vacancy.
/// This uses Look Up tables containing previously identified unsolvable configurations.
/// </summary>
/// <param name="myBoard">Board to be Solved</param>
/// <param name="solver">Solver to Employ</param>
/// <param name="emptyPeg">Starting Vacancy</param>
void timeAllSolutionsOneBoardWithLookUp(PegBoard *myBoard, PegBoardSolver solver, int emptyPeg) {
    std::clock_t c_start, c_end;
    double duration;

    myBoard->Initialize(emptyPeg);
    solver.ShowSolutions = false;   // don't show solution to avoid impacting the timing statistic

    c_start = std::clock();
    solver.DFS_AllSolutionsWithLookUpUtil(myBoard);
    c_end = std::clock();
    duration = ((double)c_end - (double)c_start) / (double CLOCKS_PER_SEC);
    std::cout << emptyPeg << " Duration: " << duration << "\n";
}

int main()
{
    PegBoard myBoard; 
    PegBoardSolver solver;

    /* Solve a Single Board -- No Look Up table; No timing statistic */
    /*
    myBoard.Initialize(4);
    solver.ShowSolutions = true;    // show solutions
    solver.DFS_AllSolutionsUtil(myBoard);
    */

    /* Solve Every Board -- No Look Up table; No timing statistic */
    /*
    for (int iEmpty = 0; iEmpty < NUMBER_OF_PEGS; iEmpty++) {
        myBoard.Initialize(iEmpty);
        solver.ShowSolutions = true;    // show solutions
        solver.DFS_AllSolutionsUtil(myBoard);
    }
    */

    /* Solve a Single Board -- No Look Up table; With timing statistic */
    /*
    timeAllSolutionsOneBoard(myBoard, solver, 4);
    */


    /* Solve each Starting Position Class -- No Look Up table; With timing statistic */
    /* 
    for (int i = 0; i < 5; i++) {
        timeAllSolutionsOneBoard(myBoard, solver, 0);
        timeAllSolutionsOneBoard(myBoard, solver, 1);
        timeAllSolutionsOneBoard(myBoard, solver, 3);
        timeAllSolutionsOneBoard(myBoard, solver, 4);
        std::cout << "\n";
    }
    */

    /* Solve a Single Board -- With Look Up table; No timing statistic */
    /*
    myBoard.Initialize(4);
    solver.DFS_AllSolutionsWithLookUpUtil(myBoard);
    */

    /* Solve a Single Board -- With Look Up table; With timing statistic */
    /*
    timeAllSolutionsOneBoardWithLookUp(&myBoard, solver, 4);
    */
  
    /* Solve each Starting Position Class -- With Look Up table; With timing statistic */
    ///*
    for (int i = 0; i < 5; i++) {
        timeAllSolutionsOneBoardWithLookUp(&myBoard, solver, 0);
        timeAllSolutionsOneBoardWithLookUp(&myBoard, solver, 1);
        timeAllSolutionsOneBoardWithLookUp(&myBoard, solver, 3);
        timeAllSolutionsOneBoardWithLookUp(&myBoard, solver, 4);
        std::cout << "\n";
    }
    //*/

    // Hard Pause
    std::cout << "DONE!\n";
    std::string userInputNeeded;
    std::cin >> userInputNeeded;
}