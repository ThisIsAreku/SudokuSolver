/*
* SudokuSolver.cpp
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

#ifndef __SUDOKU_SOLVER_H_
#define __SUDOKU_SOLVER_H_
class SudokuSolver
{
protected:
    int **m;
    bool checkSolution();
    bool checkSolution(int **);
    void cloneTo(int **, int **);
public:
    SudokuSolver();
    virtual ~SudokuSolver();
    void affiche();
    void affiche(int **);
    bool litGrille(std::string);
    void importGrille(int **);
    int **getGrille();
    virtual bool solve() = 0;
    virtual int getTries() = 0;
};

#endif