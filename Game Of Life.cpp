#include <iostream>
#include <time.h>  //for using random function for initial seed
#include <windows.h> //for using sleep function
using namespace std;

const int gridSize = 25;

//function prototypes
int randNum();                                                                                          //random 1 or 0
void firstState(bool grid[gridSize + 1][gridSize + 1]);                                                 //populates the first seed
void gridDisplay(bool grid[gridSize + 1][gridSize + 1]);                                                //generates the grid
void copyGrid(bool grid[gridSize + 1][gridSize + 1], bool grid2[gridSize + 1][gridSize + 1]);           //makes a copy of the grid
void nextState(bool grid[gridSize + 1][gridSize + 1]);                                                  //populates the future seeds
bool checkForLife(bool grid[gridSize + 1][gridSize + 1]);                                               //checks for life


int main() {
    srand(time(NULL));

    bool grid[gridSize + 1][gridSize + 1] = {};

    int gen = 1;        //tracks the generation
    bool lives = true;  //tracks life

    firstState(grid);
    nextState(grid);

    //if population stabalises then it will continue to run
    //loop will run until no life remains
      
    while (lives == true) {  
        

        gridDisplay(grid);      //Displays first generation
        nextState(grid);        //calculate if it lives or dies
        cout << "Generation = " << gen << endl;
        gen = gen + 1;


        if (checkForLife(grid) == true){
            lives = true;
        }
        else{
            lives = false;
        }

        //system("PAUSE"); //for testing purposes 
        Sleep(200);
        system("CLS");

    }

    
    cout << "All life is dead!" << endl; 
}


//returns either a 1 or 0 at random this can be adjusted to determine the chance of life at the start
int randNum() {
    int a = rand() % 2;
    return a;
}


//declares the first states of the cells either dead or alive
void firstState(bool grid[gridSize + 1][gridSize + 1]) {
    for (int a = 1; a < gridSize; a++) {
        for (int b = 1; b < gridSize; b++) {
            if (randNum() == 0)

                grid[a][b] = true;
        }
    }
}


//diplays the new iteration of the grid
void gridDisplay(bool grid[gridSize + 1][gridSize + 1]) {
    for (int a = 1; a < gridSize; a++) {
        for (int b = 1; b < gridSize; b++) {
            if (grid[a][b] == true) {
                cout << " X ";
            }
            else {
                cout << "   ";
                              
            }
                if (b == gridSize - 1) {
                    cout << endl;
                
            }
        }
    }
}

//Makes copy of the grid 
void copyGrid(bool grid[gridSize + 1][gridSize + 1], bool grid2[gridSize + 1][gridSize + 1]) {
    for (int a = 0; a < gridSize; a++) {
        for (int b = 0; b < gridSize; b++) { grid2[a][b] = grid[a][b]; }
    }
}

//Using a copy of the grid determines what the next state of the cells are
void nextState(bool grid[gridSize + 1][gridSize + 1]) {
  
    bool grid2[gridSize + 1][gridSize + 1] = {};
    int life;


    copyGrid(grid, grid2);

    for (int a = 1; a < gridSize; a++) {

        for (int b = 1; b < gridSize; b++) {

            life = 0;


          
            for (int c = -1; c < 2; c++) {

                for (int d = -1; d < 2; d++) {

                    if ((d != 0) && (c != 0)) {

                        if (grid2[a + c][b + d] == true){

                            life = life + 1;

                        }
                    }
                
                }
            }

            if (grid2[a][b] == false) {

                if (life == 3) {

                    grid[a][b] = true;
                }

            }
            else if (grid2[a][b] == true) {

                if (life < 2) {

                    grid[a][b] = false; //underpopulation
                }
                else if (life > 3) {

                    grid[a][b] = false; //overpopulation
                }
                else {

                    grid[a][b] = true; //stable
                }

            }   
        }
    }
}


//checks to see if the grid still contains life if not will end the program
bool checkForLife(bool grid[gridSize + 1][gridSize + 1]) {

    int deaths = 0;



    for (int a = 1; a < gridSize + 1; a++) {

        for (int b = 1; b < gridSize + 1; b++) {

            if (grid[a][b] == true) {

                return true;

            }
            else {

                deaths = deaths + 1;
            }
        }
    }

    if (deaths == (gridSize * gridSize)) {

        return false;
    }

}