#include "include/Block.hpp"
#include "include/BasicCam.hpp"
#include "include/Utils.hpp"

#include <U8glib.h>
#include <unistd.h>

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE);

PlayerInfo player = {0, 0};
byte* playerPointer = (byte*)&player;
PlayerInfo opponent = {0, 0};
byte* opponentPointer = (byte*)&opponent;

bool chasing = false;

// 0 = ongoing, 1 = won, 2 = lost
byte playerState = 0;

// 0 = menu, 1 = game 
byte gameState = 0;

Block* blocks;
BasicCam cam;

float showInfoTimer = 0;

bool justEnteredMenu = false;

int transmitTime = 0;

void setup()
{
    Serial.begin(9600);
    oled.setFont(u8g_font_osb18);
    pinMode(CHASE_PIN, INPUT);

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
    
    chasing = (digitalRead(CHASE_PIN) == HIGH);
    
    SetPositions();
    
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

    transmitTime += 1;
    if (transmitTime >= TRANSMIT_INTERVAL)
    {
        Transmit();
        transmitTime = 0;
    }
}

void MenuUpdate()
{
    oled.firstPage();
    do {
        switch (playerState)
        {
        // ongoing
        case 0:
            oled.drawStr(Width / 2 - (oled.getStrWidth("MENU") / 2), 25, "MENU");
            break;
        // won
        case 1:
            oled.drawStr(Width / 2 - (oled.getStrWidth("YOU WON!!!") / 2), 20, "YOU WON!!!");
            break;
        // lost
        case 2:
            oled.drawStr(Width / 2 - (oled.getStrWidth("YOU LOST!!!") / 2), 20, "YOU LOST!!!");
            break;
        }

    } while (oled.nextPage());

    if (justEnteredMenu)
    {
        delay(2000);
        justEnteredMenu = false;
    }

    if (analogRead(VRY_PIN) < JoystickLow)
    {
        gameState = 1;
        ResetGame();
        return;
    }

    return;
}

void GameUpdate()
{
    
    cam.HandleInput();

    cam.GetCorners(blocks);
    cam.GenerateLineBuffer(blocks);
    cam.ClampLines();

    oled.firstPage();
    do {
        cam.DrawCall();
        cam.DrawOpponent();
        
        oled.drawLine(HMid -3, VMid, HMid +3, VMid);
        oled.drawLine(HMid, VMid +3, HMid, VMid -3);

        if (showInfoTimer < 1)
        {
            if (chasing)
                oled.drawStr(Width / 2 - (oled.getStrWidth("CHASE") / 2), 25, "CHASE");
            else
                oled.drawStr(Width / 2 - (oled.getStrWidth("RUN") / 2), 25, "RUN");
            showInfoTimer += 0.01;
        }

        renderFreeRam();

    } while (oled.nextPage());

    if (GetDistance(Vector{player.x, player.y}, Vector{opponent.x, opponent.y}) < TagDistance)
    {
        if (chasing)
        {
            playerState = 1;
        }
        else
        {
            playerState = 2;
        }
           
        gameState = 0;
        justEnteredMenu = true;
        //Transition();
        return;
    }
    
    return;
}

void Transition()
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
    showInfoTimer = 0;
    SetPositions();
    playerState = 0;
    return;
}

void SetPositions()
{
    if (chasing)
    {
        cam.Position = ChaseStart;
        player.x = cam.Position.x;
        player.y = cam.Position.y;

        opponent.x = RunStart.x;
        opponent.y = RunStart.y;
    }
    else 
    {
        cam.Position = RunStart;
        player.x = cam.Position.x;
        player.y = cam.Position.y;

        opponent.x = ChaseStart.x;
        opponent.y = ChaseStart.y;
    }
    return;
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