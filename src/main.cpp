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
#include <cstring>

#include "SudokuSolver.h"
#include "BasicSudokuSolver.h"
#include "AdvancedSudokuSolver.h"
#include "UberSudokuSolver.h"


using namespace std;


void testWithSolver(SudokuSolver *solver, string grille)
{

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

void displayHelp(char cmdline[])
{
    cout << "Usage: " << cmdline << endl;
    cout << "--grid=<file>" << '\t' << "Select a grid file" << endl;
    cout << "--skip_basic" << '\t' << "Skip BasicSudokuSolver (because it's slow !)" << endl;
    cout << endl << "Without --grid=<file>, the program will try to load default.txt in the current working directory" << endl;
}


int main(int argc, char *argv[])
{
    cout << "SudokuSolver by Alexandre Boucey" << endl;
    cout << "http://pro.areku.fr/" << endl;
    cout << "Use --help to see options" << endl << endl;


    // lecture de la ligne de commande
    bool skip_basic = false;
    string grille("default.txt");

    string skip_basic_cmd("--skip_basic");
    string grid_cmd("--grid=");
    string help_cmd("--help");

    for (int i = 0; i < argc; ++i)
    {
        if(skip_basic_cmd.compare(argv[i]) == 0)
        {
            skip_basic = true;
        }
        else if(help_cmd.compare(argv[i]) == 0)
        {
            displayHelp(argv[0]);
            return 0;
        }
        else if(grid_cmd.compare(0, 7, argv[i], 0, 7) == 0)
        {
            grille = argv[i];
            grille = grille.substr(7);
        }
    }

    cout << "Fichier grille: " << grille << endl;

    UberSudokuSolver usolver;
    cout << endl << "Test avec UberSudokuSolver"
         << endl << "==========================" << endl << endl;
    testWithSolver(&usolver, grille);

    AdvancedSudokuSolver asolver;
    cout << endl << "Test avec AdvancedSudokuSolver"
         << endl << "==============================" << endl << endl;
    testWithSolver(&asolver, grille);

    if(!skip_basic)
    {
        BasicSudokuSolver bsolver;
        cout << endl << "Test avec BasicSudokuSolver"
             << endl << "==============================" << endl << endl;
        testWithSolver(&bsolver, grille);
    }
    else
    {
        cout << endl << "Skipped BasicSudokuSolver" << endl;
    }
}
