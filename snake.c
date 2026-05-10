#include <stdio.h>
#include <stdlib.h>
#include <conio.h>    // kbhit() 與 getch()
#include <windows.h>  // Sleep()

#define WIDTH 50
#define HEIGHT 20

char MAP[HEIGHT][WIDTH] = {0};
int snakeX[100], snakeY[100];
int snakeLen = 3;
int dirX = 1, dirY = 0;
int speed = 100; // 遊戲延遲時間 (ms)
char alive = 1;

void init()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                MAP[i][j] = 3; // 牆壁
            else
                MAP[i][j] = 0; // 空地
        }
    }

    // 初始化蛇位置
    for (int i = 0; i < snakeLen; i++) {
        snakeX[i] = 10 - i;
        snakeY[i] = 10;
        MAP[snakeY[i]][snakeX[i]] = 2;
    }

    MAP[5][15] = 1; // 放置星星
}

void show()
{
    // 技巧：將游標移回 (0,0) 而不是 cls，可以大幅減少閃爍
    system("cls");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (MAP[i][j] == 0) printf(" ");
            else if (MAP[i][j] == 1) printf("*");
            else if (MAP[i][j] == 2)
            {
                printf(((i == snakeY[0] && j == snakeX[0]) ? "O" : "o"));
            }
            else if (MAP[i][j] == 3) printf("X");
        }
        printf("\n");
    }
    printf("Score: %d | Speed: %dms\n", (snakeLen - 3) * 10, speed);
}

void move()
{
    // 1. 抹除舊尾巴
    MAP[snakeY[snakeLen - 1]][snakeX[snakeLen - 1]] = 0;

    // 2. 座標遞推 (傳遞足跡)
    for (int i = snakeLen - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // 3. 根據目前方向移動蛇頭
    snakeX[0] += dirX;
    snakeY[0] += dirY;

    // 4. 碰撞檢查
    int headVal = MAP[snakeY[0]][snakeX[0]];
    if (headVal == 3 || headVal == 2)
    {
        alive = 0;
        return;
    }

    // 5. 吃到星星判定
    if (headVal == 1)
    {
        snakeLen++;
        speed = (speed > 30) ? speed - 2 : speed; // 越吃越快
        // 隨機生成新星星
        MAP[rand() % (HEIGHT - 2) + 1][rand() % (WIDTH - 2) + 1] = 1;
    }

    // 6. 更新地圖標記
    MAP[snakeY[0]][snakeX[0]] = 2;
}

int main()
{

    init();

    while (alive)
    {
        // A. 處理輸入 (非阻塞)
        if (kbhit())
        {
            char key = getch();
            // 防止 180 度直接回頭 (自殺防止邏輯)
            if (key == 'w' && dirY != 1)        { dirX = 0;     dirY = -1;  }
            else if (key == 's' && dirY != -1)  { dirX = 0;     dirY = 1;   }
            else if (key == 'a' && dirX != 1)   { dirX = -1;    dirY = 0;   }
            else if (key == 'd' && dirX != -1)  { dirX = 1;     dirY = 0;   }
            else if (key == 'q') break;
        }

        // B. 更新邏輯
        move();

        // C. 渲染畫面
        show();

        // D. 控制節奏：如果不加這行，CPU 會跑太快，蛇會瞬間撞牆
        Sleep(speed);
    }

    printf("\n--- GAME OVER ---\n");
    return 0;
}
