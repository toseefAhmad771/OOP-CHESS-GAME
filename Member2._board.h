

#ifndef MEMBER2_BOARD_H     
#define MEMBER2_BOARD_H

#include <iostream>
#include <windows.h>        //  console colors
#include <cstdlib>          //  system("cls")
#include "Member1_Pieces.h" //  all piece classes
using namespace std;

// COLOR CODES for Windows Console
// 0x0_ = black background
// 0xF_ = white background
// _0xC = bright red text
// _0xA = bright green text
// _0xE = yellow text

// --- Light square colors (white background = 0xF_) ---
#define P1_ON_WHITE   0xFC   // white bg + bright RED text   (Player 1 piece)
#define P2_ON_WHITE   0xFA   // white bg + bright GREEN text (Player 2 piece)
#define EMPTY_WHITE   0xF0   // white bg + black text        (empty light square)

// --- Dark square colors (black background = 0x0_) ---
#define P1_ON_BLACK   0x0C   // black bg + bright RED text   (Player 1 piece)
#define P2_ON_BLACK   0x0A   // black bg + bright GREEN text (Player 2 piece)
#define EMPTY_BLACK   0x00   // black bg + black text        (empty dark square)

// --- UI colors ---
#define COLOR_BORDER  0x0E   // yellow text for borders/labels
#define COLOR_P1_INFO 0x0C   // red   for Player 1 info line
#define COLOR_P2_INFO 0x0A   // green for Player 2 info line

// BOARD CLASS
class Board {
private:
    Piece* grid[8][8];
    int capturedW;
    int capturedB;

    //  to set console text color
    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    //  to reset console color back to default
    void resetColor() {
        setColor(0x07);
    }

public:
    Board() {
        // initialize grid to NULL
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                grid[i][j] = NULL;

        capturedW = 0;
        capturedB = 0;

        setupPieces();
    }

    // setting up all pieces
    void setupPieces() {
        // BLACK pieces  top of board
        grid[0][0] = new Rook(2, 0, 0);
        grid[0][1] = new Knight(2, 0, 1);
        grid[0][2] = new Bishop(2, 0, 2);
        grid[0][3] = new Queen(2, 0, 3);
        grid[0][4] = new King(2, 0, 4);
        grid[0][5] = new Bishop(2, 0, 5);
        grid[0][6] = new Knight(2, 0, 6);
        grid[0][7] = new Rook(2, 0, 7);

        // black pawns
        for (int i = 0; i < 8; i++)
            grid[1][i] = new Pawn(2, 1, i);

        // WHITE pieces  bottom of board
        grid[7][0] = new Rook(1, 7, 0);
        grid[7][1] = new Knight(1, 7, 1);
        grid[7][2] = new Bishop(1, 7, 2);
        grid[7][3] = new Queen(1, 7, 3);
        grid[7][4] = new King(1, 7, 4);
        grid[7][5] = new Bishop(1, 7, 5);
        grid[7][6] = new Knight(1, 7, 6);
        grid[7][7] = new Rook(1, 7, 7);

        // white pawns
        for (int i = 0; i < 8; i++)
            grid[6][i] = new Pawn(1, 6, i);
    }


    void displayBoard() {
        system("cls");  // clear screen

        cout << endl;

        setColor(COLOR_BORDER);
        cout << "       a  b  c  d  e  f  g  h" << endl;
        resetColor();

        // display each row
        for (int i = 0; i < 8; i++) {

            // row number on left side
            setColor(COLOR_BORDER);
            cout << "   " << (8 - i) << " ";
            resetColor();

            for (int j = 0; j < 8; j++) {

                // gives alternating pattern
                bool isLight = (i + j) % 2 == 0;

                if (grid[i][j] == NULL) {
                    // empty square
                    if (isLight)
                        setColor(EMPTY_WHITE);
                    else
                        setColor(EMPTY_BLACK);

                    cout << "   ";
                }
                else {
                    // if there is a piece on this square
                    Piece* p = grid[i][j];

                    if (p->getColor() == 1) {
                        // player 1 piece in bright red text
                        if (isLight)
                            setColor(P1_ON_WHITE);
                        else
                            setColor(P1_ON_BLACK);
                    }
                    else {
                        // player 2 piece show in bright green text
                        if (isLight)
                            setColor(P2_ON_WHITE);
                        else
                            setColor(P2_ON_BLACK);
                    }

                    cout << " " << p->getSymbol() << " ";
                }
            }

            // row number on right side
            setColor(COLOR_BORDER);
            cout << " " << (8 - i) << endl;
            resetColor();
        }

        // print column letters at bottom
        setColor(COLOR_BORDER);
        cout << "       a  b  c  d  e  f  g  h" << endl;
        resetColor();

        // show score
        cout << endl;
        setColor(COLOR_P1_INFO);
        cout << "   [Player 1 - RED  ] Pieces Captured: " << capturedW << endl;
        setColor(COLOR_P2_INFO);
        cout << "   [Player 2 - GREEN] Pieces Captured: " << capturedB << endl;
        resetColor();
        cout << endl;
    }

    // get piece at position
    Piece* getPiece(int r, int c) {
        return grid[r][c];
    }

    // move piece from one position to another
    int movePiece(int r1, int c1, int r2, int c2, int currentPlayer) {
        // check if source has a piece
        if (grid[r1][c1] == NULL) {
            cout << "   No piece at that position!" << endl;
            return 0;
        }

        Piece* p = grid[r1][c1];

        // check if piece belongs to current player
        if (p->getColor() != currentPlayer) {
            cout << "   That is not your piece!" << endl;
            return 0;
        }

        // check if destination is same as source
        if (r1 == r2 && c1 == c2) {
            cout << "   You didn't move anywhere!" << endl;
            return 0;
        }

        // check if destination is within board
        if (r2 < 0 || r2 > 7 || c2 < 0 || c2 > 7) {
            cout << "   Position out of board!" << endl;
            return 0;
        }

        // check if move is valid for this piece
        if (!p->validMove(r1, c1, r2, c2, grid)) {
            cout << "   Invalid move for this piece!" << endl;
            return 0;
        }

        // check if king is being captured
        int result = 1;
        if (grid[r2][c2] != NULL) {
            if (grid[r2][c2]->getSymbol() == 'K') {
                result = 2;
            }

            // update score
            if (grid[r2][c2]->getColor() == 2)
                capturedB++;
            else
                capturedW++;

            delete grid[r2][c2]; // remove captured piece
        }

        // moving the piece
        grid[r2][c2] = p;
        grid[r1][c1] = NULL;

        // update piece position
        p->setRow(r2);
        p->setCol(c2);

        return result;
    }

    // destructor - free memory
    ~Board() {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (grid[i][j] != NULL)
                    delete grid[i][j];
    }
};

#endif #pragma once
