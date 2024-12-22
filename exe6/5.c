#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_OBJECTS 100
#define ANIMATION_FPS 10
#define FRAME_DELAY (1000 / ANIMATION_FPS)

// 定义物体结构体
typedef struct Object {
    int x;
    int y;
    char symbol;
    int color_pair;
} Object;

Object objects[MAX_OBJECTS];
int objectCount = 0;

// 初始化ncurses库
void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    // 可以根据需要添加更多的颜色对
}

// 关闭ncurses库
void end_ncurses() {
    endwin();
}

// 添加物体
void add_object(int x, int y, char symbol, int color_pair) {
    if (objectCount < MAX_OBJECTS) {
        objects[objectCount].x = x;
        objects[objectCount].y = y;
        objects[objectCount].symbol = symbol;
        objects[objectCount].color_pair = color_pair;
        objectCount++;
    }
}

// 在屏幕上绘制所有物体
void draw_objects() {
    clear(); // 清除屏幕
    for (int i = 0; i < objectCount; i++) {
        attron(COLOR_PAIR(objects[i].color_pair));
        mvaddch(objects[i].y, objects[i].x, objects[i].symbol);
        attroff(COLOR_PAIR(objects[i].color_pair));
    }
    refresh(); // 刷新屏幕以显示更新
}

// 导出动画帧到文件
void export_frames(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < objectCount; i++) {
        fprintf(fp, "%d %d %c %d\n", objects[i].x, objects[i].y, objects[i].symbol, objects[i].color_pair);
    }
    fclose(fp);
}

// 从文件读取并回放动画
void replay_frames(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    Object temp_obj;
    int x, y, color_pair;
    char symbol;
    while (fscanf(fp, "%d %d %c %d\n", &x, &y, &symbol, &color_pair) == 4) {
        temp_obj.x = x;
        temp_obj.y = y;
        temp_obj.symbol = symbol;
        temp_obj.color_pair = color_pair;
        clear();
        draw_objects(); // 这里应该只绘制当前读取到的物体
        refresh();
        usleep(FRAME_DELAY * 1000);
    }
    fclose(fp);
}

int main() {
    init_ncurses();

    // 添加物体
    add_object(10, 10, '*', 1);
    add_object(15, 10, '#', 2);

    // 简单动画，物体移动
    for (int frame = 0; frame < 50; frame++) {
        for (int i = 0; i < objectCount; i++) {
            objects[i].x++;
            if (objects[i].x > COLS - 1) {
                objects[i].x = 0;
            }
        }
        draw_objects();
        usleep(FRAME_DELAY * 1000);
    }

    // 导出动画帧
    export_frames("animation_frames.txt");

    // 回放动画
    replay_frames("animation_frames.txt");

    end_ncurses();
    return 0;
}
