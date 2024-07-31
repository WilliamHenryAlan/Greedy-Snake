#include "greedySnake.h"

int main(void) {
    // 初始化随机种子
    srand(time(NULL));
    // hide cursor
    hideCursor();
    // init snake
    Snake* s = NULL;
    s = init_snake(s);
    // show wall
    showWall();
    // start loop
    startGame(s);
    // free memory
    free(s);
    return 0;
}