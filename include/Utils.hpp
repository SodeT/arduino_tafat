#ifndef UTILS_HPP
#define UTILS_HPP

#include "Block.hpp"
#include <U8glib.h>

#define pi 3.14159
#define VRX_PIN  A0
#define VRY_PIN  A1

class Block;

struct Vector
{
    int x;
    int y;
};

struct Line
{
    Vector From;
    Vector To;
};

struct MappedCorner
{
    int XOffset;
    char Distance;
};

struct Corner
{
    Vector Position;
    int Direction;
    char Distance;
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
    int x;
    int y;
};

const int Width = 128;
const int Height = 64;
const int HMid = Width / 2;
const int VMid = Height / 2;

const int Scale = 10;
const int WorldSize = 8;

const size_t BLOCK_COUNT = 6; 
const int World[WorldSize][WorldSize] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {1, 2, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0} 
};

float RadToDeg(float rad);
float DegToRad(float deg);
float GetAngle(Vector from, Vector to);
float GetDistance(Vector from, Vector to);
void SelectionSort(Block* blocks);
//bool InsideSpan(ViewportSpan span, float x);

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE);

#endif

