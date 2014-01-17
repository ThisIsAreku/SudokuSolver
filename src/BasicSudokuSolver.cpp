/*
* BasicSudokuSolver.cpp
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

#include <iostream>

#include "SudokuSolver.h"
#include "BasicSudokuSolver.h"

using namespace std;


BasicSudokuSolver::BasicSudokuSolver()
{
}
BasicSudokuSolver::~BasicSudokuSolver()
{
}

bool BasicSudokuSolver::solve()
{
    tries = 0;
    return backtrack(0);
}

int BasicSudokuSolver::getTries()
{
    return tries;
}
bool BasicSudokuSolver::backtrack(int p)
{
    if(p >= 81)
        return SudokuSolver::checkSolution();

    int i = p / 9;
    int j = p % 9;
    if(m[i][j] != 0)
        return backtrack(p + 1);

    for(int k = 1; k < 10; ++k)
    {
        m[i][j] = k;
        tries++;
        if(backtrack(p + 1))
            return true;
    }
    m[i][j] = 0;
    return false;
}
