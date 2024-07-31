#include "greedySnake.h"
//初始化snake
Snake* init_snake(Snake* s) {
    s = (Snake*)malloc(sizeof(Snake));
    s->body[0].x = Width / 2;
    s->body[0].y = Height / 2;
    s->body[1].x = Width / 2 - 1;
    s->body[1].y = Height / 2;
    s->size = 2;
    s->deviation_x = 1;
    s->deviation_y = 0;
    return s;
}

void showSnake(Snake* s) {
    //show snake
    for (int i = 0;i < s->size;i++) {
        s->position.X = s->body[i].x;
        s->position.Y = s->body[i].y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),s->position);
        printf("#");
    }

    //clear snake tail
    s->position.X = s->tail.x;
    s->position.Y = s->tail.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),s->position);
    printf(" ");
}

//show wall
void showWall() {
    for (int i = 0;i <= Height;i++) {//建立高
        for (int j = 0;j <= Width;j++) {//建立长
            if (i == 0 || j == 0 || i == Height || j == Width)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}
//show food
void showFood(Snake* s) {
    int valid;
    do {
        valid = 1;
        s->food.x = rand() % (Width - 2) + 1; // 确保食物在墙内
        s->food.y = rand() % (Height - 2) + 1; // 确保食物在墙内
        for (int i = 0; i < s->size; i++) {
            if (s->food.x == s->body[i].x && s->food.y == s->body[i].y) {
                valid = 0; // 如果食物生成在蛇的身体上，则标记为无效
                break;
            }
        }
    } while (!valid);

    // show food
    s->position.X = s->food.x;
    s->position.Y = s->food.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), s->position);
    printf("*");
}

//hide cursor
void hideCursor() {
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = sizeof(cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
}

void moveSnake(Snake* s) {
    s->tail = s->body[s->size - 1];
    for (int i = s->size - 1;i > 0;i--) {
        s->body[i] = s->body[i - 1];
    }
    s->body[0].x += s->deviation_x;
    s->body[0].y += s->deviation_y;

    if (s->body[0].x == s->food.x && s->body[0].y == s->food.y) {//snake吃到食物
        s->size++;
        showFood(s);
    }
}

void startGame(Snake* s) {
    showFood(s);
    while (1) {
        controlSnake(s);
        moveSnake(s);
        showSnake(s);
        // 检查蛇是否撞墙
        if (s->body[0].x <= 0 || s->body[0].y <= 0 
        || s->body[0].x >= Width || s->body[0].y >= Height) {
            printf("\nGame Over!\n");
            break;
        }
        Sleep(200);
    }
}

void controlSnake(Snake* s) {
    char key = 0;
    while (_kbhit()) {
        key = _getch();
    }
    switch (key) {
        case 'w':
            if (s->deviation_y != 1) {//保证snake不直接反向
                s->deviation_x = 0;
                s->deviation_y = -1;
            }
            break;
        case 's':
            if (s->deviation_y != -1) {
                s->deviation_x = 0;
                s->deviation_y = 1;
            }
            break;
        case 'a':
            if (s->deviation_x != 1) {
                s->deviation_x = -1;
                s->deviation_y = 0;
            }
            break;
        case 'd':
            if (s->deviation_x != -1) {
                s->deviation_x = 1;
                s->deviation_y = 0;
            }
            break;
    }
}