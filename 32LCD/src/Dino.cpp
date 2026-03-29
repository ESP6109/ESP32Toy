#include "Dino.h"

int frame = 0;
int dinoX = 10;
float dinoY = 0;
float jumpVel = 0;
bool jumping = false;
bool gameOver = false;

int cactusX = 128;
int countS = 0;
int score = 0;
int speed = 3;                 // base cactus speed
unsigned long frameDelay = 30; // base delay (ms)

// Ground and clouds
int indexca = 0;
const int groundY = 56;
int cloud1X = 40;
int cloud2X = 100;
const int cloudY1 = 8;
const int cloudY2 = 15;

int widthC[4] = {8, 26, 17, 12};
int heightC[4] = {17, 16, 17, 23};

// Button
// const int BUTTON_PIN = 0; // connect to GND for press

// ---- Drawing helpers ----
void drawDino(int x, int y, bool legSwitch)
{
    if (gameOver)
    {
        u8g2.drawXBMP(x, y, 20, 22, Dinosaur3);
    }
    else if (jumping)
    {
        u8g2.drawXBMP(x, y, 20, 22, Dinosaur4);
    }
    else
    {
        if (legSwitch)
        {
            u8g2.drawXBMP(x, y, 20, 22, Dinosaur1);
        }
        else
        {
            u8g2.drawXBMP(x, y, 20, 22, Dinosaur2);
        }
    }
}

void drawCactus(int x, int y, int i)
{
    u8g2.drawXBMP(x, y, widthC[i], heightC[i], cactus[i]);
}

void drawCloud(int x, int y, int i)
{
    u8g2.drawXBMP(x, y, 23, 7, Cloud);
}

// ---- Logic helpers ----
void triggerJump()
{
    if (!jumping && !gameOver)
    {
        jumping = true;
        jumpVel = -5.5;
    }
}

void restartGame()
{
    gameOver = false;
    cactusX = 128;
    countS = 0;
    score = 0;
    dinoX = 10;
    dinoY = 0;
    jumpVel = 0;
    jumping = false;
    speed = 3;
    frameDelay = 30;
    cloud1X = 40;
    cloud2X = 100;
}

void dino()
{
    u8g2.setFontMode(1);
    restartGame();
    setCpuFrequencyMhz(160);
    while (!Button)
    {
        bool pressed = (digitalRead(MIDDLE) == LOW);
        bool f = (digitalRead(RIGHT) == LOW);
        bool r = (digitalRead(LEFT) == LOW);
        // restart
        if (pressed && gameOver)
        {
            restartGame();
            pressed = 0;
        }
        if (!gameOver)
        {
            if (f && !jumping)
            {
                dinoX++;
                if (dinoX >= 64)
                    dinoX = 64;
            }
            if (r && !jumping)
            {
                dinoX--;
                if (dinoX <= 2)
                    dinoX = 2;
            }
            // Jump
            if (pressed && !jumping && !gameOver)
                triggerJump();

            // Jump physics
            if (jumping && !gameOver)
            {
                dinoY += jumpVel;
                jumpVel += 0.5;
                if (dinoY >= 0)
                {
                    dinoY = 0;
                    jumping = false;
                }
            }

            // Cactus movement
            countS++;
            cactusX -= speed;
            if (cactusX < -widthC[indexca])
            {
                cactusX = 128 + random(30, 80);
                indexca = random(0, 4);
                // speed up every 10 points
                if (countS % 10 == 0 && frameDelay > 10)
                {
                    speed++;
                    frameDelay -= 5; // faster frame loop
                }
            }
        }

        // Clouds (slower parallax)
        cloud1X -= 2;
        cloud2X -= 1;
        if (cloud1X < -47)
            cloud1X = 128 + random(10, 30);
        if (cloud2X < -47)
            cloud2X = 128 + random(30, 60);

        // Collision

        if (!gameOver && (cactusX < dinoX + 20) && (cactusX + widthC[indexca] > dinoX) && (dinoY) > (-heightC[indexca]))
        {
            gameOver = true;
        }

        // Draw frame
        u8g2.clearBuffer();
        drawCloud(cloud1X, cloudY1, 1);
        drawCloud(cloud2X, cloudY2, 2);
        if (!gameOver)
        {
            drawCactus(cactusX, groundY - heightC[indexca], indexca);
            drawDino(dinoX, groundY + dinoY - 22, frame % 4 < 2);
        }
        else
        {
            u8g2.setFont(u8g2_font_6x10_tf);
            u8g2.drawStr(35, 15, "GAME OVER");
            u8g2.drawStr(10, 30, "Press to restart");
            drawCactus(cactusX, groundY - heightC[indexca], indexca);
            drawDino(dinoX, groundY + dinoY - 22, frame % 4 < 2);
        }
        u8g2.drawHLine(0, groundY, 128);
        u8g2.setFont(u8g2_font_6x10_tf);
        score = countS / 5;
        // u8g2.setCursor(10, 10);
        // u8g2.print(indexca);
        u8g2.setCursor(100, 10);
        u8g2.print(score);
        u8g2.sendBuffer();
        frame++;
        delay(frameDelay);
    }
    setCpuFrequencyMhz(80);
    swclr();
}

