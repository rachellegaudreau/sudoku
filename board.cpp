#include <iostream>
#include <iomanip>
#include "board.h"
#include "move.h"
#define RESET       "\033[0m"
#define BRIGHT_BLUE "\033[94m"
#define CYAN        "\033[96m"

using namespace std;

Board::Board() {
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c) {
            grid[r][c] = 0;
            fixed[r][c] = false;
        }
}

void Board::loadPuzzle(const string& puzzleStr) {
    for (int i = 0; i < 81; ++i) {
        int r = i / 9;
        int c = i % 9;
        char ch = puzzleStr[i];
        if (ch >= '1' && ch <= '9') {
            grid[r][c] = ch - '0';
            fixed[r][c] = true;
        } else {
            grid[r][c] = 0;
            fixed[r][c] = false;
        }
    }
}

void Board::display() {
    cout << "   1 2 3   4 5 6   7 8 9\n";
    cout << "  ------+-------+------\n";
    for (int r = 0; r < 9; ++r) {
        // Print row label (A-I)
        cout << static_cast<char>('A' + r) << "  ";

        for (int c = 0; c < 9; ++c) {
            // '.' for empty cell
            if (grid[r][c] == 0) {
                cout << ".";
            }
            // fixed numbers
            else if (fixed[r][c]) {
              cout << CYAN << grid[r][c] << RESET;
            }
            // user input numbers
            else {
              cout <<BRIGHT_BLUE <<grid[r][c]<<RESET;
            }

            if ((c + 1) % 3 == 0 && c != 8) cout << " | ";
            else cout << " ";
        }

        cout << "\n";
        if ((r + 1) % 3 == 0) {
            cout << "   ------+-------+------\n";
        }
    }
}

bool Board::placeNumber(int r, int c, int val) {
    if (fixed[r][c]) return false;
    if (!isValidMove(grid, r, c, val)) return false;

    grid[r][c] = val;
    moves.addMove(r, c, val);
    return true;
}

void Board::removeNumber(int row, int col) {
    if (!fixed[row][col]) {
        grid[row][col] = 0;
    }
}

bool Board::isComplete() {
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            if (grid[r][c] == 0)
                return false;
    return true;
}
