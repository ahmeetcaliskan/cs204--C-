#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

void InputCheckForSearching(int row, int column, int size, bool& checkProcess) {        /*This function check that row and column are in the range or not*/
    if (row < 0 || row >= size || column < 0 || column >= size) {
        checkProcess = false;
    }
};
void addition(int& num) {                           /*This function increment row or column depends on situation*/           
    num++;
}
void subtraction(int& num) {                        /*This function increment row or column depends on situation*/ 
    num--;
}
void characterCheck(string word, vector<vector<char>> nameOfPuzzle, int row, int column, int& characterDigit, bool& checkProcess) {             
    if (word[characterDigit] != nameOfPuzzle[row][column]) {
        checkProcess = false;                                                       /*This function check that puzzle character and word's substring are equal or not. If it is equal function move to other character, if is not stop whole process with bool*/ 
    }
    else {
        characterDigit++;
    }
};
void displaying(vector<string> stringMatrix) {                      /*This function displays finding words in puzzle*/ 
    cout << stringMatrix.size() << " Words are Found:  ";
    for (int counter = 0; counter < stringMatrix.size(); counter++) {
        cout << stringMatrix[counter] << " ";
    }
}
ifstream openingFile() {
    ifstream  openFile;
    do {
        string fileName;                /*Describing variables for input check*/

        cout << "Enter the name of the file" << endl; /*Importing input from user*/
        cin >> fileName;

        openFile.open(fileName);                    /*Input check process with if condition*/

        if (openFile.fail()) {
            cout << "Could not open the file " << fileName << endl;
        }
    } while (openFile.fail());

    return openFile;
}

bool Searching(string word, vector<vector<char>> nameOfPuzzle, int & row, int & column, int resetRow, int resetColumn, int size, string order) {
    int characterDigit = 1;                                      /*This function finding words in the puzzle with loops*/
    bool checkProcess = true;                                                           

    while (characterDigit != word.length() && checkProcess == true) {                    
        int numberForLoop = 1;
        while (checkProcess == true && characterDigit != word.length()) {
            int counter2 = 0;
            while (characterDigit != word.length() &&  counter2 < numberForLoop && checkProcess == true) {         /*This is first loop for searching*/
                if (order == "RightBottom" || order == "RightUp") {
                    addition(row);
                }
                else if(order == "BottomRight" || order == "BottomLeft") {
                    addition(column);

                }
                else if (order == "UpLeft" || order == "UpRight") {
                    subtraction(column);
                }
                else {
                    subtraction(row);
                }

                if (checkProcess == false || characterDigit == word.length()) {
                    break;                                      /* Whole break parts are essantial for ending the loop because of checks or exporting word if it found*/
                }

                InputCheckForSearching(row, column, size, checkProcess);
                
                if (checkProcess == false || characterDigit == word.length()) {
                    break;
                }

                characterCheck(word, nameOfPuzzle, row, column, characterDigit, checkProcess);
                
                if (checkProcess == false || characterDigit == word.length()) {
                    break;
                }

                counter2++;
            }
            counter2 = 0;
            while (characterDigit != word.length() && counter2 < numberForLoop && checkProcess == true) {   /*Second searching direction*/
                if (order == "LeftBottom" || order == "RightBottom") {
                    addition(column);
                }
                else if (order == "BottomRight" || order == "UpRight") {
                    addition(row);

                }
                else if (order == "UpLeft" || order == "BottomLeft") {
                    subtraction(row);
                }
                else {
                    subtraction(column);
                }
                
                if (checkProcess == false || characterDigit == word.length()) {
                    break;
                }
                InputCheckForSearching(row, column, size, checkProcess);
                if (checkProcess == false || characterDigit == word.length()) {
                    break;
                }
                characterCheck(word, nameOfPuzzle, row, column, characterDigit, checkProcess);
                if (checkProcess == false || characterDigit == word.length()) {
                    break;
                }
                counter2++;
            }
            numberForLoop++;
            int counter = 0;
            while (characterDigit != word.length() && counter < numberForLoop && checkProcess == true) {        /*Third searching direction*/
                if (order == "RightBottom" || order == "RightUp") {
                    subtraction(row);
                }
                else if (order == "BottomRight" || order == "BottomLeft") {
                    subtraction(column);

                }
                else if (order == "UpLeft" || order == "UpRight") {
                    addition(column);
                }
                else {
                    addition(row);
                }


                if (checkProcess == false || characterDigit == word.length()) {
                    break;
                }
                InputCheckForSearching(row, column, size, checkProcess);
                if (checkProcess == false || characterDigit == word.length()) {
                    break;
                }
                characterCheck(word, nameOfPuzzle, row, column, characterDigit, checkProcess);
                if (checkProcess == false || characterDigit == word.length()) {
                    break;
                }
                counter++;
            }
            counter = 0;
            while(characterDigit != word.length() && counter < numberForLoop && checkProcess == true) {    /*Fourth searching direction*/
                if (order == "LeftBottom" || order == "RightBottom") {
                    subtraction(column);
                }
                else if (order == "BottomRight" || order == "UpRight") {
                    subtraction(row);

                }
                else if (order == "UpLeft" || order == "BottomLeft") {
                    addition(row);
                }
                else {
                    addition(column);
                }

                if (checkProcess == false || characterDigit == word.length()) {
                    break;
                }
                InputCheckForSearching(row, column, size, checkProcess);
                if (checkProcess == false || characterDigit == word.length()) {
                    break;
                }
                characterCheck(word, nameOfPuzzle, row, column, characterDigit, checkProcess);
                if (checkProcess == false || characterDigit == word.length()) {
                    break;
                }
                counter++;
            }
            numberForLoop++;
        }
    }
    if (checkProcess == false) {
        row = resetRow;                                 /*It is for resetting row and column values for next searching direction*/
        column = resetColumn;
        return false;
    }
    else {
        row = resetRow;
        column = resetColumn;
        return true;
    }
};

