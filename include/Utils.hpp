#ifndef UTILS_HPP
#define UTILS_HPP

#include "Block.hpp"
#include <U8glib.h>

#define pi 3.14159
#define VRX_PIN  A0
#define VRY_PIN  A1
#define ATK_PIN 2

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

struct Line
{
    Vector From;
    Vector To;
};

struct MappedCorner
{
    int XOffset;
    byte Distance;
};

struct Corner
{
    Vector Position;
    int Direction;
    byte Distance;
};

struct PlayerInfo 
{
    int x;
    int y;
    bool Won;
};

const byte Width = 128;
const byte Height = 64;
const byte HMid = Width / 2;
const byte VMid = Height / 2;

const byte Scale = 10;
const byte WorldSize = 8;

const size_t BLOCK_COUNT = 8;       // Change this variable to malloc more blocks, just changing the world map wont alloc more memory
const byte World[WorldSize][WorldSize] = {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0} 
};

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE);

PlayerInfo player = {3, 2, false};
byte* playerPointer = (byte*)&player;
PlayerInfo opponent = {0, 0, false};
byte* opponentPointer = (byte*)&opponent;

// 0 = menu, 1 = game 
byte gameState = 0;


float RadToDeg(float rad);
float DegToRad(float deg);

float GetAngle(Vector from, Vector to);
float GetDistance(Vector from, Vector to);

float GetAngle(FVector from, FVector to);
float GetDistance(FVector from, FVector to);

FVector ToFVector(Vector vec);
Vector ToVector(FVector vec);

void SelectionSort(Block* blocks);


#endif

