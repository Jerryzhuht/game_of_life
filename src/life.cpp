#include <iostream>
#include "console.h"
#include <simpio.h>
#include <grid.h>
#include <string>
#include <filelib.h>
#include <fstream>
#include <strlib.h>
#include <vector.h>
#include <algorithm>
#include <unistd.h>

using namespace std;

string checkATQ();
Grid<string> growGrid(Grid<string> g);
int checkFRM();
Grid<string> loadfile();


int main() {
    // Rules
    cout << "Welcome to the CS 106B/X Game of Life!" << endl;
    cout << "This program simulates the lifecycle of a bacterial colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "* A cell with 1 or fewer neighbors dies." << endl;
    cout << "* Locations with 2 neighbors remain stable." << endl;
    cout << "* Locations with 3 neighbors will create life." << endl;
    cout << "* A cell with 4 or more neighbors dies." << endl;
    cout << endl;

    while(true){
        Grid<string> gameboard = loadfile();
        //string answer = my_answer();
        //cout << answer << endl;

        while (true){
            string answer = checkATQ();
            if (answer == "t" || answer == "T"){
                gameboard = growGrid(gameboard);
            }

            if (answer == "a"|| answer == "A"){
                int frame = checkFRM();
                for (int i=0; i<frame;i++){
                    gameboard = growGrid(gameboard);
                    usleep(100);
                }
            }
            if (answer == "q"){
               break;
            }
        }
        if (!getYesOrNo("Load another file? (y/n)")){
            cout << "Have a nice Life!" << endl;
            break;
        }
    }
    return 0;

}

Grid<string> loadfile(){
    ifstream infile;
    promptUserForFile(infile, "Grid input file name?");
    // Generate grid
    // exclude word outside the bound
    string row_num_str;
    getline(infile, row_num_str);
    int row_num = stringToInteger(row_num_str);
    string col_num_str;
    getline(infile, col_num_str);
    int col_num = stringToInteger(col_num_str);

    Grid<string> gameboard(row_num,col_num);
    string line;
    for (int r=0; r<row_num; r++){
        getline(infile, line);
        for (int c=0; c<col_num; c++){
            gameboard[r][c] = line.at(c);
            cout << gameboard[r][c] << "";
        }
        cout << endl;
    }
    infile.close();
    return gameboard;
}

string checkATQ(){
    Vector<string> choice_vec {"A","a","T","t","Q","q"};
    string value;
    while (true){
        string choice = getLine("a)nimate, t)ick, q)uit");
        if (find(choice_vec.begin(), choice_vec.end(), choice) != choice_vec.end()){
            value = choice;
            break;
        }
        cout<<"Invalid choice; please try again."<<endl;
    }
    return value;
}

Grid<string> growGrid(Grid<string> g){
    clearConsole();
    Grid<string> newG (g.numRows(),g.numCols());
    for (int r=0; r<g.numRows(); r++){
        for (int c=0; c<g.numCols(); c++){
            if (countNeighbours(r,c,g) <= 1) {
                newG[r][c] = "-";
            }
            if (countNeighbours(r,c,g) == 2) {
                newG[r][c] = newG[r][c];
            }

            if (countNeighbours(r,c,g) == 3) {
                newG[r][c] = "X";
            }
            if (countNeighbours(r,c,g) > 3) {
                newG[r][c] = "-";
            }
            cout << newG[r][c] <<"";
        }
        cout << endl;
    }
    return newG;
}

int checkFRM(){
    int value = getInteger("How many frames?");
    return value;
}


int countNeighbours(int r, int c, Grid<string> g){//r, c are the row and column number of the cell, num_row and num_col are the size the grid
    int numAlive = 0;
    int numRows = g.numRows();
    int numCols = g.numCols();
    for (int row = (r-1+numRows)%numRows; row < (r+2+numRows)%numRows; row ++ ) {
        for (int column = (c-1+numCols)%numCols; column < (col+2)%numCols; column ++) {
            if ((grid(row)(column) == "X"));
                    numAlive += 1;
        }
    }
    return numAlive;
}



