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

#include <iostream>

#include "SudokuSolver.h"
#include "AdvancedSudokuSolver.h"
#include "UberSudokuSolver.h"

using namespace std;


UberSudokuSolver::UberSudokuSolver()
{

    contraintes = new bool **[9];
    for(int i = 0; i < 9; ++i)
    {
        contraintes[i] = new bool*[9];
        for(int j = 0; j < 9; ++j)
        {
            contraintes[i][j] = new bool[9];
            for(int k = 0; k < 9; ++k)
            {
                contraintes[i][j][k] = true;
            }
        }
    }
}
UberSudokuSolver::~UberSudokuSolver()
{
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            delete [] contraintes[i][j];
        }
        delete [] contraintes[i];
    }
    delete [] contraintes;
}

bool UberSudokuSolver::solve()
{
    tries = 0;
    fill_contraintes();
    fastplace();

    cout << endl << "end guess" << endl;

    SudokuSolver::affiche();

    cout << "Now, backtracking..." << endl;
    cout << "after " << tries << " guess" << endl;

    AdvancedSudokuSolver backtracking;
    backtracking.importGrille(m);

    bool solved = backtracking.solve();

    tries += backtracking.getTries();

    SudokuSolver::cloneTo(backtracking.getGrille(), m);

    return solved;
}

int UberSudokuSolver::getTries()
{
    return tries;
}

void UberSudokuSolver::fill_contraintes()
{
    for (int x = 0; x < 9; ++x)
    {
        for (int y = 0; y < 9; ++y)
        {
            if(m[x][y] > 0)
            {
                int v = m[x][y] - 1;
                for (int k = 0; k < 9; ++k)
                {
                    contraintes[x][k][v] = false;
                    contraintes[k][y][v] = false;
                }
                int gx = x / 3;
                int gy = y / 3;
                int gxv = gx * 3;
                int gyv = gy * 3;
                for (int gxp = gxv; gxp < gxv + 3; ++gxp)
                {
                    for (int gyp = gyv; gyp < gyv + 3; ++gyp)
                    {
                        contraintes[gxp][gyp][v] = false;
                    }
                }
            }
        }
    }
    /*
        for (int k = 0; k < 9; ++k)
        {
            cout << "======= " << k+1 << " =======" << endl;
            for(int i = 0; i < 9; ++i)
            {
                if(i % 3 == 0 && i != 0)
                    cout << endl;
                for(int j = 0; j < 9; ++j)
                {
                    if(j % 3 == 0 && j != 0)
                        cout << '\t';
                    cout << contraintes[i][j][k] << ' ';
                }
                cout << endl;
            }
        }*/
}

void UberSudokuSolver::fastplace()
{
    int p;
    bool one_edit = false;
    do
    {
        one_edit = false;
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if(m[i][j] == 0)
                {
                    p = findFastplace(i, j);
                    if(p != 0)
                    {
                        m[i][j] = p;
                        fill_contraintes();
                        one_edit = true;
                        tries++;
                    }
                }
            }
        }
    }
    while(one_edit);
}
int UberSudokuSolver::findFastplace(int &i, int &j)
{
    int possibility = 0;
    for (int k = 0; k < 9; ++k)
    {
        if(!contraintes[i][j][k])
            continue;
        if(possibility == 0)
            possibility = k + 1;
        else
            return 0;
    }
    return possibility;
}