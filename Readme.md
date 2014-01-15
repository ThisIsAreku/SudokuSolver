# SudokuSolver
## Solveur de sudoku optimisé en C++

Voici trois implémentations du Solver de sudoku:
* BasicSudokuSolver: ne fonctionne pas, ajouté pour respecter le sujet.
* AdvancedSudokuSolver: résout les sudoku par la méthode du backtracking
* UberSudokuSolver: trouve le maximum de cases à remplir par déduction avant de lancer une phase de backtracking

### BasicSudokuSolver
Cette implémentation ne fait rien. Le code de résolution est bien présent, mais l'énoncé est trop flou pour pouvoir résoudre correctement les sudoku
Tester toutes les solutions "à l'aveugle" est impossible et prendrait dans certain cas beaucoup trop de temps.

### AdvancedSudokuSolver
Cette implémentation peut résoudre n'importe quel sudoku en un temps dépendant de la complexité. Pour des sudoku simples, le temps de résolution est inférieur à 1 sec.