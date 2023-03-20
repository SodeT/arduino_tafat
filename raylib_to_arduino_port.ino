#include "include/Block.hpp"
#include "include/BasicCam.hpp"
#include "include/Utils.hpp"
#include <U8glib.h>
#include <unistd.h>

Block* blocks;
BasicCam cam(3, 2, 90);

void setup()
{
    pinMode(ATK_PIN, INPUT);
    Serial.begin(11520);
    oled.setFont(u8g_font_osb18);

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
    cam.Recieve();

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

    cam.Transmit();
}

void MenuUpdate()
{
    if (digitalRead(ATK_PIN) == HIGH)
    {
        gameState = 1;
        ResetGame();
        Delay(300);
        //Transition(10);
        return;
    }

    oled.firstPage();
    do {
        if (opponent.Won)
        {
            oled.drawStr(Width / 2 - (oled.getStrWidth("YOU DIE!!!") / 2), 30, "YOU DIE!!!");
        }
        else if (player.Won)
        {
            oled.drawStr(Width / 2 - (oled.getStrWidth("YOU WIN!!!") / 2), 30, "YOU WIN!!!");
        }
        else
        {
            oled.drawStr(Width / 2 - (oled.getStrWidth("MENU") / 2), 30, "MENU");
        }

    } while (oled.nextPage());
    return;
}

void GameUpdate()
{
    if (opponent.Won || player.Won)
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
    } while (oled.nextPage());

    return;
}

void Transition(int d)
{
    for (int i = -Width; i < 0; i++)
    {
        do {
            oled.drawBox(i, 0, Width, Height);
        } while (oled.nextPage());
    }
    return;
}

void ResetGame()
{
    player.Won = false;
    opponent.Won = false;
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