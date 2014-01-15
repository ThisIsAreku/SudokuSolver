/*
* BasicSudokuSolver.h
*
* Copyright 2013-2014 Alexandre Boucey <alexandre.boucey@alumni.univ-avignon.fr>
*
* This file is part of SudokuSolver.
*
* SudokuSolver is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* SudokuSolver is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with SudokuSolver.  If not, see <http://www.gnu.org/licenses/>.
*
*
*/

#ifndef __BASIC_SUDOKU_SOLVER_H_
#define __BASIC_SUDOKU_SOLVER_H_

#include "SudokuSolver.h"

class BasicSudokuSolver : public SudokuSolver
{
private:
    long tries;
    bool backtrack();
public:
    BasicSudokuSolver();
    ~BasicSudokuSolver();
//from SudokuSolver
    bool solve();
    int getTries();
};

#endif