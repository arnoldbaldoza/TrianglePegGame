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
#include <list>
#include "Board.h"

#define NUMBER_OF_POSSIBLE_MOVES 36
//#define SUCCESS_EXCEPTION 0

struct Move {
	int from;
	int to;
	int jump;
};

typedef std::list <Move> typeListOfMoves;
typedef std::list <Board> typeListOfBoards;

class PegBoard
{
private:
	// PossibleMoves[] contains the 36 possible moves on the board
	// This array is used to generate a list of available moves in a given position.
	// Optimization: Programmically determine valid moves from a specified peg position, as opposed to explicitly specifying them as we do now.
	//
	// A valid move requires <to> to be Empty, <from> to be Full, and <jump> to be Full
	Move PossibleMoves[NUMBER_OF_POSSIBLE_MOVES] = {
		{0,3,1}, {0,5,2},
		{1,6,3}, {1,8,4},
		{2,7,4}, {2,9,5},
		{3,0,1}, {3,5,4}, {3,10,6}, {3,12,7},
		{4,11,7},{4,13,8},
		{5,0,2}, {5,3,4}, {5,12,8}, {5,14,9},
		{6,1,3}, {6,8,7},
		{7,2,4}, {7,9,8},
		{8,1,4}, {8,6,7},
		{9,2,5}, {9,7,8},
		{10,3,6}, {10,12,11},
		{11,4,7}, {11,13,12},
		{12,3,7}, {12,5,8}, {12,10,11}, {12,14,13},
		{13,4,8}, {13,11,12},
		{14,5,9}, {14,12,13} };

	const int NumberOfPegs = NUMBER_OF_PEGS;

	// Private variables
	Board board;	// current configuration of the board
	bool BoardSolved = false; // Is the board in a valid ending (winning) configuration? 
	bool boardSolvable = false; // Has it already been determind that the board is Solvable or not?
	typeListOfMoves pathTo;	// moves performed to get from starting configuration to current configuration

	// Private methods
	bool ValidMove(Move m);
	int RemainingPegs(void);
	
public:
	// Public access methods
	Board GetBoard(void);
	PEGSTATUS GetPeg(int i);
	void SetPeg(int i, PEGSTATUS val);
	void SetBoardSolvable(bool val);
	bool IsBoardSolvable(void);
	void AddToPath(Move m);
	void ShowPathTo(void);


	void Initialize(int emptyPeg);
	bool isSolved(void);
	void CopyBoard(PegBoard src);
	void ShowBoard(void);
	
	typeListOfMoves GetAvailableMoves(void);
	void PerformMove(Move action);
	void TakeBackMove(Move action);
	
};


