
#include <iostream>
#include <string>
#include <cstdlib>          // for system()
#include <windows.h>        // for console colors
#include "Member1_Pieces.h" // need piece classes
#include "Member2_Board.h"  // need board class 
using namespace std;

inline void uiColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
inline void uiReset() {
    uiColor(0x07);
}

// PLAYER CLASS
class Player {
private:
    string name;
    int playerNum;
    int score;

public:
    Player(string n, int num) {
        name = n;
        playerNum = num;
        score = 0;
    }

    string getName() { return name; }
    int    getNum() { return playerNum; }
    int    getScore() { return score; }
    void   addScore() { score++; }
};

// HELPER FUNCTION
// Converts input like "e2" to row and column numbers
bool parseInput(string input, int& row, int& col) {
    if (input.length() < 2)
        return false;

    char colChar = input[0];  // letter a-h
    char rowChar = input[1];  // number 1-8

    // convert column letter to index
    if (colChar >= 'a' && colChar <= 'h')
        col = colChar - 'a';
    else if (colChar >= 'A' && colChar <= 'H')
        col = colChar - 'A';
    else
        return false;

    // convert row number to array index
    if (rowChar >= '1' && rowChar <= '8')
        row = 8 - (rowChar - '0');  // flip because row 8 is index 0
    else
        return false;

    return true;
}

// function  welcome screen
void showTitle() {
    system("cls");
    uiColor(0x0E);
    cout << endl;
    cout << "                                             " << endl;
    cout << "               CHESS GAME          " << endl;
    cout << "        Object Oriented Programming         " << endl;
    cout << endl;
    uiReset();

    uiColor(0x0C);
    cout << "  Player 1 controls RED pieces (bottom)" << endl;
    uiColor(0x0A);
    cout << "  Player 2 controls GREEN pieces (top)" << endl;
    cout << endl;
    uiReset();

    uiColor(0x0F);
    cout << "  HOW TO PLAY:" << endl;
    cout << "   Enter position like: e2  (column then row)" << endl;
    cout << "   First enter the piece you want to move" << endl;
    cout << "   Then enter where you want to move it" << endl;
    cout << endl;
    cout << "  PIECE SYMBOLS:" << endl;
    cout << "  K = King   Q = Queen  R = Rook" << endl;
    cout << "  B = Bishop N = Knight P = Pawn" << endl;
    cout << endl;
    uiReset();
}

// MAIN FUNCTION
int main() {
    showTitle();

    //  player names
    string name1, name2;
    uiColor(0x0C);
    cout << "  Enter Player 1 name (red): ";
    uiReset();
    cin >> name1;

    uiColor(0x0A);
    cout << "  Enter Player 2 name (green): ";
    uiReset();
    cin >> name2;

    // player objects
    Player p1(name1, 1);
    Player p2(name2, 2);

    Board board;

    int currentPlayer = 1;
    bool gameOver = false;
    int winner = 0;

    // main loop
    while (!gameOver) {
        // display the board
        board.displayBoard();

        // show turn
        if (currentPlayer == 1) {
            uiColor(0x0C);
            cout << "   *** " << p1.getName() << "'s turn (red/Player 1) ***" << endl;
        }
        else {
            uiColor(0x0A);
            cout << "   *** " << p2.getName() << "'s turn (green/Player 2) ***" << endl;
        }
        uiReset();

        cout << endl;

        // getting input from player
        string fromPos, toPos;
        int r1, c1, r2, c2;

        cout << "   Enter piece position (e.g. e2): ";
        cin >> fromPos;

        // parse the from position
        if (!parseInput(fromPos, r1, c1)) {
            uiColor(0x0C);
            cout << "   Invalid input! Please use format like e2 or a1" << endl;
            uiReset();
            system("pause");
            continue;
        }

        cout << "   Enter move position  (e.g. e4): ";
        cin >> toPos;

        // parse the to position
        if (!parseInput(toPos, r2, c2)) {
            uiColor(0x0C);
            cout << "   Invalid input! Please use format like e4 or a3" << endl;
            uiReset();
            system("pause");
            continue;
        }

        // try to move the piece
        int result = board.movePiece(r1, c1, r2, c2, currentPlayer);

        if (result == 0) {
            // invalid move
            system("pause");
            continue;
        }
        else if (result == 2) {
            // king was captured
            board.displayBoard();
            gameOver = true;
            winner = currentPlayer;
        }
        else {
            // valid move switch turns
            if (currentPlayer == 1)
                currentPlayer = 2;
            else
                currentPlayer = 1;
        }
    }

    system("cls");
    uiColor(0x0E);
    cout << endl;
    cout << "              GAME OVER!                 " << endl;
    cout << endl;
    uiReset();

    if (winner == 1) {
        uiColor(0x0A);
        cout << "   *** " << p1.getName() << " (GREEN) WINS! Congratulations! ***" << endl;
    }
    else {
        uiColor(0x0C);
        cout << "   *** " << p2.getName() << " (RED) WINS! Congratulations! ***" << endl;
    }

    uiReset();
    cout << endl;
    cout << "  Final Scores:" << endl;
    cout << "  " << p1.getName() << ": " << p1.getScore() << " wins" << endl;
    cout << "  " << p2.getName() << ": " << p2.getScore() << " wins" << endl;
    cout << endl;

    system("pause");
    return 0;
}