
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
    int _depthEffect = 700; // lower value => increased shrinking at distance

    int _speed = 1;
    int _rotationSpeed = 2;

    FVector _velocity = {0, 0};

public:
    FVector Position;
    float Fov;
    int Direction = 180;

    BasicCam(int x, int y, float Fov);
    void GetCorners(Block* blocks);
    void OccludeCorners(Block* blocks);
    void GenerateLineBuffer(Block* blocks);
    void ClampLines();
    void DrawCall();
    void HandleInput();
    void DrawOpponent();

};

#endif

