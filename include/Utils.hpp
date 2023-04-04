#ifndef UTILS_HPP
#define UTILS_HPP

#include "Block.hpp"
#include <U8glib.h>

#define pi 3.14159
#define VRX_PIN  A0
#define VRY_PIN  A1
#define CHASE_PIN 2

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
    bool chasing : 1;
    bool waitingToStart : 1;
    
};

const int JoystickHigh = 768;
const int JoystickLow = 256;

const byte Width = 128;
const byte Height = 64;
const byte HMid = Width / 2;
const byte VMid = Height / 2;

const int Fov = 90;
const int DepthEffect = 700; // lower value => increased shrinking at distance
const float FovPixels = Width / Fov;

const byte Scale = 20;
const byte WorldSize = 8;

const size_t BLOCK_COUNT = 10;       // Change this variable to malloc more blocks, just changing the world map wont alloc more memory
const byte World[WorldSize][WorldSize] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 2, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 3, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0} 
};

const byte TagDistance = 1 * Scale;
const FVector ChaseStart = {8 * Scale, 8 * Scale};
const FVector RunStart = {0 * Scale, 0 * Scale};

const int TRANSMIT_INTERVAL = 2;

float RadToDeg(float rad);
float DegToRad(float deg);

float GetAngle(Vector from, Vector to);
float GetDistance(Vector from, Vector to);

float GetAngle(FVector from, FVector to);
float GetDistance(FVector from, FVector to);

FVector ToFVector(Vector vec);
Vector ToVector(FVector vec);

void Recieve();
void Transmit();

void RecieveSetup();


#endif