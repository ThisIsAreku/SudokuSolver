/*
* UberSudokuSolver.cpp
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

    //cout << endl << "Fin du fastplace (" << tries << " placés, " << empty << " restants)" << endl << endl;

    //SudokuSolver::affiche();

    if(empty == 0)
    {
        //cout << "Grille complété par fastplace (" << tries << ")" << endl;
        return SudokuSolver::checkSolution(); // vérification de la solution
    }

    //cout << "Maintenant, Backtracking !" << endl;

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
    empty = 0;
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
            else
            {
                empty++;
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
void UberSudokuSolver::update_contraintes(int &x, int &y)
{
    empty--;
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

void UberSudokuSolver::fastplace()
{
    int p;
    bool one_edit;
    int rule_b_indexes_l[9], rule_b_counters_l[9];
    int rule_b_indexes_c[9], rule_b_counters_c[9];
    bool rule_b_done_l, rule_b_done_c;
    do
    {
        one_edit = false;
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if(m[i][j] == 0)
                {
                    for (int k = 0; k < 9; ++k)
                    {
                        if(!contraintes[i][j][k])
                            continue;
                        if(p == 0)
                        {
                            p = k + 1;
                        }
                        else
                        {
                            p = 0;
                            break;
                        }
                    }
                    if(p != 0)
                    {
                        m[i][j] = p;
                        update_contraintes(i, j);
                        //fill_contraintes();
                        one_edit = true;
                        tries++;
                    }
                }
            }
            for (int x = 0; x < 9; ++x)
            {
                rule_b_counters_l[x] = 0;
                rule_b_indexes_l[x] = 0;
                rule_b_counters_c[x] = 0;
                rule_b_indexes_c[x] = 0;
            }
            for (int j = 0; j < 9; ++j)
            {
                for (int k = 0; k < 9; ++k)
                {
                    if(contraintes[i][j][k] && m[i][j] == 0)
                    {
                        rule_b_counters_l[k]++;
                        rule_b_indexes_l[k] = j;
                    }
                    if(contraintes[j][i][k] && m[j][i] == 0)
                    {
                        rule_b_counters_c[k]++;
                        rule_b_indexes_c[k] = j;
                    }
                }
            }
            rule_b_done_l = rule_b_done_c = false;
            for (int x = 0; x < 9 && (!(rule_b_done_l && rule_b_done_c)); ++x)
            {
                if(rule_b_counters_l[x] == 1 && !rule_b_done_l)
                {
                    m[i][rule_b_indexes_l[x]] = x + 1;
                    update_contraintes(i, rule_b_indexes_l[x]);
                    //fill_contraintes();
                    one_edit = true;
                    rule_b_done_l = true;
                    tries++;
                }
                if(rule_b_counters_c[x] == 1 && !rule_b_done_c)
                {
                    m[rule_b_indexes_c[x]][i] = x + 1;
                    update_contraintes(rule_b_indexes_l[x], i);
                    //fill_contraintes();
                    one_edit = true;
                    rule_b_done_c = true;
                    tries++;
                }
            }
        }
    }
    while(one_edit);
}