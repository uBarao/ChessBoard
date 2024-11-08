#include <stdio.h>

typedef struct myVec {
    int x, y;
} Vector;

Vector RookDirections[4] =   {{-1,0}, {0,-1}, {1,0}, {0,1}};
Vector KnightDirections[8] = {{-2,-1}, {-1,-2}, {1,-2}, {2,-1}, {2,1}, {1,2}, {-1,2}, {-2,1}};
Vector BishopDirections[4] = {{-1,-1}, {1,-1}, {1,1}, {-1,1}};
Vector QueenDirections[8] =  {{-1,0}, {0,-1}, {1,0}, {0,1}, {-1,-1}, {1,-1}, {1,1}, {-1,1}};
Vector KingDirections[8] =   {{-1,0}, {0,-1}, {1,0}, {0,1}, {-1,-1}, {1,-1}, {1,1}, {-1,1}};

char board[8][8];

void startBoard() {
    const char blackBackRank[8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    const char whiteBackRank[8] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == 0) {
                board[i][j] = blackBackRank[j];
            }
            else if (i == 1) {
                board[i][j] = 'P';
            }
            else if (i == 6) {
                board[i][j] = 'p';
            }
            else if (i == 7) {
                board[i][j] = whiteBackRank[j];
            }
            else {
                board[i][j] = '.';
            }
        }
    }
}

void printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int areEnemies(char ch1, char ch2) {
    if (ch1 >= 'A' && ch1 <= 'Z' && ch2 >= 'a' && ch2 <= 'z') {
        return 1;
    }
    else if (ch1 >= 'a' && ch1 <= 'z' && ch2 >= 'A' && ch2 <= 'Z') {
        return 1;
    }
    return 0;
}

void movesTo(int x, int y, char moves[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            moves[i][j] = '.';
        }
    }

    moves[x][y] = '*';

    switch (board[x][y])
    {
    case 'r':
    case 'R':
        for (int i = 0; i < 4; i++) {
            for (int step = 1;; step++) {
                Vector targetPos = {x+RookDirections[i].x*step, y+RookDirections[i].y*step};
                if (targetPos.x < 0 || targetPos.x >= 8 || targetPos.y < 0 || targetPos.y >= 8) {
                    break;
                }
                char targetChar = board[targetPos.x][targetPos.y];
                if (targetChar == '.') {
                    moves[targetPos.x][targetPos.y] = 'x';
                }
                else if (areEnemies(board[x][y], targetChar)) {
                    moves[targetPos.x][targetPos.y] = 'X';
                    break;
                }
                else {
                    break;
                }
            }
        }
        break;

    case 'N':
    case 'n':
        for (int i = 0; i < 8; i++) {
            Vector targetPos = {x+KnightDirections[i].x, y+KnightDirections[i].y};
            if (targetPos.x < 0 || targetPos.x >= 8 || targetPos.y < 0 || targetPos.y >= 8) {
                continue;
            }
            char targetChar = board[targetPos.x][targetPos.y];
            if (targetChar == '.') {
                moves[targetPos.x][targetPos.y] = 'x';
            }
            else if (areEnemies(board[x][y], targetChar)) {
                moves[targetPos.x][targetPos.y] = 'X';
                continue;
            }
        }
        break;

    case 'B':
    case 'b':
        for (int i = 0; i < 4; i++) {
            for (int step = 1;; step++) {
                Vector targetPos = {x+BishopDirections[i].x*step, y+BishopDirections[i].y*step};
                if (targetPos.x < 0 || targetPos.x >= 8 || targetPos.y < 0 || targetPos.y >= 8) {
                    break;
                }
                char targetChar = board[targetPos.x][targetPos.y];
                if (targetChar == '.') {
                    moves[targetPos.x][targetPos.y] = 'x';
                }
                else if (areEnemies(board[x][y], targetChar)) {
                    moves[targetPos.x][targetPos.y] = 'X';
                    break;
                }
                else {
                    break;
                }
            }
        }
        break;

    case 'Q':
    case 'q':
        for (int i = 0; i < 8; i++) {
            for (int step = 1;; step++) {
                Vector targetPos = {x+QueenDirections[i].x*step, y+QueenDirections[i].y*step};
                if (targetPos.x < 0 || targetPos.x >= 8 || targetPos.y < 0 || targetPos.y >= 8) {
                    break;
                }
                char targetChar = board[targetPos.x][targetPos.y];
                if (targetChar == '.') {
                    moves[targetPos.x][targetPos.y] = 'x';
                }
                else if (areEnemies(board[x][y], targetChar)) {
                    moves[targetPos.x][targetPos.y] = 'X';
                    break;
                }
                else {
                    break;
                }
            }
        }
        break;

    case 'K':
    case 'k':
        for (int i = 0; i < 8; i++) {
            Vector targetPos = {x+KingDirections[i].x, y+KingDirections[i].y};
            if (targetPos.x < 0 || targetPos.x >= 8 || targetPos.y < 0 || targetPos.y >= 8) {
                continue;
            }
            char targetChar = board[targetPos.x][targetPos.y];
            if (targetChar == '.') {
                moves[targetPos.x][targetPos.y] = 'x';
            }
            else if (areEnemies(board[x][y], targetChar)) {
                moves[targetPos.x][targetPos.y] = 'X';
                break;
            }
        }
        break;
    
    case 'P':
        if (board[x][y+1] == '.') {
            moves[x][y+1] = 'x';
        }
        if (areEnemies(board[x][y], board[x-1][y+1])) {
            moves[x-1][y+1] = 'X';
        }
        if (areEnemies(board[x][y], board[x+1][y+1])) {
            moves[x+1][y+1] = 'X';
        }
        break;

    case 'p':
        if (board[x][y-1] == '.') {
            moves[x][y-1] = 'x';
        }
        if (areEnemies(board[x][y], board[x-1][y-1])) {
            moves[x-1][y-1] = 'X';
        }
        if (areEnemies(board[x][y], board[x+1][y-1])) {
            moves[x+1][y-1] = 'X';
        }
        break;
    
    default:
        break;
    }
}

void main() {
    startBoard();
    printBoard();

    printf("\n");
    board[1][3] = '.';
    board[1][4] = '.';

    char moves[8][8];
    movesTo(0, 3, moves);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%c ", moves[i][j]);
        }
        printf("\n");
    }
}