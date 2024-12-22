#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

// 定义颜色代码（这里简单模拟一些基本颜色）
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// 定义最大物体数量和最大动画帧数
#define MAX_OBJECTS 10
#define MAX_FRAMES 100

// 物体结构体，包含位置、颜色和字符表示
typedef struct {
    int x;
    int y;
    char color[10];
    char symbol;
} Object;

// 动画帧结构体，包含多个物体信息
typedef struct {
    Object objects[MAX_OBJECTS];
    int object_count;
} Frame;

Frame frames[MAX_FRAMES];  // 存储动画帧的数组
int frame_count = 0;  // 当前动画帧数量

// 函数原型声明
void clear_screen();
void gotoxy(int x, int y);
void create_object(int x, int y, char *color, char symbol);
void save_frame();
void play_animation();

int main() {
    char command[10];
    int x, y;
    char color[10];
    char symbol;

    // 设置终端为非标准模式，用于获取单个字符输入而不等待回车
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("简易字符动画设计制作套件\n");
    printf("命令：create <x> <y> <color> <symbol> 创建物体\n");
    printf("       save 保存当前帧\n");
    printf("       play 播放动画\n");
    printf("       exit 退出程序\n");

    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "create") == 0) {
            scanf("%d %d %s %c", &x, &y, color, &symbol);
            create_object(x, y, color, symbol);
        } else if (strcmp(command, "save") == 0) {
            save_frame();
        } else if (strcmp(command, "play") == 0) {
            play_animation();
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("无效命令，请重新输入。\n");
        }
    }

    // 恢复终端原始模式
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}

// 清屏函数
void clear_screen() {
    printf("\033[2J");
}

// 移动光标到指定位置函数
void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
}

// 创建物体函数
void create_object(int x, int y, char *color, char symbol) {
    Object new_object;
    new_object.x = x;
    new_object.y = y;
    strcpy(new_object.color, color);
    new_object.symbol = symbol;

    frames[frame_count].objects[frames[frame_count].object_count] = new_object;
    frames[frame_count].object_count++;
}

// 保存帧函数
void save_frame() {
    if (frame_count < MAX_FRAMES - 1) {
        frame_count++;
        printf("帧已保存，当前帧数：%d\n", frame_count);
    } else {
        printf("动画帧已满，无法保存更多帧。\n");
    }
}

// 播放动画函数
void play_animation() {
    int i, j, k;
    if (frame_count > 0) {
        clear_screen();
        for (i = 0; i < frame_count; i++) {
            for (j = 0; j < frames[i].object_count; j++) {
                gotoxy(frames[i].objects[j].x, frames[i].objects[j].y);
                printf("%s%c%s", frames[i].objects[j].color, frames[i].objects[j].symbol, RESET);
            }
            usleep(500000);  // 每帧之间延时500毫秒
            if (i < frame_count - 1) {
                clear_screen();
            }
        }
    } else {
        printf("没有保存的动画帧，无法播放。\n");
    }
}
