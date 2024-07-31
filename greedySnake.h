#ifndef __GREEDYSNAKE_H
#define __GREEDYSNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define Width 100
#define Height 20
//坐标
typedef struct coordinate {int x,y;}Coordinate; //建立x y坐标
//snake and food
typedef struct snake{
    Coordinate body[Width * Height];//snake的body
    Coordinate tail;//记录snake tail 在snake move时用于清除
    int size;//sizeof snake
    Coordinate food;//food 坐标
    COORD position;//定位光标位置
    int deviation_x,deviation_y;//移动方向偏移
}Snake;

//初始化snake
Snake* init_snake(Snake* s);

//显示snake
void showSnake(Snake* s);

//show wall
void showWall();

//show food
void showFood(Snake* s);

//hide cursor
void hideCursor();

//移动snake
void moveSnake(Snake* s);

//主逻辑
void startGame(Snake* s);

//控制snake
void controlSnake(Snake* s);
#endif