//
//  playMove.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <tic-tac-toe/playMove.h>

using namespace std;

void playMove(int board[3][3], int row, int col, bool& turn, bool& validMove, bool& gameOver, int& winCode)
 {

    // If the game is over, do nothing
    if (gameOver) return;

    // Insert your code here
    if (board[col][row] == (Empty)) {
        validMove = true; //move is valid 
        if (turn == true) {
            board[col][row] = 1; //X begins by default
            turn = false; //switches to O
        } else if (turn == false) {
            board[col][row] = -1; //O's turn
            turn = true; //next turn will be X's
        }
    }
    else {
        validMove = false;
    }

    //WIN CODES
    if (board[0][0] + board[1][0] + board[2][0] == 3 || board[0][0] + board[1][0] + board[2][0] == -3)// horizontal line across the top
        winCode = 1;

    else if (board[0][1] + board[1][1] + board[2][1] == 3 || board[0][1] + board[1][1] + board[2][1] == -3) //2nd row
        winCode = 2;

    else if (board[0][2] + board[1][2] + board[2][2] == 3 || board[0][2] + board[1][2] + board[2][2] == -3) // 3rd row
        winCode = 3;

    else if (board[0][0] + board[0][1] + board[0][2] == 3 || board[0][0] + board[0][1] + board[0][2] == -3) //first col
        winCode = 4;

    else if (board[1][0] + board[1][1] + board[1][2] == 3 || board[1][0] + board[1][1] + board[1][2] == -3) //second col
        winCode = 5;

    else if (board[2][0] + board[2][1] + board[2][2] == 3 || board[2][0] + board[2][1] + board[2][2] == -3) //third col
        winCode = 6;

    else if (board[0][0] + board[1][1] + board[2][2] == 3 || board[0][0] + board[1][1] + board[2][2] == -3) //diagonal from top left to bottom right
        winCode = 7;

    else if (board[0][2] + board[1][1] + board[2][0] == 3 || board[0][2] + board[1][1] + board[2][0] == -3) //diagonal from top right to bottom left
        winCode = 8;

    else winCode = 0; //no win! 

    if (winCode != 0) {
        gameOver = true; //someone won, game over!
    }

    int count;
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            cout << board[j][i] << " ";

            if (board[i][j] != Empty) {
                count = count + 1;
            }

            if (count == 9) { // Total count of Xs/Os on board add up to 9 if board is full
                gameOver = true; // In which case, no more moves are valid and gameOver is set to true
            }

        }
    }

    // The function must always print the output specified in the handout before it exits
    // Use the standard output (i.e., cout) to print the output
    // Insert code to print the output below


    cout << row << " " << col << " ";

    cout << turn << " ";

    cout << validMove << " ";

    cout << gameOver << " ";

    cout << winCode << endl;

}
