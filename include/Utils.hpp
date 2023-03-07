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

struct FVector
{
    float x;
    float y;
};

struct BlockCullInfo
{
    char xCull : 2;
    char yCull : 2;
    char padding : 4;
};

struct Line
{
    Vector From;
    Vector To;
};

struct MappedCorner
{
    int XOffset;
    int Distance;
};

struct Corner
{
    Vector Position;
    int Direction;
    int Distance;
};

struct ViewportSpan
{
    int From;
    int To;
};

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

const size_t BLOCK_COUNT = 3;       // Change this variable to malloc more blocks, just changing the world map wont alloc more memory
const int World[WorldSize][WorldSize] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0} 
};

float RadToDeg(float rad);
float DegToRad(float deg);

float GetAngle(Vector from, Vector to);
float GetDistance(Vector from, Vector to);

float GetAngle(FVector from, FVector to);
float GetDistance(FVector from, FVector to);

FVector ToFVector(Vector vec);
Vector ToVector(FVector vec);

void SelectionSort(Block* blocks);
bool InsideSpan(ViewportSpan* span, int x);

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE);

#endif

