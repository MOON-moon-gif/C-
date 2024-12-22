#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

// 定义一些颜色对应的代码（这里简单模拟，实际可能对应具体硬件的颜色设置值）
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

// 假设LED的数量
#define LED_NUM 8  

int main() {
    int led_status[LED_NUM];
    int i;
    struct termios oldt, newt;
    char ch;

    // 获取终端当前属性设置
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    // 设置终端为非标准模式（不缓冲输入等，以便能及时检测按键）
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // 初始化LED状态都为灭
    for (i = 0; i < LED_NUM; i++) {
        led_status[i] = 0;
    }

    while (1) {
        // 红色LED依次点亮动画
        for (i = 0; i < LED_NUM; i++) {
            led_status[i] = 1;
            printf(RED);  // 设置输出为红色
            print_led_status(led_status);
            usleep(300000);
            led_status[i] = 0;
            printf(RESET);  // 恢复默认颜色
        }
        // 绿色LED依次点亮动画
        for (i = 0; i < LED_NUM; i++) {
            led_status[i] = 1;
            printf(GREEN);  // 设置输出为绿色
            print_led_status(led_status);
            usleep(300000);
            led_status[i] = 0;
            printf(RESET);  // 恢复默认颜色
        }
        // 蓝色LED依次点亮动画
        for (i = 0; i < LED_NUM; i++) {
            led_status[i] = 1;
            printf(BLUE);  // 设置输出为蓝色
            print_led_status(led_status);
            usleep(300000);
            led_status[i] = 0;
            printf(RESET);  // 恢复默认颜色
        }

        // 检测是否有按键按下，如果是 'q' 则退出循环
        if (read(STDIN_FILENO, &ch, 1) == 1 && tolower(ch) == 'q') {
            break;
        }
    }

    // 恢复终端原来的属性设置
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}

// 函数用于打印LED当前状态（简单用字符表示，1打印 * 表示亮，0打印空格表示灭）
void print_led_status(int *led_status) {
    int i;
    for (i = 0; i < sizeof(led_status) / sizeof(led_status[0]); i++) {
        if (led_status[i]) {
            printf("* ");
        } else {
            printf("  ");
        }
    }
    printf("\n");
}
