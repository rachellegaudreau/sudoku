#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cctype>
#include <thread>
#include <chrono>
#include <limits>
#include "board.h"
#include "move.h"
#include "puzzles.h"

#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define MBLUE   "\033[94m" // main blue
using namespace std;


void dramaticPause() {
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    cout << "\n";
}

void printBorder(){
    // border
        cout << MBLUE<< R"(
.--.      .-'.      .--.      .--.      .--.      .--.
:::::.\::::::::.\::::::::.\::::::::.\::::::::.\:::::::.\
'      `--'      `.-'      `--'      `--'      `--'      `
)" << RESET <<endl;
}

void splashScreen() {
    cout << MBLUE << R"(
           _____           __    
          / ___/__  ______/ /___ 
          \__ \/ / / / __  / __ \
         ___/ / /_/ / /_/ / /_/ /
        /____/\____/\____/\____/  
                                
            TERMINAL SUDOKU GAME
        ~ The logic awakens within you ~
    )" << RESET <<endl;
    dramaticPause();
    printBorder();
}

void choosePuzzle(Board& board){
    string choice;
    cout << "Choose your challenge:\n";
    cout << "  1. " << GREEN << "Easy" << RESET << endl;
    cout << "  2. " << YELLOW << "Medium" << RESET << endl;
    cout << "  3. " << RED << "Hard" << RESET << endl;
    cout << "  4. " << BLUE << "ULTRA MODE" << RESET << endl;
    cout << "Enter 1-4: ";
    cin >> choice;
    cin.ignore(10, '\n');

    if (choice == "1") board.loadPuzzle(easyPuzzle);
    else if (choice == "2") board.loadPuzzle(mediumPuzzle);
    else if (choice == "3") board.loadPuzzle(hardPuzzle);
    else if (choice == "4") {
        cout << "You have chosen"; dramaticPause();
        cout << "poorly." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Just kidding." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "GOOD LUCK!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        board.loadPuzzle(ultraGodPuzzle);
    } else {
        cout << "Invalid choice. Defaulting to Easy mode.\n";
        board.loadPuzzle(easyPuzzle);
    }
    printBorder();
}

int main() {
    int tries = 0;
    bool quitGame = false;
    char rowChar;
    int colNum, val;
    MoveList moveList;
    Board board;

    splashScreen();
    choosePuzzle(board);

    while (!board.isComplete()) {
        board.display();
        string inputLine;
        cout << "\nEnter your move (e.g. B3 9) 'q' to exit, 'undo' to undo: ";
        getline(cin, inputLine);

        // convert to lower case
        string lowerInput = inputLine;
        for (auto& c : lowerInput) c = tolower(c);

        // quit
        if (lowerInput == "quit" || lowerInput == "q") {
          quitGame = true;
          cout<< "Goodbye!"<<endl;
            break;
        }

        // undo
        if (inputLine == "undo") {
            int r, c, v;
            if (moveList.undoMove(r, c, v)) {
                board.removeNumber(r, c);
                cout << "\033[35mMove undone!\033[0m The past trembles..."<<endl;
            } else {
                cout << "Nothing to undo!"<<endl;
            }
            continue;
        }

        istringstream iss(inputLine);
        if (!(iss >> rowChar >> colNum >> val)) {
            cout << "Invalid input format. Try again." << endl\
;
            continue;
        }

        int row = static_cast<int>(toupper(rowChar) - 'A');
        int col = colNum - 1;

        if (row < 0 || row >= 9 || col < 0 || col >= 9 || val < 1 || val > 9) {
            cout << "Invalid input! Try again."<<endl;
            continue;
        }

        tries++;
        if (!board.placeNumber(row, col, val)) {
            cout << "That number doesn't fit. Try again." <<endl;
        } else {
            moveList.addMove(row, col, val);
            cout << "Nice move! You're cooking!" <<endl;
        }
        cout << RED << "Attempt: " << tries << RESET <<endl;
        if (tries == 50) {
            cout << "Wow, you really took your time... But hey I'm sure you'll get it some day!\n";
        }
        printBorder();
    }

    if(!quitGame){
      cout << "SUCCESS!"<<endl;
      cout << BLUE << R"(
      
 __   __  _______  __   __    _     _  ___   __    _  __  
|  | |  ||       ||  | |  |  | | _ | ||   | |  |  | ||  | 
|  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| ||  | 
|       ||  | |  ||  |_|  |  |       ||   | |       ||  | 
|_     _||  |_|  ||       |  |       ||   | |  _    ||__| 
  |   |  |       ||       |  |   _   ||   | | | |   | __  
  |___|  |_______||_______|  |__| |__||___| |_|  |__||__| 

)" << RESET <<endl;
    }
    return 0;
}
