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
#pragma once
#include "PegBoard.h"

typedef std::list <PegBoard> typeListOfPegBoards;

class PegBoardSolver
{
private:
	int numSolution = 0;	// Number of PegBoards to which a solution was found
	int numNoSolution = 0;  // Number of PegBoards to which a solution was not found
	int numSeenBefore = 0;	// Number of PegBoards that had previously been seen
	bool StopFindingSolutions = false;	// flag to stop finding solutions
	typeListOfBoards listUnSolvable;	// list of PegBoards determined to be UnSolvable

	bool IsBoardInUnsolvableList(Board p);	
	
public:
	bool StopWithSolution = false;	// Do we stop on the first solution?
	bool ShowSolutions = true;	// Do we show the solutions as they are found?

	PegBoardSolver(void);
	void DFS_AllSolutionsUtil(PegBoard p);
	void DFS_AllSolutions(PegBoard p);

	void DFS_AllSolutionsWithLookUpUtil(PegBoard *p);
	void DFS_AllSolutionsWithLookUp(PegBoard *p);

	void ShowUnsolvableList(void);
};

