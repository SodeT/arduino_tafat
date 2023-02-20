#ifndef BASICCAM_HPP
#define BASICCAM_HPP

#include "Block.hpp"

class BasicCam 
{
    Line* _lineBuffer;
    size_t _bufferSize = 0;

    float _fovPixels;
    int _depthEffect = 700; // lower value => increase shrinking at distance

    float _speed = 0.3;
    float _rotationSpeed = 2;

    Vector _velocity = {0, 0};
    float _friction = 0.9;

public:
    Vector Position;
    float Fov;
    float Direction = 180;

    BasicCam(float x, float z, float Fov);
    ~BasicCam();
    void GetCorners(Block* blocks);
    void MapToScreen(Block* blocks);
    void GenerateLineBuffer(Block* blocks);
    void OccludeCorners(Block* blocks);
    void DrawCall();
    void HandleInput();

};

#endif

