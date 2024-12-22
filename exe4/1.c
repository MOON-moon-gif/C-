#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 24
#define MAX_DROPS 100

// 雨滴结构体
typedef struct Drop {
    int x;
    int y;
    int length;
} Drop;

// 初始化ncurses
void init_ncurses() {
    initscr();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    clear();
}

// 关闭ncurses
void close_ncurses() {
    endwin();
}

// 生成随机长度的雨滴
int random_length() {
    return (rand() % 15) + 5;
}

// 初始化雨滴数组
void init_drops(Drop drops[]) {
    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i].x = rand() % WIDTH;
        drops[i].y = rand() % HEIGHT;
        drops[i].length = random_length();
    }
}

// 移动和绘制雨滴
void update_drops(Drop drops[]) {
    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i].y++;
        if (drops[i].y >= HEIGHT) {
            drops[i].y = 0;
            drops[i].x = rand() % WIDTH;
            drops[i].length = random_length();
        }
        attron(COLOR_PAIR(1));
        for (int j = 0; j < drops[i].length; j++) {
            mvaddch(drops[i].y - j, drops[i].x, "01"[rand() % 2]);
        }
        attroff(COLOR_PAIR(1));
    }
}

int main() {
    srand(time(NULL));
    Drop drops[MAX_DROPS];

    init_ncurses();
    init_drops(drops);

    while (1) {
        update_drops(drops);
        refresh();
        napms(50);
    }

    close_ncurses();
    return 0;
}
