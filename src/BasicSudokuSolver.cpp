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
#include <cstdlib>
#include <ctime>

#include "SudokuSolver.h"
#include "BasicSudokuSolver.h"

using namespace std;


BasicSudokuSolver::BasicSudokuSolver()
{
    srand(time(NULL));
}
BasicSudokuSolver::~BasicSudokuSolver()
{
}

bool BasicSudokuSolver::solve()
{
    tries = 0;
    cout << "Cette implémentation ne peut pas fonctionner" << endl;
    cout << "Tester toutes les solution \"à l'aveugle\" n'est pas possible" << endl;
    return false;
    //return backtrack();
}

int BasicSudokuSolver::getTries()
{
    return tries;
}
bool BasicSudokuSolver::backtrack()
{
    int **m_cpy;
    m_cpy = new int*[9];
    for(int i = 0; i < 9; ++i)
        m_cpy[i] = new int[9];

    do
    {
        tries++;
        SudokuSolver::cloneTo(m, m_cpy);
        for(int i = 0; i < 81; i++)
        {
            if(m_cpy[i / 9][i % 9] == 0)
            {
                m_cpy[i / 9][i % 9] = (rand() % 9) + 1;
            }
        }
    }
    while(!SudokuSolver::checkSolution(m_cpy));

    SudokuSolver::cloneTo(m_cpy, m);
    for(int i = 0; i < 9; ++i)
    {
        delete [] m_cpy[i];
    }
    delete [] m_cpy;
    return true;
}