/*
///////恐龙//////
int DinosaurY = 28;         // 恐龙的高
uint8_t Dinosaur_blood = 3; // 血量
//////障碍物//////
int obstacleX = 130; // 障碍物坐标
uint8_t obstacle_index = 0;
///////云朵//////
int16_t CloudX = 150;
uint8_t Cloud_index = 0;
int die = 0;

uint32_t score = 0;
void impact()
{
    if (obstacleX <= 21)
    {
        if (DinosaurY >= 12 && Dinosaur_blood > 0 && obstacle_index == 0)
        {
            obstacleX = 150;
            Dinosaur_blood--;
            obstacle_index++;
        }
        else if (DinosaurY >= 13 && Dinosaur_blood > 0 && obstacle_index == 1)
        {
            obstacleX = 150;
            Dinosaur_blood--;
            obstacle_index++;
            u8g2.setCursor(10, 20);
            u8g2.printf("!!!");
        }
    } // 发生碰撞
    if (Dinosaur_blood == 0) // 去往极乐世界.
    {
        die = 1;
        u8g2.setCursor(40, 20);
        u8g2.printf("GAME OVER");
    }
}

void jump()
{
    static uint8_t jump_flag = 0; // 跳跃标志位
    static uint8_t Back_flag = 0; // 归为标志位
    if (digitalRead(Middle) == 0 && jump_flag == 0 && Back_flag == 0)
    {
        jump_flag = 1; // 跳起来
    }
    if (jump_flag)
    { // 允许跳起
        DinosaurY -= 3;
    }
    if (DinosaurY <= 2)
    { // 限制高度
        jump_flag = 0;
        Back_flag = 1; // 允许回落
    }
    if (Back_flag)
    { // 回落
        DinosaurY += 3;
    }
    if (DinosaurY >= 28)
    {
        DinosaurY = 28;
        Back_flag = 0; // 终止回落
    }
}

void dino()
{
    u8g2.setFontMode(1);
    uint8_t thread = 0;
    // Pin_init(GPIOB,GPIO_Pin_9,GPIO_Mode_IPU);//初始化按键
    // OLED_Init(GPIOB,GPIO_Pin_10,GPIO_Pin_11);//STM32和OLED屏幕通讯
    Dinosaur_blood = 3;
    score = 0;
    die = 0;
    while (!Button)
    {
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_6x10_tf);
        ///////////基础参数///////////
        thread++;
        if (thread >= 8)
            thread = 0;
        u8g2.drawHVLine(0, 50, 128, 50);
        if (!die)
        {
            u8g2.setCursor(10, 10);
            u8g2.printf("score:%d", score);
            score++;
            ///////////云朵///////////
            switch (Cloud_index)
            {
            case 0:
                u8g2.drawXBMP(CloudX, 10, 20, 10, Cloud2);
                break;
            case 1:
                u8g2.drawXBMP(CloudX, 14, 20, 10, Cloud1);
                break;
            }
            CloudX--;
            if (CloudX <= -20)
            {
                Cloud_index++;
                if (Cloud_index >= 2)
                    Cloud_index = 0;
                CloudX = 150;
            }

            ///////////恐龙///////////
            jump();   // 跳跃
            impact(); // 碰撞
            if (millis() / 250 % 2 == 1)
            {
                u8g2.drawXBMP(0, DinosaurY, 21, 22, Dinosaur1);
            }
            else
            {
                u8g2.drawXBMP(0, DinosaurY, 21, 22, Dinosaur2);
            }
            for (uint8_t i = 0; i < Dinosaur_blood; i++)
            {
                u8g2.drawXBMP(120 - i * 8, 6, 7, 6, blood);
            }

            ///////////障碍物///////////
            if (obstacleX <= -10)
            {
                obstacleX = 160; // 超出屏幕范围，重新生成
                obstacle_index++;
            }
            else if (obstacle_index >= 3)
            {
                obstacle_index = 0;
            }

            switch (obstacle_index)
            {
            case 0:
                u8g2.drawXBMP(obstacleX, 34, 9, 16, obstacle1);
                break;
            case 1:
                u8g2.drawXBMP(obstacleX, 35, 19, 15, obstacle2);
                break;
            case 2:
                u8g2.drawXBMP(obstacleX, 45, 9, 5, obstacle3);
                break;
            }
            obstacleX -= 5;
            // delay(1); // 图像更新速度
        }
        else
        {
            u8g2.setCursor(40, 20);
            u8g2.printf("GAME OVER");
            u8g2.setCursor(5, 10);
            u8g2.printf("score:%d", score);
        }
        u8g2.sendBuffer();
    }
    swclr();
    u8g2.setFontMode(0);
}*/
