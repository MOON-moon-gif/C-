#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 15

// 棋盘结构体
typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
} ChessBoard;

// 初始化棋盘
void initBoard(ChessBoard *board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board->board[i][j] = '.';
        }
    }
}

// 绘制棋盘
void drawBoard(ChessBoard *board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board->board[i][j]);
            if (j < BOARD_SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < BOARD_SIZE - 1) {
            for (int k = 0; k < BOARD_SIZE * 4 - 1; k++) {
                printf("-");
            }
            printf("\n");
        }
    }
}

// 判断坐标是否在棋盘内
int isInBoard(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

// 判断是否有五子连珠
int checkWin(ChessBoard *board, int x, int y, char currentPlayer) {
    int count;

    // 横向检查
    count = 1;
    for (int i = 1; i < 5; i++) {
        if (isInBoard(x + i, y) && board->board[x + i][y] == currentPlayer) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 5; i++) {
        if (isInBoard(x - i, y) && board->board[x - i][y] == currentPlayer) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 5) {
        return 1;
    }

    // 纵向检查
    count = 1;
    for (int i = 1; i < 5; i++) {
        if (isInBoard(x, y + i) && board->board[x][y + i] == currentPlayer) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 5; i++) {
        if (isInBoard(x, y - i) && board->board[x][y - i] == currentPlayer) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 5) {
        return 1;
    }

    // 正斜向检查（从左上角到右下角方向）
    count = 1;
    for (int i = 1; i < 5; i++) {
        if (isInBoard(x + i, y + i) && board->board[x + i][y + i] == currentPlayer) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 5; i++) {
        if (isInBoard(x - i, y - i) && board->board[x - i][y - i] == currentPlayer) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 5) {
        return 1;
    }

    // 反斜向检查（从右上角到左下角方向）
    count = 1;
    for (int i = 1; i < 5; i++) {
        if (isInBoard(x - i, y + i) && board->board[x - i][y + i] == currentPlayer) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 5; i++) {
        if (isInBoard(x + i, y - i) && board->board[x + i][y - i] == currentPlayer) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 5) {
        return 1;
    }

    return 0;
}

// 电脑随机落子
void computerMove(ChessBoard *board) {
    int x, y;
    do {
        x = rand() % BOARD_SIZE;
        y = rand() % BOARD_SIZE;
    } while (board->board[x][y]!= '.');
    board->board[x][y] = 'O';
}

int main() {
    ChessBoard board;
    initBoard(&board);
    int currentPlayer = 1;  // 1表示玩家（用 'X' 表示棋子），0表示电脑（用 'O' 表示棋子）
    char input[10];
    int x, y;
    int gameOver = 0;

    srand((unsigned int)time(NULL));

    while (!gameOver) {
        drawBoard(&board);
        if (currentPlayer == 1) {
            // 玩家落子
            printf("请输入坐标（格式为x,y）落子: ");
            scanf("%s", input);
            if (sscanf(input, "%d,%d", &x, &y) == 2) {
                if (isInBoard(x, y) && board.board[x][y] == '.') {
                    board.board[x][y] = 'X';
                    if (checkWin(&board, x, y, 'X')) {
                        drawBoard(&board);
                        printf("玩家获胜！\n");
                        gameOver = 1;
                    }
                    currentPlayer = 0;
                } else {
                    printf("该位置已被占用或坐标超出棋盘范围，请重新输入！\n");
                }
            } else {
                printf("输入格式错误，请按照 'x,y' 的格式输入坐标！\n");
            }
        } else {
            // 电脑落子
            computerMove(&board);
            if (checkWin(&board, x, y, 'O')) {
                drawBoard(&board);
                printf("电脑获胜！\n");
                gameOver = 1;
            }
            currentPlayer = 1;
        }
    }

    return 0;
}
