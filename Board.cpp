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
#include "Board.h"

/// <summary>
/// Board::GetPeg() returns the PEGSTATUS associated with a specified position on the board
/// </summary>
/// <param name="pos">Position to Query</param>
/// <returns>PEGSTATUS associated with the specified position</returns>
PEGSTATUS Board::GetPeg(int pos) {
	return (PEGSTATUS) Pegs[pos];
}

/// <summary>
/// Board::SetPeg() sets the PEGSTATUS associated with a specified position on the board to the specified value
/// </summary>
/// <param name="pos">Position on the board to be set</param>
/// <param name="val">PEGSTATUS value to set</param>
void Board::SetPeg(int pos, PEGSTATUS val) {
	Pegs[pos] = val;
}

/// <summary>
/// Board::setFull() is a special case of Board::SetPeg() wherein the PEGSTATUS is Full
/// </summary>
/// <param name="pos">Position of the board to be set to FULL></param>
void Board::setFull(int pos) {
	Pegs[pos] = Full;
}

/// <summary>
/// Board::setEmpty() is a special case of Board::SetPeg() wherein the PEGSTATUS is Empty
/// </summary>
/// <param name="pos">Position of the board to be set to FULL></param>
void Board::setEmpty(int pos) {
	Pegs[pos] = Empty;
}

/// <summary>
/// Board::DecreaseNumberOfRemainingPegs() decreases the variable NumberOfRemainingPegs
/// </summary>
/// <param name=""></param>
void Board::DecreaseNumberOfRemainingPegs(void) {
	NumberOfRemainingPegs--;
}

/// <summary>
/// Board::GetNumberOfRemainingPegs() returns the variable NumberOfRemainingPegs
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int Board::GetNumberOfRemainingPegs(void) {
	return NumberOfRemainingPegs;
}
/// <summary>
/// Board::SetNumberOfRemainingPegs() sets the variable NumberOfRemainingPegs to the specified value
/// </summary>
/// <param name="n">Value to which to set NumberOfRemainingPegs</param>
void Board::SetNumberOfRemainingPegs(int n) {
	NumberOfRemainingPegs = n;
}

/// <summary>
/// GetStartingVacancy() returns the saved starting vacancy for the board.  This can be used if we needed to solve for different ending configurations.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int Board::GetStartingVacancy(void) {
	return StartingVacancy;
}

/// <summary>
/// Board::isEmpty() checks if the specified board position is Empty
/// </summary>
/// <param name="pos">Position to be Queried</param>
/// <returns>Returns true/false if the board position is Empty/Full</returns>
bool Board::isEmpty(int pos) {
	return (Pegs[pos] == Empty);
}

/// <summary>
/// Board::isFull() checks if the specified board position is Full
/// </summary>
/// <param name="pos">Position to be Queried</param>
/// <returns>Returns true/false if the board position is Full/Empty</returns>
bool Board::isFull(int pos) {
	return (Pegs[pos] == Full);
}

/// <summary>
/// Board::isEqual() check is the specified board is equal to the current board 
/// </summary>
/// <param name="p">Board to be compared to</param>
/// <returns></returns>
bool Board::isEqual(Board p) {
	bool r = true;
	int i = 0;
	while ((i < NUMBER_OF_PEGS) && (r)) {
		r = (Pegs[i] == p.Pegs[i]);
		i++;
	}
	return r;
}

/// <summary>
/// Board::Initialize() initializes the board to a configuration wherein every board position is full except for the specified starting vacancy
/// </summary>
/// <param name="emptyPeg"></param>
void Board::Initialize(int startingVacancy) {
	for (int i = 0; i < NUMBER_OF_PEGS; i++)
		Pegs[i] = Full;
	Pegs[startingVacancy] = Empty;
	StartingVacancy = startingVacancy;
}

/// <summary>
/// Board::RemainingPegs() counts the number of pegs on the board.
/// </summary>
/// <param name=""></param>
/// <returns>Number of Pegs on the board</returns>
int Board::RemainingPegs(void) {
	int r = 0;
	for (int i = 0; i < NUMBER_OF_PEGS; i++)
		r += (int) Pegs[i];
	return r;
}

/// <summary>
/// Board::ShowBoard() displays the board.  Used for debugging purposes.
/// </summary>
/// <param name=""></param>
void Board::ShowBoard(void) {
	for (int i = 0; i < NUMBER_OF_PEGS; i++) {
		if (Pegs[i] == Full)
			std::cout << "Full ";
		else
			std::cout << "Empty ";
	}
	std::cout << "\n";
}