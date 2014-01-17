/*
* AdvancedSudokuSolver.cpp
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
#include <cstdlib>

#include "SudokuSolver.h"
#include "AdvancedSudokuSolver.h"

using namespace std;


AdvancedSudokuSolver::AdvancedSudokuSolver()
{
}
AdvancedSudokuSolver::~AdvancedSudokuSolver()
{
}

bool AdvancedSudokuSolver::solve()
{
    tries = 0;
    return backtrack(0);
}

int AdvancedSudokuSolver::getTries()
{
    return tries;
}

bool AdvancedSudokuSolver::backtrack(int p)
{
    if(p >= 81)
        return true;

    int i = p / 9;
    int j = p % 9;
    if(m[i][j] != 0)
        return backtrack(p + 1);

    for(int k = 1; k < 10; ++k)
    {
        if(valeur_valide(k, i, j))
        {
            m[i][j] = k;
            if(backtrack(p + 1))
                return true;
        }
    }
    m[i][j] = 0;
    return false;
}

bool AdvancedSudokuSolver::valeur_valide(int &v, int &x, int &y)
{
    tries++;
    for(int i = 0; i < 9; ++i)
    {
        if(m[x][i] == v || m[i][y] == v)
            return false;
    }

    int gx = x / 3;
    int gy = y / 3;

    int gxv = gx * 3;
    int gyv = gy * 3;

    // test si mm groupe
    for(int i = gxv; i < gxv + 3; ++i)
    {
        for(int j = gyv; j < gyv + 3; ++j)
        {
            if(m[i][j] == v)
                return false;
        }
    }
    // cout << "OK" << endl << endl;
    return true;

}