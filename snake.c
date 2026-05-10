#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 50
#define HEIGHT 20

char MAP[HEIGHT][WIDTH] = {0};
int snakeX[100], snakeY[100];
int snakeLen = 3;
char alive = 1;

void init()
{
    // 1. 初始化邊界與地圖
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                MAP[i][j] = 3;
            else
                MAP[i][j] = 0;
        }
    }

    // 2. 初始化蛇的座標
    for (int i = 0; i < snakeLen; i++)
    {
        snakeX[i] = 10 - i;
        snakeY[i] = 10;
        MAP[snakeY[i]][snakeX[i]] = 2;
    }

    // 3. 放置一顆星星
    MAP[5][15] = 1;
}

void show()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (MAP[i][j] == 0) printf(" ");
            else if (MAP[i][j] == 1) printf("*");
            else if (MAP[i][j] == 2)
            {
                if (i == snakeY[0] && j == snakeX[0]) printf("O");
                else printf("o");
            }
            else if (MAP[i][j] == 3) printf("X");
        }
        printf("\n");
    }
}

void move(int dx, int dy)
{
    // 1. 紀錄舊尾巴位置
    int oldTailX = snakeX[snakeLen - 1];
    int oldTailY = snakeY[snakeLen - 1];

    // 2. 移動蛇身座標
    for (int i = snakeLen - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // 3. 更新蛇頭
    snakeX[0] += dx;
    snakeY[0] += dy;

    // 4. 碰撞檢查
    if (MAP[snakeY[0]][snakeX[0]] == 3 || MAP[snakeY[0]][snakeX[0]] == 2)
    {
        alive = 0;
        return;
    }

    // 5. 更新地圖標記
    MAP[oldTailY][oldTailX] = 0;
    MAP[snakeY[0]][snakeX[0]] = 2;
}

int main()
{
    init();

    while (alive)
    {
        system("cls");
        show();

        char input;
        printf("Move (w/a/s/d): ");
        scanf(" %c", &input);

        if (input == 'w') move(0, -1);
        else if (input == 's') move(0, 1);
        else if (input == 'a') move(-1, 0);
        else if (input == 'd') move(1, 0);
        else if (input == 'q') break;
    }

    printf("Game Over!\n");
    return 0;
}
