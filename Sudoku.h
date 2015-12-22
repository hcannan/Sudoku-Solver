/* Sudoku.h
 * Author: Camille Annan
 */

#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <string>
using namespace std;



/// SPACE CLASS ///
class Space  {
public:
    
    short value;
    short satisfyAllDiff[9]; // potential space values satisfying alldiff constraint
    
    // constructor
    Space(short spaceValue)  {
        value = spaceValue;
        for(int i = 0; i < 9; i ++)  {
            if(value == 0)
                satisfyAllDiff[i] = i + 1;
            else
                satisfyAllDiff[i] = 0;
        }
    }
    
    
    // remove value from satisfy alldiff array
    void removeValueFromSatisfyAllDiff(short spaceValue)  {
        int updatedIndex = 0;
        short updated[9];
        bool valueFound = false;
        
        for(int i = 0; i < 9; i++)  { // iterate through original satisfyAllDiff values
            if(satisfyAllDiff[i] != spaceValue)  {
                updated[updatedIndex] = satisfyAllDiff[i];
                updatedIndex++;
            }  else
                valueFound = true;
        }
        if(valueFound) // only 8 values copied to updated array
            updated[updatedIndex] = 0;
        
        for(int i = 0; i < 9; i++) // replace original satisfyAllDif array with updated array
            satisfyAllDiff[i] = updated[i];
    }
};



/// SUDOKU CLASS ///
class Sudoku  {
public:
    
    Space *puzzle[9][9];
    int unsolvedSpaces;
    
    
    // constructor
    Sudoku(short spaceValues[9][9]);
    
    
    // destructor
    ~Sudoku();
    
    
    // get alldiff domains (make sure the domain of each space satisfies alldiff constraint)
    void getAllDiffDomains();
    
    
    // get alldiff domain for a space
    void getAllDiffDomainForSpace(int row, int column);
    
    
    // get space region (for a puzzle space)
    int getSpaceRegion(int row, int column);
    
    
    // update puzzle
    void updatePuzzle(int row, int column, short value, bool firstInitialization);
    
    
    // print puzzle
    void printPuzzle();
    
    
};
#endif