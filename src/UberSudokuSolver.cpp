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
    // tableau 9*9*9 des contraintes
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
    fill_contraintes(); // initialise contraintes[][][];
    fastplace(); // trouve toutes les simplifications

    //cout << endl << "Fin du fastplace (" << tries << " placés, " << empty << " restants)" << endl << endl;

    //SudokuSolver::affiche();

    if(empty == 0) // si il ne reste pas de cases vides
    {
        //cout << "Grille complété par fastplace (" << tries << ")" << endl;
        return SudokuSolver::checkSolution(); // vérification de la solution
    }

    //cout << "Maintenant, Backtracking !" << endl;

    AdvancedSudokuSolver backtracking; // sinon, on instancie un object AdvancedSudokuSolver
    backtracking.importGrille(m); // on importe la grille pré remplie

    bool solved = backtracking.solve(); // on résout avec le backtracking

    tries += backtracking.getTries(); // on compte le nombre de tests supplémentaires

    SudokuSolver::cloneTo(backtracking.getGrille(), m); // on actualise la grille de notre instance

    return solved; // normalement, c'est résolu !
}

int UberSudokuSolver::getTries()
{
    return tries;
}

/* Remplis le tableau des contraintes avec les données */
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
                int gxv = (x / 3) * 3;
                int gyv = (y / 3) * 3;
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
}
/* met a jour les contraintes modifiés sans re-parcourir tout le tableau */
void UberSudokuSolver::update_contraintes(int &x, int &y)
{
    empty--;
    int v = m[x][y] - 1;
    for (int k = 0; k < 9; ++k)
    {
        contraintes[x][k][v] = false;
        contraintes[k][y][v] = false;
    }
    int gxv = (x / 3) * 3;
    int gyv = (y / 3) * 3;
    for (int gxp = gxv; gxp < gxv + 3; ++gxp)
    {
        for (int gyp = gyv; gyp < gyv + 3; ++gyp)
        {
            contraintes[gxp][gyp][v] = false;
        }
    }
}

/* méthode pour trouver les chiffres grâces aux contraintes */
void UberSudokuSolver::fastplace()
{
    bool one_edit;

    do
    {
        one_edit = false;
        for (int i = 0; i < 9; ++i)
        {
            one_edit |= findRuleA(i);
            one_edit |= findRuleB(i, false);
            one_edit |= findRuleB(i, true);
        }
        // add a lot of tries with few success..
        //one_edit |= findRuleBGroup();

    }
    while(one_edit);
}
bool UberSudokuSolver::findRuleA(int &i)
{
    int rule_a(0);
    for (int j = 0; j < 9; ++j)
    {
        if(m[i][j] == 0)
        {
            for (int k = 0; k < 9; ++k)
            {
                if(!contraintes[i][j][k])
                    continue;
                if(rule_a == 0)
                {
                    rule_a = k + 1;
                }
                else
                {
                    rule_a = 0;
                    break;
                }
            }
            if(rule_a != 0)
            {
                m[i][j] = rule_a;
                update_contraintes(i, j);
                return true;
                tries++;
            }
        }
    }
    return false;
}

/* reversed = true pour faire les lignes à la place des colonnes */
bool UberSudokuSolver::findRuleB(int &i, bool reversed)
{
    int indexes[9], counters[9];
    for (int x = 0; x < 9; ++x)
    {
        counters[x] = 0;
        indexes[x] = 0;
    }
    for (int j = 0; j < 9; ++j)
    {
        for (int k = 0; k < 9; ++k)
        {
            if(!reversed && contraintes[i][j][k] && m[i][j] == 0)
            {
                counters[k]++;
                indexes[k] = j;
            }
            else if(reversed && contraintes[j][i][k] && m[j][i] == 0)
            {
                counters[k]++;
                indexes[k] = j;
            }
        }
    }
    for (int x = 0; x < 9; ++x)
    {
        if(counters[x] == 1)
        {
            if(!reversed)
            {
                m[i][indexes[x]] = x + 1;
                update_contraintes(i, indexes[x]);
            }
            else
            {
                m[indexes[x]][i] = x + 1;
                update_contraintes(indexes[x], i);
            }
            tries++;
            return true;
        }
    }
    return false;
}

/* Lent, et ne marche pas. Fausse les sudoku simples, rallonge les sudoku moyens */
bool UberSudokuSolver::findRuleBGroup()
{
    int indexes_i[9], indexes_j[9], counters[9];
    for(int gxv = 0; gxv < 9; gxv += 3)
    {
        for(int gyv = 0; gyv < 9; gyv += 3)
        {
            cout << "v: " << gxv << ", " << gyv << endl;
            for (int x = 0; x < 9; ++x)
            {
                counters[x] = 0;
                indexes_i[x] = 0;
                indexes_j[x] = 0;
            }
            for (int i = gxv; i < gxv + 3; ++i)
            {
                for (int j = gyv; j < gyv + 3; ++j)
                {
                    if(m[i][j] != 0)
                        continue;
                    for (int k = 0; k < 9; ++k)
                    {
                        if(contraintes[i][j])
                        {
                            counters[k]++;
                            indexes_j[k] = j;
                            indexes_i[k] = i;
                        }
                    }
                }
            }
            for (int x = 0; x < 9; ++x)
            {
                if(counters[x] == 1)
                {
                    cout << indexes_i[x] << ", " << indexes_j[x] << endl;
                    cout << x << endl;
                    m[indexes_i[x]][indexes_j[x]] = x + 1;
                    update_contraintes(indexes_i[x], indexes_j[x]);
                    tries++;
                    return true;
                }
            }
        }
    }
    return false;
}
