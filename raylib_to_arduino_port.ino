#include "include/Block.hpp"
#include "include/BasicCam.hpp"
#include "include/Bullet.hpp"
#include "include/Utils.hpp"

#include <U8glib.h>
#include <unistd.h>

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE);

PlayerInfo player = {3, 2, false};
byte* playerPointer = (byte*)&player;
PlayerInfo opponent = {0, 0, false};
byte* opponentPointer = (byte*)&opponent;

int activeBullets;
Bullet* playerBullets;
Bullet* opponentBullets;

// 0 = menu, 1 = game 
byte gameState = 0;

Block* blocks;
BasicCam cam(3, 2, 90);

void setup()
{
    pinMode(ATK_PIN, INPUT);
    Serial.begin(9600);
    oled.setFont(u8g_font_osb18);

    Bullet tmp(0,0,-1);
    tmp.Active = false;

    playerBullets = (Bullet*)malloc(sizeof(Bullet) * BULLET_COUNT);
    opponentBullets = (Bullet*)malloc(sizeof(Bullet) * BULLET_COUNT);

    memset(playerBullets, tmp, sizeof(Bullet) * BULLET_COUNT);
    memset(opponentBullets, tmp, sizeof(Bullet) * BULLET_COUNT);

    blocks = (Block*)malloc(BLOCK_COUNT * sizeof(Block));
    int i = 0;
    for (int y = 0; y < 8; y++) 
    {
        for (int x = 0; x < 8; x++) 
        {
            if (World[y][x] == 1 && i < BLOCK_COUNT)
            {
                blocks[i] = Block(x, y);
                i++;
            }
        }
    }
    return;
}

void loop()
{
    Recieve();

    switch (gameState)
    {
    // menu
    case 0:
        MenuUpdate();
        break;
    // game
    case 1:
        GameUpdate();
        break;
    }

    Transmit();
}

void MenuUpdate()
{
    if (digitalRead(ATK_PIN) == HIGH)
    {
        gameState = 1;
        ResetGame();
        // delay(300);
        //Transition(10);
        return;
    }

    oled.firstPage();
    do {
        if (player.Died)
        {
            oled.drawStr(Width / 2 - (oled.getStrWidth("YOU DIE!!!") / 2), 25, "YOU DIE!!!");
        }
        else if (opponent.Died)
        {
            oled.drawStr(Width / 2 - (oled.getStrWidth("YOU WIN!!!") / 2), 25, "YOU WIN!!!");
        }
        else
        {
            oled.drawStr(Width / 2 - (oled.getStrWidth("MENU") / 2), 25, "MENU");
        }

    } while (oled.nextPage());
    return;
}

void GameUpdate()
{
    if (opponent.Died || player.Died)
    {
        gameState = 0;
        //Transition(10);
        return;
    }
    
    cam.HandleInput();

    cam.GetCorners(blocks);
    //cam.OccludeCorners(blocks);
    cam.GenerateLineBuffer(blocks);
    cam.ClampLines();

    oled.firstPage();
    do {
        cam.DrawCall();
        cam.DrawOpponent();
        
        oled.drawLine(HMid -3, VMid, HMid +3, VMid);
        oled.drawLine(HMid, VMid +3, HMid, VMid -3);

        renderFreeRam();

    } while (oled.nextPage());

    return;
}

void Transition(int d)
{
    for (int i = 0; i < Width; i++)
    {
        do {
            oled.drawBox(0, 0, i, Height);
        } while (oled.nextPage());
    }
    return;
}

void ResetGame()
{
    player.Died = false;
    opponent.Died = false;
}

void renderFreeRam()
{
    float length = (2048 - freeRam())/2048.0f;
    length *= Width;
    oled.drawLine(0, 0, length, 0);
    return;
}

// this is not my code
void display_freeram() {
    Serial.print(F("- SRAM left: "));
    Serial.println(freeRam());
}

int freeRam() {
    extern int __heap_start,*__brkval;
    int v;
    return (int)&v - (__brkval == 0  
        ? (int)&__heap_start : (int) __brkval);  
}