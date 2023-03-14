#include "include/Block.hpp"
#include "include/BasicCam.hpp"
#include "include/Utils.hpp"
#include <U8glib.h>
#include <unistd.h>
#include <SerialTransfer.h>

Block* blocks;
BasicCam cam(3, 2, 90);

void setup()
{
    Serial.begin(11520);
    serialTrans.begin(Serial);

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
    oled.firstPage();
    do {
        if (serialTrans.available()) 
        {
            serialTrans.rxObj(Opponent);
        }
        cam.HandleInput();

        cam.DrawOpponent();

        cam.GetCorners(blocks);
        //cam.OccludeCorners(blocks);
        cam.GenerateLineBuffer(blocks);
        cam.ClampLines();
        cam.DrawCall();
        
        oled.drawLine(HMid -3, VMid, HMid +3, VMid);
        oled.drawLine(HMid, VMid +3, HMid, VMid -3); 

    } while(oled.nextPage());
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