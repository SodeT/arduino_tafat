
#ifndef BASICCAM_HPP
#define BASICCAM_HPP

#include "Block.hpp"

class BasicCam 
{
private:
    Line* _lineBuffer;
    size_t _bufferSize = 0;

    bool* _occlusionMap;

    float _fovPixels;

    int _speed = 4;
    int _rotationSpeed = 11;

    FVector _velocity = {0, 0};

public:
    FVector Position;
    int Direction = 180;

    BasicCam();
    void GetCorners(Block* blocks);
    void GenerateLineBuffer(Block* blocks);
    void ClampLines();
    void DrawCall();
    void HandleInput();

    void DrawOpponent();

};

#endif

