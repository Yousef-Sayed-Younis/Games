#include <ctime>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

char MATRIX[10], PLAYER, POS, COMPUTER;

void startMatrix() {
    for (char i = '1'; i <= '9'; i++) MATRIX[i - 48] = i;
}

void board() {
    system("cls");

    for (int i = 1; i <= 7; i += 3)
        cout << "| " << MATRIX[i] << " | " << MATRIX[i + 1] << " | " << MATRIX[i + 2] << " |\n";
}

void playNow(bool playWithComputer = false) {
    cout << "\nEnter Your Position (" << PLAYER << "): ";
    cin >> POS;

    if (POS < '1' or POS > '9') {
        cout << "Invalid Input, It's Out of Range";
        return playNow(playWithComputer);
    }

    char matrixPos = MATRIX[POS - 48];
    if (matrixPos == 'X' or matrixPos == 'O') {
        cout << "This Position is Occupied!, Please Enter Another Number";
        return playNow(playWithComputer);
    }

    MATRIX[POS - 48] = PLAYER;

    if (not playWithComputer) PLAYER = (PLAYER == 'X') ? 'O' : 'X';
}

char whoWon() {
    // check the rows
    for (int i = 1; i <= 7; i += 3)
        if ((MATRIX[i] == MATRIX[i + 1]) and (MATRIX[i + 1] == MATRIX[i + 2])) return MATRIX[i + 1];

    // check the columns
    for (int i = 1; i <= 3; i++)
        if ((MATRIX[i] == MATRIX[i + 3]) and (MATRIX[i + 3] == MATRIX[i + 6])) return MATRIX[i + 3];

    // check the  diagonal
    if (((MATRIX[1] == MATRIX[5]) and (MATRIX[5] == MATRIX[9])) or ((MATRIX[3] == MATRIX[5]) and (MATRIX[5] == MATRIX[7]))) return MATRIX[5];

    // continue the game
    for (int i = 1; i <= 9; i++)
        if (MATRIX[i] != 'X' and MATRIX[i] != 'O') return '*';
        
    // Draw
    return '=';
}

bool canChoose(char POS) {
    return (POS != 'X' and POS != 'O');
}

int canWin() {
    // check the rows
    for (int i = 1; i <= 7; i += 3) {
        if ((MATRIX[i] == MATRIX[i + 1]) and canChoose(MATRIX[i + 2])) return i + 2;
        else if ((MATRIX[i + 2] == MATRIX[i + 1]) and canChoose(MATRIX[i])) return i;
        else if ((MATRIX[i + 2] == MATRIX[i]) and canChoose(MATRIX[i + 1])) return i + 1;
    }

    // check the columns
    for (int i = 1; i <= 3; i++) {
        if ((MATRIX[i] == MATRIX[i + 3]) and canChoose(MATRIX[i + 6])) return i + 6;
        else if ((MATRIX[i + 6] == MATRIX[i + 3]) and canChoose(MATRIX[i])) return i;
        else if ((MATRIX[i] == MATRIX[i + 6]) and canChoose(MATRIX[i + 3])) return i + 3;
    }

    // check the diagonal
    if ((MATRIX[1] == MATRIX[5]) and canChoose(MATRIX[9])) return 9;
    else if ((MATRIX[1] == MATRIX[9]) and canChoose(MATRIX[5])) return 5;
    else if ((MATRIX[9] == MATRIX[5]) and canChoose(MATRIX[1])) return 1;
    if ((MATRIX[3] == MATRIX[5]) and canChoose(MATRIX[7])) return 7;
    else if ((MATRIX[3] == MATRIX[7]) and canChoose(MATRIX[5])) return 5;
    else if ((MATRIX[7] == MATRIX[5]) and canChoose(MATRIX[3])) return 3;

    // check a play that makes two chances to win
    if ((MATRIX[2] == MATRIX[4]) and canChoose(MATRIX[1])) return 1;
    else if ((MATRIX[2] == MATRIX[6]) and canChoose(MATRIX[3])) return 3;
    if ((MATRIX[2] == MATRIX[7]) and canChoose(MATRIX[1])) return 1;
    else if ((MATRIX[2] == MATRIX[9]) and canChoose(MATRIX[3])) return 3;
    if ((MATRIX[8] == MATRIX[4]) and canChoose(MATRIX[7])) return 7;
    else if ((MATRIX[8] == MATRIX[6]) and canChoose(MATRIX[9])) return 9;    
    if ((MATRIX[8] == MATRIX[1]) and canChoose(MATRIX[7])) return 7;
    else if ((MATRIX[8] == MATRIX[3]) and canChoose(MATRIX[9])) return 9;    

    return -1;
}

void AI() {       
    // Pos 5 is important and Strong in XO
    // If you loose it, you can't win with diagonals
    // So We Want to Take it as We Could
    if (MATRIX[5] == '5') {MATRIX[5] = COMPUTER; return;}
    else if (MATRIX[5] == PLAYER and MATRIX[1] == '1') {MATRIX[1] = COMPUTER; return;}

    int position = canWin();
    if (position != -1) MATRIX[position] = COMPUTER; return;
    
    for (int i = 1; i <= 9; i++)
        if (canChoose(MATRIX[i])) {MATRIX[i] = COMPUTER; return;}       
}

int main() {
    char comp = 'y';
    cout << "Welcome to Tic Tac Toe.\n";

    while (comp == 'y') {
        startMATRIX();
        cout << "Do You Want to Play with a Computer? (y, n): ";

        char choose;
        cin >> choose;
        if (choose == 'y') {
            cout << "Choose What Do You Want to Play with: (X, O): ";
            cin >> PLAYER;

            if (PLAYER == 'X' or PLAYER == 'x') PLAYER = 'X', COMPUTER = 'O';
            else PLAYER = 'O', COMPUTER = 'X';

            while (whoWon() == '*') board(), playNow(true), AI();
            
            board();

            char winner = whoWon();
            if (winner == PLAYER) cout << "\nYou Win!!";
            else if (winner == COMPUTER) cout << "\nThe Winner is the Computer :P";
            else if (winner == '=') cout << "\nNo Winner";

            cout << "\nDo You Want to Play Again? (y, n): ";
            cin >> comp;

            if (comp == 'y') system("cls");

        } else {
            cout << "Which Player Want to Begin? (X, O): ";
            cin >> PLAYER;

            if (PLAYER == 'X' or PLAYER == 'x') PLAYER = 'X';
            else PLAYER = 'O';

            while (whoWon() == '*') board(), playNow(), whoWon();

            board();

            char winner = whoWon();
            if (winner == '=') cout << "\nNo Winner";
            else cout << "\nThe Winner is the Player " << winner;

            cout << "\nDo You Want to Play Again? (y, n): ";
            cin >> comp;

            if (comp == 'y') system("cls");
        }
    }

    return 0;
}
