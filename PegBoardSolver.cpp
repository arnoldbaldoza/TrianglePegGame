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
#include "PegBoardSolver.h"
#include "PegBoard.h"

/// <summary>
/// Constructor.  Explicitly initializes the class.
/// </summary>
/// <param name=""></param>
PegBoardSolver::PegBoardSolver(void) {
	numSolution = 0;
	numNoSolution = 0;
	numSeenBefore = 0;	
	StopWithSolution = false; // Do we stop on the first solution?
	ShowSolutions = true; // Do we show the solutions as they are found?
	listUnSolvable.clear();
}

/// <summary>
/// PegBoardSolver::DFS_AllSolutionsUtil() is the utility function that solves the specified PegBoard and displays the statistics.
/// Future work: keep the solutions in a list for future use.
/// </summary>
/// <param name="parent"></param>
void PegBoardSolver::DFS_AllSolutionsUtil(PegBoard parent) {
	numSolution = 0;
	numNoSolution = 0;
	
	DFS_AllSolutions(parent);
	std::cout << "\n";
	std::cout << "Number of Solutions: " << numSolution << "\n";
	std::cout << "Number of No Solutions: " << numNoSolution << "\n";
	std::cout << "Number of Games : " << numSolution + numNoSolution << "\n";
	
}

/// <summary>
/// PegBoardSolver::DFS_AllSolutions() solves the specified PegBoard and keeps track of statistics.  This function does not keep track of unsolvable configurations (listUnSolvable).
/// If ShowSolutions == true, solutions are displayed as they are found.
/// If StopWithSolution == true, find only one solution.
/// Future work: keep the solutions in a list for future use.
/// </summary>
/// <param name="parent"></param>
void PegBoardSolver::DFS_AllSolutions(PegBoard parent) {
	// Is the board in a a valid ending (winning) configuration? If so, it has been solved
	if (parent.isSolved()) {
		numSolution++;
		if (ShowSolutions) {
			// Display the solution that was found
			std::cout << "[" << numSolution << "] ";
			parent.ShowPathTo();

			if (StopWithSolution) {
				StopFindingSolutions = true;
			}
		}
	}
	else { // if not solved, 
		typeListOfMoves moves = parent.GetAvailableMoves();
		PegBoard child;
	
		// While the board still has moves that have not been tried
		// Get the next move to try
		// Perform the move
		// Solve the next position
		// if Solved, indicate that the board has been solved and return
		// else take back the move and loop around for the next move
		if (moves.size() == 0) {
			numNoSolution++;	// no solution found for current configuration
		} 
		else while (moves.size() > 0) {
			Move m = moves.front(); // next move to attempt
			moves.pop_front();	// delete the move from the list
			child.CopyBoard(parent);
			child.PerformMove(m);
			child.AddToPath(m); //child.pathTo.push_back(m);
			DFS_AllSolutions(child);  // recursively find the solutions to the new configuration
			if (StopFindingSolutions)
				return;
		}
	}
}

/// <summary>
/// PegBoardSolver::DFS_AllSolutionsWithLookUpUtil() is the utility function that solves the specified PegBoard and displays the statistics.
/// Future work: keep the solutions in a list for future use.
/// </summary>
/// <param name="parent"></param>
void PegBoardSolver::DFS_AllSolutionsWithLookUpUtil(PegBoard *parent) {
	numSolution = 0;
	numNoSolution = 0;
	numSeenBefore = 0;
	listUnSolvable.clear();

	DFS_AllSolutionsWithLookUp(parent);
	std::cout << "\n";
	std::cout << "Number of Solutions: " << numSolution << "\n";
	std::cout << "Number of No Solutions: " << numNoSolution << "\n";
	std::cout << "Number of Seen Before as No Solutions: " << numSeenBefore << "\n";
	std::cout << "Size of Unsolvable List: " << listUnSolvable.size() << "\n";
	std::cout << "Number of Games : " << numSolution + numNoSolution << "\n";

}

/// <summary>
/// PegBoardSolver::DFS_AllSolutionsWithLookUp() solves the specified PegBoard and keeps track of statistics.  
/// This function keeps track of unsolvable configurations (listUnSolvable) and uses this to prevent itself from attempting to solve these types of configurations.
/// If ShowSolutions == true, solutions are displayed as they are found.
/// If StopWithSolution == true, find only one solution.
/// Future work: keep the solutions in a list for future use.
/// </summary>
/// <param name="parent"></param>
void PegBoardSolver::DFS_AllSolutionsWithLookUp(PegBoard *parent) {
	// visit current Board first, is it solved?
	if (parent->isSolved()) {
		numSolution++;
		parent->SetBoardSolvable(true);

		if (ShowSolutions) {
			std::cout << "[" << numSolution << "] ";
			parent->ShowPathTo();

			if (StopWithSolution) {
				StopFindingSolutions = true;
			}
		}
	}
	else { // if not solved, 
		Board pBoard = parent->GetBoard();
		if (IsBoardInUnsolvableList(pBoard)) {
			parent->SetBoardSolvable(false);
			numSeenBefore++;
			numNoSolution++;
		}
		else {
			// solve it!
			typeListOfMoves moves = parent->GetAvailableMoves();
			PegBoard child;

			// While the board still has moves that have not been tried
			// Get the next move to try
			// Perform the move
			// Solve the next position
			// if Solved, indicate that the board has been solved and return
			// else take back the move and loop around for the next move
			if ((moves.size() == 0) && (!parent->IsBoardSolvable())) {
				numNoSolution++;

				// add parent to list of unsolveable nodes
				Board pBoard = parent->GetBoard();
				
				listUnSolvable.push_back(pBoard);
			}
			else {
				while (moves.size() > 0) {

				Move m = moves.front(); // next move to attempt
				moves.pop_front();
				child.CopyBoard(*parent);
				child.PerformMove(m);
				child.AddToPath(m); //child.pathTo.push_back(m);
				DFS_AllSolutionsWithLookUp(&child);
				parent->SetBoardSolvable(parent->IsBoardSolvable() || child.IsBoardSolvable());

				if (StopWithSolution)
					return;
			}
				if (!parent->IsBoardSolvable()) {
					// add parent to list of unsolveable nodes
					Board pBoard = parent->GetBoard();
					listUnSolvable.push_back(pBoard);
				}
			}
		}
	}
}

/// <summary>
/// PegBoardSolver::IsBoardInUnsolvableList() determines if a specified board is in a list of boards that were deemed to be unsolvable.
/// Future Work: Explore how to speed up the search in this list.  
/// </summary>
/// <param name="node">Board to be searched in listUnsolvable</param>
/// <returns>Returns true/false if the specified node is in/not in the list</returns>
bool PegBoardSolver::IsBoardInUnsolvableList(Board node) {

	typeListOfBoards::iterator it;
	for (it = listUnSolvable.begin(); it != listUnSolvable.end(); it++) {
		if (node.isEqual(*it)) {
				return true;
			}
	}
	return false;
}

/// <summary>
/// PegBoardSolver::ShowUnsolvableList() displays the list of identified unsolvable configurations.  Used for debugging purposes.
/// </summary>
/// <param name=""></param>
void PegBoardSolver::ShowUnsolvableList(void) {

	typeListOfBoards::iterator it;
	for (it = listUnSolvable.begin(); it != listUnSolvable.end(); it++) {
		it->ShowBoard();
	}
}
