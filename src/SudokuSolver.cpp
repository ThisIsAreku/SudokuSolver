/*
* SudokuSolver.cpp
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
#include <fstream>

#include "SudokuSolver.h"

using namespace std;

SudokuSolver::SudokuSolver()
{
    m = new int*[9];
    for(int i = 0; i < 9; ++i)
    {
        m[i] = new int[9];
        for(int j = 0; j < 9; ++j)
        {
            m[i][j] = 0;
        }
    }
}
SudokuSolver::~SudokuSolver()
{
    for(int i = 0; i < 9; ++i)
    {
        delete [] m[i];
    }
    delete [] m;
}

void SudokuSolver::affiche()
{
    affiche(m);
}
void SudokuSolver::affiche(int **m)
{
    for(int i = 0; i < 9; ++i)
    {
        if(i % 3 == 0 && i != 0)
            cout << endl;
        for(int j = 0; j < 9; ++j)
        {
            if(j % 3 == 0 && j != 0)
                cout << '\t';
            cout << m[i][j] << ' ';
        }
        cout << endl;
    }
}



bool SudokuSolver::litGrille(string grille)
{
    if(grille == "")
        grille = "grille.txt";
    ifstream ifgrille(grille);
    if(!ifgrille)
        return false;
    int v;
    for(int i = 0; i < 81; i++)
    {
        ifgrille >> v;
        m[i / 9][i % 9] = v;
    }
    return true;
}
void SudokuSolver::importGrille(int **g)
{
    cloneTo(g, m);
}

int **SudokuSolver::getGrille()
{
    return m;
}

void SudokuSolver::cloneTo(int **src, int **dst)
{
    for(int i = 0; i < 81; i++)
    {
        dst[i / 9][i % 9] = src[i / 9][i % 9];
    }
}

bool SudokuSolver::checkSolution()
{
    return checkSolution(m);
}
bool SudokuSolver::checkSolution(int **m)
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if(i != j)
            {
                for (int k = 0; k < 9; ++k)
                {
                    if(m[k][i] == m[k][j] || m[i][k] == m[j][k])
                        return false;
                }
            }
        }
    }
    int gxv, gyv;
    for (int gx = 0; gx < 3; ++gx)
    {
        for (int gy = 0; gy < 3; ++gy)
        {
            gxv = gx * 3;
            gyv = gy * 3;
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
                            if(m[i][j] == m[i2][j2])
                                return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}