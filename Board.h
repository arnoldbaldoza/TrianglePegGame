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
#define NUMBER_OF_PEGS 15

enum PEGSTATUS { Empty = 0, Full = 1 };

class Board
{
private:
	PEGSTATUS Pegs[NUMBER_OF_PEGS];
	int NumberOfRemainingPegs = NUMBER_OF_PEGS;	// keeps track of the number of pegs on the board (replacement for RemainingPegs())
	int StartingVacancy; // keeps track of the starting vacancy of the board

public:

	PEGSTATUS GetPeg(int pos);
	void SetPeg(int pos, PEGSTATUS val);
	void setFull(int pos);
	void setEmpty(int pos);
	void DecreaseNumberOfRemainingPegs(void);
	int GetNumberOfRemainingPegs(void);
	void SetNumberOfRemainingPegs(int n);
	int GetStartingVacancy(void);


	bool isEmpty(int pos);
	bool isFull(int pos);
	bool isEqual(Board p);
	
	void Initialize(int emptyPeg);
	int RemainingPegs(void);
	void ShowBoard(void);
		
};