int main()
{
    ifstream  openFile = openingFile();

    string puzzleLines;
    getline(openFile, puzzleLines);                                             /*Importing puzzle size*/
    int numOfLines = stoi(puzzleLines);                                                  /*Convering puzzle size to integer*/
    vector<vector<char>> puzzle(numOfLines, vector<char>(numOfLines));         /*Creating puzzle matrix*/

    int counterRow = 0;
    while (counterRow < numOfLines) {                           /*While loop for putting characters to matrix*/
        string puzzleRow;
        getline(openFile, puzzleRow);
        if (puzzleRow.length() != numOfLines) {                  /*Input check for matrix*/
            cout << "Error: Input file is not in correct format!" << endl;
            return 0;
        }
        for (int characterCounter = 0; characterCounter < numOfLines; characterCounter++) {
            if ((puzzleRow[characterCounter] < 65) || (puzzleRow[characterCounter] > 90)) {        /*Input check for invalid characters*/
                cout << "Error: Input file is not in correct format!" << endl;
                return 0;
            }
            puzzle[counterRow][characterCounter] = puzzleRow[characterCounter];        /*Putting characters to puzzle*/
        }
        counterRow++;                           /*Transferring next row*/
    }

    string wordNumber;
    getline(openFile, wordNumber);
    int numberOfWords = stoi(wordNumber);         /*Importing number of words from file*/


    vector<string> wordMatrix(numberOfWords);          /*Creating vector for words*/

    for (int wordCounter = 0; wordCounter < numberOfWords; wordCounter++) {
        string wordLines;
        getline(openFile, wordLines);
        int wordLength = wordLines.length();
        for (int characterCounter2 = 0; characterCounter2 < wordLength; characterCounter2++) {
            if ((wordLines[characterCounter2] < 65) || (wordLines[characterCounter2] > 90)) {        /*Input check for invalid characters*/
                cout << "Error: Input file is not in correct format!" << endl;
                return 0;
            }
        }
        wordMatrix[wordCounter] = wordLines;                                                        /*Adding words to matrix*/
    }

    vector<string> findingWords;
    for (int counter = 0; counter < numberOfWords; counter++) {
        int RowCounter = 0;
        int ColumnCounter = 0;
        string wantedString = wordMatrix[counter];
        while(RowCounter < numOfLines) {                                                                /*Scanning every matrix part for searching */
            while(ColumnCounter < numOfLines) {
                if (wantedString[0] == puzzle[RowCounter][ColumnCounter]){                  /*Finding firsrt sentence*/
                    bool RightBottom = Searching(wantedString, puzzle, RowCounter, ColumnCounter, RowCounter, ColumnCounter, numOfLines, "RightBottom");     /*8 direction possiilites detect with these functions */

                    bool LeftBottom = Searching(wantedString, puzzle, RowCounter, ColumnCounter, RowCounter, ColumnCounter, numOfLines, "LeftBottom");      /*8 direction possiilites detect with these functions */

                    bool BottomRight = Searching(wantedString, puzzle, RowCounter, ColumnCounter, RowCounter, ColumnCounter, numOfLines, "BottomRight");        /*8 direction possiilites detect with these functions */

                    bool BottomLeft = Searching(wantedString, puzzle, RowCounter, ColumnCounter, RowCounter, ColumnCounter, numOfLines, "BottomLeft");      /*8 direction possiilites detect with these functions */

                    bool RightUp = Searching(wantedString, puzzle, RowCounter, ColumnCounter, RowCounter, ColumnCounter, numOfLines, "RightUp");            /*8 direction possiilites detect with these functions */

                    bool LeftUp = Searching(wantedString, puzzle, RowCounter, ColumnCounter, RowCounter, ColumnCounter, numOfLines, "LeftUp");              /*8 direction possiilites detect with these functions */

                    bool UpRight = Searching(wantedString, puzzle, RowCounter, ColumnCounter, RowCounter, ColumnCounter, numOfLines, "UpRight");            /*8 direction possiilites detect with these functions */

                    bool UpLeft = Searching(wantedString, puzzle, RowCounter, ColumnCounter, RowCounter, ColumnCounter, numOfLines, "UpLeft");          /*8 direction possiilites detect with these functions */

                    if ((RightBottom || RightUp || BottomLeft || BottomRight || UpRight || LeftBottom || LeftUp || UpLeft) && (find(findingWords.begin(), findingWords.end(), wantedString) == findingWords.end()) && (wantedString.length() >= 3)) {
                            findingWords.push_back(wantedString);

                    }
                }
                ColumnCounter++;
            }
            RowCounter++;                           /*Transferring to next row*/
            ColumnCounter = 0;
        }

    }
    displaying(findingWords);
    return 0;


}









/*Ahmet Caliskan 31065*/
