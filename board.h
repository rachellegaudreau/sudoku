#ifndef BOARD_H
#define BOARD_H
#include "move.h"
using namespace std;

class Board{
    private: 
        int grid[9][9];
        bool fixed[9][9];
        MoveList moves;
    public: 
        Board();
        void loadPuzzle(const string& puzzleStr);
        void display();
        bool placeNumber(int r, int c, int val);
        void removeNumber(int r, int c);
        bool isComplete();
};

#endif
