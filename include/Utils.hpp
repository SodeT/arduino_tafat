#ifndef UTILS_HPP
#define UTILS_HPP

#include "Block.hpp"

#define pi 3.14159

class Block;


U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE);

const int Width = 128;
const int Height = 64;
const int HMid = Width / 2;
const int VMid = Height / 2;
const int Scale = 10;
const int WorldSize = 8;
const size_t BLOCK_COUNT = 3; 
const int World[WorldSize][WorldSize] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0} 
};

float RadToDeg(float rad);
float DegToRad(float deg);
float GetAngle(Vector from, Vector to);
float GetDistance(Vector from, Vector to);
void SelectionSort(Block* blocks);
//bool InsideSpan(ViewportSpan span, float x);

struct Line
{
    Vector From;
    Vector To;
};

struct MappedCorner
{
    float XOffset;
    float Distance;
};

struct Corner
{
    Vector Position;
    float Direction;
    float Distance;
};

struct Vector
{
    float x;
    float y;
};

/*
struct ViewportSpan
{
    float From;
    float To;
};
*/

struct Packet
{
    char State : 2; // 0 = await, 1 = playing, 2 = I won, 3 = you won
    char Damage : 6;
    float x;
    float y;
};


#endif

