/*
* main.cpp
*
* Copyright 2013-2014 Alexandre Boucey <alexandre.boucey@alumni.univ-avignon.fr>
*
* This file is part of SudokuSolver.
*
* SudokuSolver is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License.
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
#include <ctime>
#include <cstdlib>

#include "SudokuSolver.h"
#include "BasicSudokuSolver.h"
#include "AdvancedSudokuSolver.h"
#include "UberSudokuSolver.h"


using namespace std;


void testWithSolver(SudokuSolver *solver, string grille){

    if(!solver->litGrille(grille))
    {
        cerr << "Erreur de lecture de la grille" << endl;
        exit(1);
    }
    cout << "Grille: " << endl;
    solver->affiche();

    clock_t tStart = clock();
    bool success = solver->solve();
    cout << "Temps: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s" << endl;
    cout << "Tentatives: " << solver->getTries() << endl;
    cout << "Grille ";
    if(!success)
        cout << "in";
    cout << "valide" << endl;
    solver->affiche();
}


int main(int argc, char *argv[])
{

    string grille("");
    if(argc == 2)
        grille = argv[1];

    cout << "Fichier grille: " << grille << endl;

    AdvancedSudokuSolver asolver;
    cout << endl << "Test avec AdvancedSudokuSolver"
         << endl << "==============================" << endl << endl;
    testWithSolver(&asolver, grille);

    UberSudokuSolver usolver;
    cout << endl << "Test avec UberSudokuSolver"
         << endl << "==========================" << endl << endl;
    testWithSolver(&usolver, grille);
}
