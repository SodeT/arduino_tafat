#include "include/Block.hpp"
#include "include/BasicCam.hpp"
#include "include/Utils.hpp"

#include <U8glib.h>

#include <unistd.h>

void setup()
{
}

void loop()
{

    Block* blocks = (Block*)malloc(BLOCK_COUNT * sizeof(Block));

    int i = 0;
    for (int y = 0; y < 8; y++) 
    {
        for (int x = 0; x < 8; x++) 
        {
            if (World[y][x] == 1)
            {
                blocks.[i] = new Block(x, y);
                i++;
            }
        }
    }

    BasicCam cam(3, 3, 90);

    oled.firstPage();  
    do {
        cam.GetCorners(blocks);
        cam.MapToScreen(blocks);
        cam.OccludeCorners(blocks);
        cam.GenerateLineBuffer(blocks);
        cam.DrawCall();
        cam.HandleInput();
    } while(oled.nextPage());

    return 0;
}

