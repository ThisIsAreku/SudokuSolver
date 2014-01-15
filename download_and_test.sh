#!/bin/bash
cd "$(dirname "$0")"
DIFF=${1:-1]}
if [ $# -ne 1 ]||[ $DIFF -gt 4 ]||[ $DIFF -lt 1 ]; then
	echo "Difficulté entre 1 et 4"
	exit
fi
echo "Téléchargement de la grille..."
echo "Difficulté $DIFF"
SUDOKU_DATA=$(wget -qO- "http://www.sudoku.becher-sundstroem.de/read_db.php?value=$DIFF")
SUDOKU_DATA=$(echo $SUDOKU_DATA|cut -d"," -f"3-164")
SUD=
for (( k = 0; k < 3; k++ )); do
	for (( j = 0; j < 3; j++ )); do
		for (( i = 0; i < 3; i++ )); do
			SUD=$SUD$(echo $SUDOKU_DATA|cut -d"," -f"$(((($k*3 + $j)*9) + $i * 3 + 1))-$(((($k*3 + $j)*9) + $i * 3 + 3))")$'\t'
		done
		SUD=$SUD$'\n'
	done
	SUD=$SUD$'\n'
done
echo "$SUD"|sed -e 's/,/ /g' > temp.sudoku;
./bin/Sudoku temp.sudoku
rm temp.sudoku