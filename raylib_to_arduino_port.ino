#include "include/Block.hpp"
#include "include/BasicCam.hpp"
#include "include/Utils.hpp"

#include <U8glib.h>

#include <unistd.h>

Block* blocks;
BasicCam cam(3, 3, 90);

void setup()
{
    Serial.begin(9600);
    Serial.println(sizeof(int));
    Serial.println(sizeof(float));
    Serial.println(sizeof(Vector));
    Serial.println(sizeof(Line));
    Serial.println(sizeof(Block));
    Serial.println(sizeof(BasicCam));

    blocks = (Block*)malloc(BLOCK_COUNT * sizeof(Block));
    int i = 0;
    for (int y = 0; y < 8; y++) 
    {
        for (int x = 0; x < 8; x++) 
        {
            if (World[y][x] == 1)
            {
                blocks[i] = Block(x, y);
                i++;
                Serial.println("block const");
            }
        }
    }
}

void loop()
{
    Serial.println("loop");
    oled.firstPage();  
    do {
        cam.GetCorners(blocks);
        cam.MapToScreen(blocks);
        cam.OccludeCorners(blocks);
        cam.GenerateLineBuffer(blocks);
        cam.DrawCall();
        cam.HandleInput();
        Serial.println("loop - loop");
    } while(oled.nextPage());

    //free(blocks);

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