IMplemented pawan logic
#ifndef MEMBER1_PIECES_H    
#define MEMBER1_PIECES_H

#include <iostream>
using namespace std;

// BASE CLASS
class Piece {
protected:
    char symbol;
    int color;
    int row;
    int col;
    bool alive;     //  check is piece still on board

public:
    // constructor
    Piece(char sym, int clr, int r, int c) {
        symbol = sym;
        color = clr;
        row = r;
        col = c;
        alive = true;
    }

    // getter functions
    char getSymbol() {
        return symbol;
    }
    int getColor() {
        return color;
    }
    int getRow() {
        return row;
    }
    int getCol() {
        return col;
    }
    bool isAlive() {
        return alive;
    }

    // setter functions
    void setRow(int r) {
        row = r;
    }
    void setCol(int c) {
        col = c;
    }
    void setAlive(bool a) {
        alive = a;
    }

    // virtual function  every piece will override this
    // checks if move from (r1,c1) to (r2,c2) is valid
    virtual bool validMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) = 0;

    // virtual destructor
    virtual ~Piece() {}
};

// PAWN CLASS
// Pawn moves forward 1 step, first move can be 2 steps

class Pawn : public Piece {
public:
    Pawn(int clr, int r, int c) : Piece('P', clr, r, c) {}

    
    bool validMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
        int direction;

        // white moves up , black moves down 
        if (color == 1)
            direction = -1;  // white goes up
        else
            direction = 1;   // black goes down

        // normal 1 step forward
        if (c1 == c2 && r2 == r1 + direction) {
            if (board[r2][c2] == NULL)
                return true;
        }

        // first move can go 2 steps forward
        if (c1 == c2 && r2 == r1 + 2 * direction) {
            // check if pawn is at starting position
            if ((color == 1 && r1 == 6) || (color == 2 && r1 == 1)) {
                // both squares must be empty
                if (board[r2][c2] == NULL && board[r1 + direction][c1] == NULL)
                    return true;
            }
        }

        // diagonal
        if ((c2 == c1 + 1 || c2 == c1 - 1) && r2 == r1 + direction) {
            if (board[r2][c2] != NULL && board[r2][c2]->getColor() != color)
                return true;
        }

        return false;
    }
};

// ROOK CLASS
// Rook moves in straight lines
class Rook : public Piece {
public:
    Rook(int clr, int r, int c) : Piece('R', clr, r, c) {}

    // checking valid move for rook
    bool validMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
        // rook must move in straight line
        if (r1 != r2 && c1 != c2)
            return false;

        // check if moving horizontally
        if (r1 == r2) {
            int start = min(c1, c2);
            int end = max(c1, c2);
            // check all squares between start and end are empty
            for (int i = start + 1; i < end; i++) {
                if (board[r1][i] != NULL)
                    return false;
            }
        }

        // check if moving vertically
        if (c1 == c2) {
            int start = min(r1, r2);
            int end = max(r1, r2);
            for (int i = start + 1; i < end; i++) {
                if (board[i][c1] != NULL)
                    return false;
            }
        }

        // destination must be empty 
        if (board[r2][c2] == NULL || board[r2][c2]->getColor() != color)
            return true;

        return false;
    }
};

// KNIGHT CLASS
// Knight moves in L-shape
class Knight : public Piece {
public:
    Knight(int clr, int r, int c) : Piece('N', clr, r, c) {}

    // checking valid move for knight
    bool validMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
        int rdiff = abs(r2 - r1);
        int cdiff = abs(c2 - c1);

        // knight moves in L shape
        if (!((rdiff == 2 && cdiff == 1) || (rdiff == 1 && cdiff == 2)))
            return false;

        // destination must be empty 
        if (board[r2][c2] == NULL || board[r2][c2]->getColor() != color)
            return true;

        return false;
    }
};

// BISHOP CLASS
// Bishop moves diagonally any number of squares
class Bishop : public Piece {
public:
    Bishop(int clr, int r, int c) : Piece('B', clr, r, c) {}

    // checking valid move for bishop
    bool validMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
        int rdiff = abs(r2 - r1);
        int cdiff = abs(c2 - c1);

        // bishop must move diagonally
        if (rdiff != cdiff)
            return false;

        // check if path is clear
        int rStep = (r2 > r1) ? 1 : -1;
        int cStep = (c2 > c1) ? 1 : -1;

        int r = r1 + rStep;
        int c = c1 + cStep;

        // check all squares in diagonal path
        while (r != r2 && c != c2) {
            if (board[r][c] != NULL)
                return false;  
            r += rStep;
            c += cStep;
        }

        // destination must be empty 
        if (board[r2][c2] == NULL || board[r2][c2]->getColor() != color)
            return true;

        return false;
    }
};

// QUEEN CLASS
// Queen combines Rook + Bishop moves
class Queen : public Piece {
public:
    Queen(int clr, int r, int c) : Piece('Q', clr, r, c) {}

    // checking valid move for queen
    bool validMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
        int rdiff = abs(r2 - r1);
        int cdiff = abs(c2 - c1);

        // check if moving like rook
        if (r1 == r2 || c1 == c2) {
            // horizontal check
            if (r1 == r2) {
                int start = min(c1, c2);
                int end = max(c1, c2);
                for (int i = start + 1; i < end; i++) {
                    if (board[r1][i] != NULL)
                        return false;
                }
            }
            // vertical check
            if (c1 == c2) {
                int start = min(r1, r2);
                int end = max(r1, r2);
                for (int i = start + 1; i < end; i++) {
                    if (board[i][c1] != NULL)
                        return false;
                }
            }
            if (board[r2][c2] == NULL || board[r2][c2]->getColor() != color)
                return true;
        }

        // check if moving like bishop
        if (rdiff == cdiff) {
            int rStep = (r2 > r1) ? 1 : -1;
            int cStep = (c2 > c1) ? 1 : -1;
            int r = r1 + rStep;
            int c = c1 + cStep;
            while (r != r2 && c != c2) {
                if (board[r][c] != NULL)
                    return false;
                r += rStep;
                c += cStep;
            }
            if (board[r2][c2] == NULL || board[r2][c2]->getColor() != color)
                return true;
        }

        return false;
    }
};

// KING CLASS
// King moves 1 square in any direction
class King : public Piece {
public:
    King(int clr, int r, int c) : Piece('K', clr, r, c) {}

    // checking valid move for king
    bool validMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
        int rdiff = abs(r2 - r1);
        int cdiff = abs(c2 - c1);

        // king can only move 1 square in any direction
        if (rdiff > 1 || cdiff > 1)
            return false;

        // cant stay in same place
        if (rdiff == 0 && cdiff == 0)
            return false;

        // destination must be empty or enemy piece
        if (board[r2][c2] == NULL || board[r2][c2]->getColor() != color)
            return true;

        return false;
    }
};

#endif 
