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
#include "lifegui.h"

using namespace std;

string checkATQ();
Grid<string> growGrid(Grid<string> g);
int checkFRM();
Grid<string> loadfile();
int countNeighbours(int r, int c, Grid<string> g);


int main() {
    // Rules
    cout << "Welcome to the Game of Life!" << endl;
    cout << "This program simulates the lifecycle of a bacterial colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "* A cell with 1 or fewer neighbors dies." << endl;
    cout << "* Locations with 2 neighbors remain stable." << endl;
    cout << "* Locations with 3 neighbors will create life." << endl;
    cout << "* A cell with 4 or more neighbors dies." << endl;
    cout << endl;

    while(true){
        LifeGUI::initialize();
        Grid<string> gameboard = loadfile();

        while (true){
            string answer = checkATQ();
            if (answer == "t" || answer == "T"){
                LifeGUI::clear();
                gameboard = growGrid(gameboard);
            }

            if (answer == "a"|| answer == "A"){
                int frame = checkFRM();
                for (int i=0; i<frame;i++){
                    LifeGUI::clear();
                    gameboard = growGrid(gameboard);
                    //usleep(100);
                }
            }
            if (answer == "q"|| answer == "Q"){
               break;
            }
        }
        if (!getYesOrNo("Load another file? (y/n)")){
            cout << "Have a nice Life!" << endl;
            LifeGUI::shutdown();
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

    LifeGUI::resize(row_num, col_num);

    Grid<string> gameboard(row_num,col_num);
    string line;
    for (int r=0; r<row_num; r++){
        getline(infile, line);
        for (int c=0; c<col_num; c++){
            gameboard[r][c] = line.at(c);
            if(gameboard[r][c] == "X"){
                LifeGUI::fillCell(r, c);
            }
            cout << gameboard[r][c] << "";
        }
        cout << endl;
    }
    infile.close();
    LifeGUI::repaint();
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
    int numRows = g.numRows();
    int numCols = g.numCols();
    //LifeGUI::resize(numRows, numCols);
    Grid<string> newG (numRows,numCols);
    for (int r=0; r<numRows; r++){
        for (int c=0; c<numCols; c++){
            int numNeighbour =countNeighbours(r,c,g);
            if (numNeighbour <= 1) {
                newG[r][c] = "-";
            }
            if (numNeighbour == 2) {
                newG[r][c] = g[r][c];
            }

            if (numNeighbour == 3) {
                newG[r][c] = "X";
            }
            if (numNeighbour > 3) {
                newG[r][c] = "-";
            }
            cout << newG[r][c] <<"";
            if(newG[r][c] == "X"){
                LifeGUI::fillCell(r, c);
            }
        }
        cout << endl;
        LifeGUI::repaint();
    }
    return newG;
}

int checkFRM(){
    int value = getInteger("How many frames?");
    return value;
}


int countNeighbours(int r, int c, Grid<string> g){
    int numAlive = 0;
    if (g[r][c] == "X"){
        numAlive -= 1;
    }
    int numRows = g.numRows();
    int numCols = g.numCols();
    Vector<int> row_vec {(r-1+numRows)%numRows, r , (r+1+numRows)%numRows};
    Vector<int> col_vec {(c-1+numCols)%numCols, c , (c+1+numCols)%numCols};

    for (int i=0 ; i<3; i++){
        for (int j=0 ; j<3; j++){
            if (g[row_vec[i]][col_vec[j]] == "X"){
                numAlive += 1;
            }
        }
    }
    return numAlive;
}



