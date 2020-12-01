# TrianglePegGame
Solving the Triangle Peg Game (aka Cracker Barrel Puzzle)

A C++ program using a depth-first search algorithm was developed to solve the 15-Peg Triangle Board Game.  This game has 438,984 unique solutions out of the possible 7,335,390 outcomes.  Optimizations to the baseline implementation employed a mechanism to abandon a potential solution once a board configuration had been determined to be unsolvable (i.e., does not result into a valid ending configuration) and a bitboard representation of the board.  These optimizations produced significant reductions in processing time.  
