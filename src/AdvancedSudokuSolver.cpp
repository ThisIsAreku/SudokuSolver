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
    if(m[i][j] == 0)
    {
        for(int k = 1; k < 10; ++k)
        {
            m[i][j] = k;
            if(est_valide(i, j))
            {
                if(backtrack(p + 1))
                {
                    return true;
                }
            }
        }
        m[i][j] = 0;
        return false;
    }
    return backtrack(p + 1);
}

bool AdvancedSudokuSolver::est_valide(int &x, int &y)
{
    tries++;
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(i == j)
                continue;
            if(m[x][i] + m[x][j] == 0 || m[i][y] + m[j][y] == 0)
                continue;
            if(m[i][y] == m[j][y]) // si mm colonne
            {
                /*cout << "COL FAIL" << endl;
                cout << "m[" << i << "][" << y << "] == m[" << j << "]["<< y <<"] : " << m[i][y] << " == " << m[j][y] << endl;*/
                return false;
            }
            if(m[x][i] == m[x][j]) // si mm ligne
            {
                /* cout << "LIGNE FAIL" << endl;
                 cout << "m[" << x << "][" << i << "] == m[" << x << "]["<< j <<"] : " << m[x][i] << " == " << m[x][j] << endl;*/
                return false;
            }
        }
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
            for(int i2 = gxv; i2 < gxv + 3; ++i2)
            {
                for(int j2 = gyv; j2 < gyv + 3; ++j2)
                {
                    if(i == i2 && j == j2)
                        continue;
                    if(m[i][j] + m[i2][j2] == 0)
                        continue;
                    if(m[i][j] == m[i2][j2])
                    {
                        //cout << "GROUPE FAIL" << endl;
                        return false;
                    }
                }
            }
        }
    }
    // cout << "OK" << endl << endl;
    return true;

}