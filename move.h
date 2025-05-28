#ifndef MOVE_H
#define MOVE_H
#include <iostream>
using namespace std; 

struct Move{
    int row, col, val;
    Move* next;
};

class MoveList{
    private:
        Move* head;
    public: 
        MoveList();
        void addMove(int r, int c, int v);
        bool undoMove(int & r, int & c, int & v);
        ~MoveList();
        void clear();
};

bool isValidMove(const int grid[9][9], int r, int c, int val);

#endif
