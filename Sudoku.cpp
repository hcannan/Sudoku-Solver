/* Sudoku.cpp
 * Author: Camille Annan
 */

#include "Sudoku.h"


/// SUDOKU CLASS IMPLEMENTATION ///

// constructor
Sudoku::Sudoku(short spaceValues[9][9])  {
    short currentValue = 0;
    unsolvedSpaces = 81;
    
    for(int row = 0; row < 9; row++)  {
        for(int column = 0; column < 9; column++)  {
            currentValue = spaceValues[row][column];
            updatePuzzle(row, column, currentValue, true);
        }
    }
    getAllDiffDomains();
}




// destructor
Sudoku::~Sudoku()  {
    for(int row = 0; row < 9; row++)  {
        for(int column = 0; column < 9; column++)  {
            delete puzzle[row][column];
        }
    }
}




// get all diff domains
void Sudoku::getAllDiffDomains()  {
    
    // for each space in puzzle, check already-set space values in space's same row, column, and group
    for(int row = 0; row < 9; row++)  {
        for(int column = 0; column < 9; column++)  {
            if(puzzle[row][column]->value == 0)
                getAllDiffDomainForSpace(row, column);
        }
    }
}




// get alldiff domain for space
void Sudoku::getAllDiffDomainForSpace(int row, int column)  {
    Space *space = puzzle[row][column];
    int groupRow = 0, groupColumn = 0, region = getSpaceRegion(row, column);
    
    switch(region)  {
        case 0:
            groupRow = 0, groupColumn = 0;
            break;
        case 1:
            groupRow = 0, groupColumn = 3;
            break;
        case 2:
            groupRow = 0, groupColumn = 6;
            break;
        case 3:
            groupRow = 3, groupColumn = 0;
            break;
        case 4:
            groupRow = 3, groupColumn = 3;
            break;
        case 5:
            groupRow = 3, groupColumn = 6;
            break;
        case 6:
            groupRow = 6, groupColumn = 0;
            break;
        case 7:
            groupRow = 6, groupColumn = 3;
            break;
        case 8:
            groupRow = 6, groupColumn = 6;
            break;
    }
    
    for(int i = 0; i < 9; i++)  {
        if(puzzle[row][i]->value > 0) // space in same row
            space->removeValueFromSatisfyAllDiff(puzzle[row][i]->value);
        if(puzzle[i][column]->value > 0) // space in same column
            space->removeValueFromSatisfyAllDiff(puzzle[i][column]->value);
        if(i < 3)  {
            if(puzzle[groupRow + i][groupColumn]->value > 0 && !(groupRow + i == row && groupColumn == column))
                space->removeValueFromSatisfyAllDiff(puzzle[groupRow + i][groupColumn]->value);
            if(puzzle[groupRow + i][groupColumn + 1]->value > 0 && !(groupRow + i == row && groupColumn + 1 == column))
                space->removeValueFromSatisfyAllDiff(puzzle[groupRow + i][groupColumn + 1]->value);
            if(puzzle[groupRow + i][groupColumn + 2]-> value > 0 && !(groupRow + i == row && groupColumn + 2 == column))
                space->removeValueFromSatisfyAllDiff(puzzle[groupRow + i][groupColumn + 2]->value);
        }
    }
}




// get space region
int Sudoku::getSpaceRegion(int row, int column)  {
    int toReturn = -1;
    if(row >= 0 && row <= 2)  {
        if(column >= 0 && column <= 2) // region 0
            toReturn = 0;
        else if(column >=3 && column <= 5) // region 1
            toReturn = 1;
        else if(column >= 6 && column <= 8) // region 2
            toReturn = 2;
    }  else if(row >= 3 && row <= 5)  {
        if(column >= 0 && column <= 2) // region 3
            toReturn = 3;
        else if(column >=3 && column <= 5) // region 4
            toReturn = 4;
        else if(column >= 6 && column <= 8) // region 5
            toReturn = 5;
    }  else if(row >= 6 && row <= 8)  {
        if(column >= 0 && column <= 2) // region 6
            toReturn = 6;
        else if(column >=3 && column <= 5) // region 7
            toReturn = 7;
        else if(column >= 6 && column <= 8) // region 8
            toReturn = 8;
    }
    return toReturn;
}




// update puzzle
void Sudoku::updatePuzzle(int row, int column, short value, bool firstInitialization)  {
    int groupRow = 0, groupColumn = 0, region = getSpaceRegion(row, column);
    
    if(value > 0)
        unsolvedSpaces--;
    
    if(firstInitialization)
        puzzle[row][column] = new Space(value);
    else  {
        puzzle[row][column]->value = value;
        puzzle[row][column]->satisfyAllDiff[0] = 0;
        
        switch(region)  {
            case 0:
                groupRow = 0, groupColumn = 0;
                break;
            case 1:
                groupRow = 0, groupColumn = 3;
                break;
            case 2:
                groupRow = 0, groupColumn = 6;
                break;
            case 3:
                groupRow = 3, groupColumn = 0;
                break;
            case 4:
                groupRow = 3, groupColumn = 3;
                break;
            case 5:
                groupRow = 3, groupColumn = 6;
                break;
            case 6:
                groupRow = 6, groupColumn = 0;
                break;
            case 7:
                groupRow = 6, groupColumn = 3;
                break;
            case 8:
                groupRow = 6, groupColumn = 6;
                break;
        }

        // update the domains of the spaces in the same row, column, and region as the changed space
        for(int i = 0; i < 9; i++)  {
            if(puzzle[row][i]->value == 0) // space in same row as changed space
                puzzle[row][i]->removeValueFromSatisfyAllDiff(value);
            if(puzzle[i][column]->value == 0) // space in same column as changed space
                puzzle[i][column]->removeValueFromSatisfyAllDiff(value);
            if(i < 3)  { // spaces in same region as changed space
                if(puzzle[groupRow + i][groupColumn]->value == 0)
                    puzzle[groupRow + i][groupColumn]->removeValueFromSatisfyAllDiff(value);
                if(puzzle[groupRow + i][groupColumn + 1]->value == 0)
                    puzzle[groupRow + i][groupColumn + 1]->removeValueFromSatisfyAllDiff(value);
                if(puzzle[groupRow + i][groupColumn + 2]->value == 0)
                    puzzle[groupRow + i][groupColumn + 2]->removeValueFromSatisfyAllDiff(value);
            }
        }
    }
}




// print puzzle
void Sudoku::printPuzzle()  {
    cout << endl;
    for(int row = 0; row < 9; row++)  {
        if(row == 0 || row == 3 || row == 6)
            cout << "=====================================" << endl;
        else
            cout << "-------------------------------------" << endl;
        cout << "| ";
        for(int column = 0; column < 9; column++)  {
            if(puzzle[row][column] > 0)  {
                if(column == 8)
                    cout << puzzle[row][column]->value << " |" << endl;
                else
                    cout << puzzle[row][column]->value << " | ";
            } else  {
                if(column == 8)
                    cout << "  |" << endl;
                else
                    cout << "  | ";
            }
        }
    }
    cout << "=====================================" << endl;
}

