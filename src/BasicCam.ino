
#include "../include/BasicCam.hpp"

#include "../include/Block.hpp"
#include "../include/Utils.hpp"

#include <math.h>

BasicCam::BasicCam(float x, float z, float Fov) 
    : Position({x * Scale, z * Scale}), Fov(Fov) 
{
    _fovPixels = Width / Fov;
    _lineBuffer = (Line*)malloc(sizeof(Line) * BLOCK_COUNT * 7);
    return;
}

BasicCam::~BasicCam()
{
    free(_lineBuffer);
    return;
}

void BasicCam::GetCorners(Block* blocks)
{
    for (size_t i = 0; i < BLOCK_COUNT; i++)
    {
        blocks[i].Distance = GetDistance(blocks[i].Middle, Position);
        for (size_t j = 0; j < 4; j++)
        {
            Vector2 cornerPos = blocks[i].Corners[j].Position;
            float cornerAngle = GetAngle(cornerPos, Position);
            float relativeAngle = cornerAngle + Direction;

            blocks[i].Corners[j].Direction = relativeAngle;

            float distance = GetDistance(cornerPos, Position);
            blocks[i].Corners[j].Distance = distance;
        }
    }
    return;
}

void BasicCam::MapToScreen(Block* blocks)
{
    for (size_t i = 0; i < BLOCK_COUNT; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            MappedCorner mCorner;
            mCorner.Distance = blocks[i].Corners[j].Distance;
            float dir = blocks[i].Corners[j].Direction;
            if (dir > 180)
                dir -= 360;

            mCorner.XOffset = HMid + dir * _fovPixels;

            blocks[i].MappedCorners[j] = mCorner;
        }
        blocks[i].SortCorners();
    }
    return;
}

void BasicCam::OccludeCorners(Block* blocks)
{
    SelectionSort(blocks);

    for (size_t i = 0; i < BLOCK_COUNT; i++)
    {
        blocks[i].GetVisible();
    }

    return;
}

void BasicCam::GenerateLineBuffer(Block* blocks)
{
    _bufferSize = 0;
    for (size_t i = 0; i < BLOCK_COUNT; i++)
    {
        Line line;
        int visibleCornerCount = 3;
        for (int j = 0; j < 3; j++)
        {
            if (blocks[i].VisibleCorners[j] ==  &blocks[i].MappedCorners[0] && j == 1)
            {
                visibleCornerCount -= 1;
                continue;
            }

            float height = _depthEffect / blocks[i].VisibleCorners[j]->Distance;
            float offset = blocks[i].VisibleCorners[j]->XOffset;
            if (offset > HMid)
            {
                offset -= Width;
            }

            line.From = {blocks[i].VisibleCorners[j]->XOffset, VMid - height};
            line.To = {blocks[i].VisibleCorners[j]->XOffset, VMid + height};
            _lineBuffer[_bufferSize] = line;
            _bufferSize++;
        }

        int index = _bufferSize - visibleCornerCount;
        for (int j = 0; j < visibleCornerCount -1; j++)
        {
            line.From = _lineBuffer[index + j].From;
            line.To = _lineBuffer[index + j +1].From;
            _lineBuffer[_bufferSize] = line;
            _bufferSize++;
            

            line.From = _lineBuffer[index + j].To;
            line.To = _lineBuffer[index + j +1].To;
            _lineBuffer[_bufferSize] = line;
            _bufferSize++;
        }
    }

    return;
}

void BasicCam::DrawCall()
{
    for (size_t i = 0; i < _bufferSize; i++)
    {
        Line line = _lineBuffer[i];
        if ((line.From.x > Width && line.To.x < 0) || (line.From.x < 0 && line.To.x > Width))
        {
            continue;
        }

        oled.drawLine(line.From.x, 
                line.From.y, 
                line.To.x, 
                line.To.y);
    }
    return;
}

void BasicCam::HandleInput()
{


/*
    if (IsKeyDown(KEY_UP))
    {
        _velocity.x = -cos(DegToRad(Direction)) * _speed;
        _velocity.y = sin(DegToRad(Direction)) * _speed;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        _velocity.x = -cos(DegToRad(Direction)) * -_speed;
        _velocity.y = sin(DegToRad(Direction)) * -_speed;
    }
    else
    {
        _velocity.x *= _friction;
        _velocity.y *= _friction;

        if (abs(_velocity.x) < 0.001)
            _velocity.x = 0;
        if (abs(_velocity.y) < 0.001)
            _velocity.y = 0;
    }

    Vector tempPos = Position;
    tempPos.x += _velocity.x;
    tempPos.y += _velocity.y;

    int gridX = (int)tempPos.x / Scale;
    int gridY = (int)tempPos.y / Scale;

    // Collision detection in world map
    if (gridX >= 0 && gridX < WorldSize && gridY >= 0 && gridY < WorldSize)
    {
        if (World[gridY][gridX] != 1)
        {
            Position = tempPos;
        }
        else
        {
            _velocity = {0, 0};
        }
    }
    else 
    {
        Position = tempPos;   
    }

    // Rotation
    if (IsKeyDown(KEY_LEFT))
    {
        Direction += _rotationSpeed;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        Direction -= _rotationSpeed;
    }

    if (Direction > 360)
    {
        Direction -= 360;
    }
    else if (Direction < 0)
    {
        Direction += 360;
    }

    return;
*/
}

