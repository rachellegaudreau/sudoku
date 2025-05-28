#include "move.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

MoveList::MoveList():head(nullptr){}

void MoveList::addMove(int r, int c, int val){
    Move* newMove = new Move{r,c,val,head};
    head=newMove;
}

void MoveList::clear(){
    while (head != nullptr) {
        Move* temp = head;
        head = head->next;
        delete temp;
    }
}

bool MoveList::undoMove(int & row, int & col, int & val){
    // reverts last correct move
    if (!head) {
        return false;
    }
    row = head->row;
    col = head->col;
    val = head->val;

    Move* temp = head;
    head = head->next;
    delete temp;
    return true;
}

MoveList::~MoveList(){
  clear();
}

bool isValidMove(const int grid[9][9], int r, int c, int val){
    // Check row
    for (int col = 0; col < 9; ++col)
        if (grid[r][col] == val) return false;

    // Check column
    for (int row = 0; row < 9; ++row)
        if (grid[row][c] == val) return false;

    // Check 3x3 box
    int boxRow = (r / 3) * 3;
    int boxCol = (c / 3) * 3;
    for (int row = boxRow; row < boxRow + 3; ++row)
        for (int col = boxCol; col < boxCol + 3; ++col)
            if (grid[row][col] == val) return false;

    return true;
}

