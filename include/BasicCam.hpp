#ifndef BASICCAM_HPP
#define BASICCAM_HPP

#include "Block.hpp"

class BasicCam 
{
    Line* _lineBuffer;
    size_t _bufferSize = 0;

    float _fovPixels;
    int _depthEffect = 700; // lower value => increase shrinking at distance

    char _speed = 1;
    char _rotationSpeed = 2;

    Vector _velocity = {0, 0};

public:
    Vector Position;
    float Fov;
    int Direction = 180;

    BasicCam(int x, int z, float Fov);
    void GetCorners(Block* blocks);
    void MapToScreen(Block* blocks);
    void OccludeCorners(Block* blocks);
    void GenerateLineBuffer(Block* blocks);
    void ClampLines();
    void DrawCall();
    void HandleInput();

};

#endif

