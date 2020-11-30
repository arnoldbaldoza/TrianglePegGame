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
#include <list>
#include <iterator>
#include "Board.h"
#include "PegBoard.h"

//
// Private Methods
//

/// <summary>
/// PegBoard::ValidMove() determines if Move m is valid.
/// Be definition, a move is valid if m.from and m.jump is Full and m.to isEmpty.  
/// Move m is taken from PossibleMoves[], so there is no need to check if m.to, m.jump, and m.from are in a straight line.
/// </summary>
/// <param name="m">Move of which to determine validity</param>
/// <returns>Returns true/false if Move m is a valid/invalid move</returns>
bool PegBoard::ValidMove(Move m) {
	return (board.isEmpty(m.to) && board.isFull(m.from) && board.isFull(m.jump));
}

/// <summary>
/// PegBoard::RemainingPegs() returns how many pegs are on the board.  This is used by isSolved() to determine if the position is solved.
/// Future Optimization: Each move decreases the number of pegs on the board by one; one can use this fact to keep track of how many pegs remain.
/// </summary>
/// <param name=""></param>
/// <returns>returns int of how many Pegs remain on the board</returns>
int PegBoard::RemainingPegs(void) {
	int cnt = 0;
	for (int i = 0; i < NumberOfPegs; i++) {
		if (board.isFull(i))
			cnt++;
	}
	return cnt;
}

//
// Public Methods
//

/// <summary>
/// PegBoard::GetBoard() returns the board contained by PegBoard.
/// </summary>
/// <param name=""></param>
/// <returns>board contained in the PegBoard</returns>
Board PegBoard::GetBoard(void) {
	return board;
}

/// <summary>
///  PegBoard::GetPeg() returns the PEGSTATUS value of the specified Peg position
/// </summary>
/// <param name="i">Peg Position to be queried</param>
/// <returns></returns>
PEGSTATUS PegBoard::GetPeg(int i) {
	return board.GetPeg(i);
}

/// <summary>
/// PegBoard::SetPeg() sets the value of a specified Peg position to a specified PEGSTATUS value (Empty or Full)
/// </summary>
/// <param name="i">Peg Position to be Set</param>
/// <param name="val">PEGSTATUS value to which to set Peg Position</param>
void PegBoard::SetPeg(int i, PEGSTATUS val) {
	board.SetPeg(i, val); 
}

/// <summary>
/// PegBoard::SetBoardSolvable() sets boardSolvalbe to a specified bool value
/// </summary>
/// <param name="val">bool value to which to set boardSolvable</param>
void PegBoard::SetBoardSolvable(bool val) {
	boardSolvable = val;
}

/// <summary>
/// PegBoard::IsBoardSolvable() returns the bool value contained in boardSolvable.  Logically, this tells us if a board is Solvable or not.
/// </summary>
/// <param name=""></param>
/// <returns>boolean contained in private variable boardSolvable</returns>
bool PegBoard::IsBoardSolvable(void) {
	return boardSolvable;
}

/// <summary>
/// PegBoard::AddToPath() adds a move to the end of the std::list pathTo.  pathTo contains moves performed to get from starting configuration to current configuration.
/// </summary>
/// <param name="m"></param>
void PegBoard::AddToPath(Move m) {
	pathTo.push_back(m);
}

/// <summary>
/// PegBoard::ShowPathTo() displays the moves performed to get from the initial (starting) configuration to the current configuration.
/// </summary>
/// <param name=""></param>
void PegBoard::ShowPathTo(void) {
	typeListOfMoves::iterator it;
	Move currentMove;
	for (it = pathTo.begin(); it != pathTo.end(); it++) {
		currentMove = *it;
		std::cout << currentMove.from << " – " << currentMove.to << "; ";
	}
	std::cout << "\n";
}

/// <summary>
/// PegBoard::Initialize() initializes Board::board (specifies the starting vacancy) and any appropriate private variables of Class PegBoard.
/// </summary>
/// <param name="emptyPeg">Starting Vacancy</param>
void PegBoard::Initialize(int emptyPeg) {
	board.Initialize(emptyPeg);
	boardSolvable = false;
}

/// <summary>
/// PegBoard::isSolved() determines if the board is in a valid ending configuration (i.e., was the board solved or not).
/// By default, a valid ending configuration is a board with only 1 peg remaining, regardless of the position of the peg.
/// If different ending configurations are desired, change this function.
/// </summary>
/// <param name=""></param>
/// <returns> true/false if the board is in a valid ending configuration or not</returns>
bool PegBoard::isSolved() {
	return (RemainingPegs() == 1);
}


/// <summary>
/// PegBoard::CopyBoard() performs a hard/deep copy of the board contained by a specified PegBoard
/// </summary>
/// <param name="src">PegBoard to be copied</param>
void PegBoard::CopyBoard(PegBoard src) {
	for (int i = 0; i < NumberOfPegs; i++)
		SetPeg(i, src.GetPeg(i));
	pathTo = src.pathTo;
	boardSolvable = src.boardSolvable;
}

/// <summary>
///  PegBoard::ShowBoard() displays the board.  Used during development for debugging purposes.
/// </summary>
/// <param name=""></param>
void PegBoard::ShowBoard(void) {
	board.ShowBoard();
}

/// <summary>
///  PegBoard::GetAvailableMoves() places all possible moves into a list after determining if the move is valid.
/// Future Optimization: Update the list of possible moves in a smarter, more efficient manner instead of going through PossibleMoves[]
/// Future Optimization: Return a pointer to the list of available moves.  
/// </summary>
/// <param name=""></param>
/// <returns>Returns a list of Moves (typeListOfMoves), not a pointer to typeListOfMoves</returns>
typeListOfMoves PegBoard::GetAvailableMoves(void) {
	typeListOfMoves mlist;
	for (int i = 0; i < NUMBER_OF_POSSIBLE_MOVES; i++) {
		if (ValidMove(PossibleMoves[i])) {
			mlist.push_back(PossibleMoves[i]);
		}
	}
	return mlist;
}

/// <summary>
/// PegBoard::PerformMove() performs the specified move by moving a peg from its current position (from-square) to its intended square (to-square) and removing the peg on the jump-square.
/// The move is assumed to be valid.
/// </summary>
/// <param name="action">Move to perform</param>
void PegBoard::PerformMove(Move action) {
	board.setFull(action.to);
	board.setEmpty(action.from);
	board.setEmpty(action.jump);
}

/// <summary>
/// PegBoard::TakeBackmMove() reverses the specified move.  This is the reverse of PegBoard::PerformMove(). 
/// The move is assumed to be valid.
/// </summary>
/// <param name="action">Move to take back</param>
void PegBoard::TakeBackMove(Move action) {
	board.setEmpty(action.to);
	board.setFull(action.from);
	board.setFull(action.jump);
}









