#include <stdio.h>
#include <stdlib.h>

// 定义棋盘大小
#define BOARD_SIZE 3

// 打印棋盘，添加行列编号方便查看
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    // 打印列编号
    printf("   ");
    for (int j = 0; j < BOARD_SIZE; j++) {
        printf(" %d ", j);
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        // 打印行编号
        printf(" %d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
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

// 检查是否有玩家获胜
int checkWin(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    // 检查行
    for (int i = 0; i < BOARD_SIZE; i++) {
        int win = 1;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j]!= player) {
                win = 0;
                break;
            }
        }
        if (win) return 1;
    }

    // 检查列
    for (int j = 0; j < BOARD_SIZE; j++) {
        int win = 1;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i][j]!= player) {
                win = 0;
                break;
            }
        }
        if (win) return 1;
    }

    // 检查对角线（主对角线）
    int win = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][i]!= player) {
            win = 0;
            break;
        }
    }
    if (win) return 1;

    // 检查对角线（副对角线）
    win = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][BOARD_SIZE - 1 - i]!= player) {
            win = 0;
            break;
        }
    }
    if (win) return 1;

    return 0;
}

// 检查棋盘是否已满（平局情况）
int isBoardFull(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

// 清理输入缓冲区，避免缓冲区残留字符影响后续输入
void clearInputBuffer() {
    while (getchar()!= '\n');
}

// 获取玩家输入，直到输入合法
void getPlayerInput(int *row, int *col, char board[BOARD_SIZE][BOARD_SIZE], int currentPlayer) {
    int inputValid = 0;
    while (!inputValid) {
        printf("玩家 %d 请输入行（0 - %d）和列（0 - %d）坐标，用空格隔开: ", currentPlayer, BOARD_SIZE - 1, BOARD_SIZE - 1);
        if (scanf("%d %d", row, col)!= 2) {
            // 输入格式错误提示
            printf("输入格式错误，请输入两个整数作为坐标哦，请重新输入！\n");
            clearInputBuffer();
            continue;
        }
        // 检查输入坐标是否合法
        if (*row < 0 || *row >= BOARD_SIZE || *col < 0 || *col >= BOARD_SIZE || board[*row][*col]!= ' ') {
            printf("输入的坐标不合法，请确保坐标在棋盘范围内且对应位置为空，请重新输入！\n");
        } else {
            inputValid = 1;
        }
    }
}

// 执行游戏流程
void playGame() {
    char board[BOARD_SIZE][BOARD_SIZE];
    // 初始化棋盘，每个位置初始化为空格
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }

    int currentPlayer = 1;  // 1表示玩家1，2表示玩家2
    char players[2] = { 'X', 'O' };
    int row, col;
    int gameOver = 0;
    int gameCount = 1;  // 记录游戏轮数，初始为1

    while (!gameOver) {
        printBoard(board);
        getPlayerInput(&row, &col, board, currentPlayer);

        board[row][col] = players[currentPlayer - 1];

        // 检查是否获胜
        if (checkWin(board, players[currentPlayer - 1])) {
            printBoard(board);
            printf("玩家 %d 获胜！\n", currentPlayer);
            gameOver = 1;
            break;
        }

        // 检查是否平局
        if (isBoardFull(board)) {
            printBoard(board);
            printf("平局！\n");
            gameOver = 1;
            break;
        }

        // 切换玩家
        currentPlayer = (currentPlayer % 2) + 1;
    }
    printf("这是第 %d 轮游戏结束。\n", gameCount);  // 显示游戏轮数
}

int main() {
    playGame();
    return 0;
}
