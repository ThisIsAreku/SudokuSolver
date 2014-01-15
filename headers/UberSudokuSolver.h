/*
* UberSudokuSolver.cpp
*
* Copyright 2013 Alexandre Boucey <alexandre.boucey@alumni.univ-avignon.fr>
*
* This file is part of Sudoku.
*
* Sudoku is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Sudoku is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Sudoku.  If not, see <http://www.gnu.org/licenses/>.
*
*
*/

#ifndef __UBER_SUDOKU_SOLVER_H_
#define __UBER_SUDOKU_SOLVER_H_

#include "SudokuSolver.h"

class UberSudokuSolver : public SudokuSolver
{
private:
    long tries;
    int empty;
    bool ** *contraintes;
    void fill_contraintes();
    void fastplace();
    bool checkSolution();
public:
    UberSudokuSolver();
    ~UberSudokuSolver();
//from SudokuSolver
    bool solve();
    int getTries();
};

#endif