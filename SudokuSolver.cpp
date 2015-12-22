/* SudokuSolver.cpp
 * Author: Camille Annan
 */

#include "Sudoku.h"


short sudoku1Data[9][9] = {{0, 0, 3, 0, 2, 0, 6, 0, 0}, {9, 0, 0, 3, 0, 5, 0, 0, 1}, {0, 0, 1, 8, 0, 6, 4, 0, 0},
    {0, 0, 8, 1, 0, 2, 9, 0, 0}, {7, 0, 0, 0, 0, 0, 0, 0, 8}, {0, 0, 6, 7, 0, 8, 2, 0, 0},
    {0, 0, 2, 6, 0, 9, 5, 0, 0}, {8, 0, 0, 2, 0, 3, 0, 0, 9}, {0, 0, 5, 0, 1, 0, 3, 0, 0}};


short sudoku2Data[9][9] = {{7, 9, 0, 4, 6, 0, 0, 0, 8}, {0, 4, 6, 0, 0, 0, 0, 9, 5}, {2, 0, 0, 1, 0, 8, 0, 7, 6},
    {0, 5, 0, 8, 1, 6, 3, 0, 0}, {0, 0, 7, 0, 3, 0, 0, 4, 0}, {0, 0, 0, 0, 5, 0, 8, 6, 9},
    {1, 0, 0, 9, 8, 0, 7, 0, 0}, {9, 2, 3, 5, 0, 0, 0, 0, 0}, {5, 0, 0, 6, 0, 3, 9, 0, 0}};


Sudoku sudoku1(sudoku1Data), sudoku2(sudoku2Data), *sudoku;
int iterationCount = 0;
bool singletonDomainsFound = false;




// eliminate singleton domains
void eliminateSingletonDomains()  {
    Space *currentSpace;
    for(int row = 0; row < 9; row++)  {
        for(int column = 0; column < 9; column++)  {
            currentSpace = sudoku->puzzle[row][column];
            if(currentSpace->value == 0 && currentSpace->satisfyAllDiff[0] > 0 && currentSpace->satisfyAllDiff[1] == 0)  { // current space has not been set, but only has one possible value in its satisfy alldiff domain
                sudoku->updatePuzzle(row, column, currentSpace->satisfyAllDiff[0], false);
                singletonDomainsFound = true;
            }
        }
    }
}




// solve a sudoku
void solve(int sudokuNumber)  {
    switch(sudokuNumber)  {
        case 1:
            sudoku = &sudoku1;
            break;
        case 2:
            sudoku = &sudoku2;
            break;
    }
    iterationCount = 0;
    cout << "\n(" << sudoku->unsolvedSpaces << " unsolved spaces)" << endl;
    while(sudoku->unsolvedSpaces > 0)  {
        singletonDomainsFound = false;
        eliminateSingletonDomains();
        iterationCount++;
    }
    cout << "\n" << endl;
}




// MAIN
int main()  {
    
    // solve first sudoku
    cout << "\nFIRST SUDOKU:";
    sudoku1.printPuzzle();
    solve(1);
    cout << "\nFirst sudoku solved in " << iterationCount << " iterations:" << endl;
    sudoku1.printPuzzle();
    
    cout << "\n***************************************" << endl;
    
    // solve second sudoku
    cout << "\nSECOND SUDOKU:";
    sudoku2.printPuzzle();
    solve(2);
    cout << "\nSecond sudoku solved in " << iterationCount << " iterations:" << endl;
    sudoku2.printPuzzle();
    
    return 0;
}











