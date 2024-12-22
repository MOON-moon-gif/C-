#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

// 定义物体结构体
typedef struct Object {
    int x;
    int y;
    char symbol;
    int color_pair;
} Object;

// 初始化ncurses库
void init_ncurses() {
    initscr();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
}

// 关闭ncurses库
void end_ncurses() {
    endwin();
}

// 设置物体颜色
void set_object_color(Object *obj, int color_pair) {
    obj->color_pair = color_pair;
}

// 在屏幕上绘制物体
void draw_object(Object obj) {
    attron(COLOR_PAIR(obj.color_pair));
    mvaddch(obj.y, obj.x, obj.symbol);
    attroff(COLOR_PAIR(obj.color_pair));
}

// 导出动画帧到文件
void export_frames(Object objects[], int num_objects, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < num_objects; i++) {
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
    Object obj;
    int x, y, color_pair;
    char symbol;
    while (fscanf(fp, "%d %d %c %d\n", &x, &y, &symbol, &color_pair) == 4) {
        obj.x = x;
        obj.y = y;
        obj.symbol = symbol;
        obj.color_pair = color_pair;
        clear();
        draw_object(obj);
        refresh();
        usleep(500000);
    }
    fclose(fp);
}

int main() {
    init_ncurses();

    // 创建两个物体
    Object obj1 = {10, 10, '*', 1};
    Object obj2 = {15, 10, '#', 2};
    Object objects[] = {obj1, obj2};
    int num_objects = sizeof(objects) / sizeof(Object);

    // 简单动画，物体移动
    for (int i = 0; i < 10; i++) {
        obj1.x++;
        obj2.x--;
        clear();
        draw_object(obj1);
        draw_object(obj2);
        refresh();
        usleep(500000);
    }

    // 导出动画帧
    export_frames(objects, num_objects, "animation_frames.txt");

    // 回放动画
    replay_frames("animation_frames.txt");

    end_ncurses();
    return 0;
}
