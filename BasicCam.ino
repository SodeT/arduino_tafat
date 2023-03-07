
BasicCam::BasicCam(int x, int z, float Fov) 
    : Position({x * Scale, z * Scale}), Fov(Fov) 
{
    _fovPixels = Width / Fov;
    _lineBuffer = (Line*)malloc(sizeof(Line) * BLOCK_COUNT * 7);
    _occlusionMap = (ViewportSpan*)malloc(sizeof(ViewportSpan) * BLOCK_COUNT);
    return;
}

void BasicCam::GetCorners(Block* blocks)
{
    for (size_t i = 0; i < BLOCK_COUNT; i++)
    {
        blocks[i].Distance = GetDistance(blocks[i].Middle, ToVector(Position));
        for (size_t j = 0; j < 4; j++)
        {
            Vector cornerPos = blocks[i].Corners[j].Position;
            float cornerAngle = GetAngle(cornerPos, ToVector(Position));
            float relativeAngle = cornerAngle + Direction;

            blocks[i].Corners[j].Direction = relativeAngle;

            float distance = GetDistance(cornerPos, ToVector(Position));
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
        blocks[i].GetVisible();
    }
    return;
}

/*
This is very inneficcient
do occlusion culling based on neighboring blocks from the World[8][8] variable

*/

void BasicCam::OccludeCorners(Block* blocks)
{
    SelectionSort(blocks);

    ViewportSpan viewportSpan; 
    for (size_t i = 0; i < BLOCK_COUNT; i++) 
    {
        Block b = blocks[i];
        int blockX = b.Corners[0].Position.x / Scale;
        int blockY = b.Corners[0].Position.y / Scale;

   

        viewportSpan.From = blocks[i].VisibleCorners[0]->XOffset;
        viewportSpan.To = blocks[i].VisibleCorners[2]->XOffset;
        _occlusionMap[i] = viewportSpan;
        _occlusionSize++;
    
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
            if (blocks[i].VisibleCorners[j] ==  nullptr) //&blocks[i].MappedCorners[0] && j == 1)
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

void BasicCam::ClampLines()
{
    for (size_t i = 0; i < _bufferSize; i++)
    {
        if((_lineBuffer[i].From.x < 0 && _lineBuffer[i].To.x < 0) ||
            (_lineBuffer[i].From.x > Width && _lineBuffer[i].To.x > Width))
        {
            continue;
        }

        
        if (_lineBuffer[i].From.x < 0)
        {
            int k = (_lineBuffer[i].To.y - _lineBuffer[i].From.y) / (_lineBuffer[i].To.x - _lineBuffer[i].From.x);
            int dX = _lineBuffer[i].From.x;
            int dY = dX * k + _lineBuffer[i].From.y;
            _lineBuffer[i].From.x = 0;
            _lineBuffer[i].From.y = dY;
        }
        else if (_lineBuffer[i].To.x > Width)
        {
            int k = (_lineBuffer[i].To.y - _lineBuffer[i].From.y) / (_lineBuffer[i].From.x - _lineBuffer[i].To.x);
            int dX = _lineBuffer[i].To.x;
            int dY = dX * k + _lineBuffer[i].To.y;
            _lineBuffer[i].To.x = Width;
            _lineBuffer[i].To.y = dY;
        }

        _lineBuffer[i].From.y = max(_lineBuffer[i].From.y, 0);
        _lineBuffer[i].From.y = min(_lineBuffer[i].From.y, Height -1);

        _lineBuffer[i].To.y = max(_lineBuffer[i].To.y, 0);
        _lineBuffer[i].To.y = min(_lineBuffer[i].To.y, Height -1);
        

    }
    return;
}

void BasicCam::DrawCall()
{
    for (size_t i = 0; i < _bufferSize; i++)
    {
        Line line = _lineBuffer[i];
        if (line.From.x < 0 || line.To.x >= Width)
        {
            continue;
        }
        if (line.From.y < 0 && line.To.y >= Height)
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
    int xValue = analogRead(VRX_PIN);
    int yValue = analogRead(VRY_PIN);

    if (yValue <= 256)
    {
        _velocity.x = -cos(DegToRad(Direction)) * _speed;
        _velocity.y = sin(DegToRad(Direction)) * _speed;
    }
    else if (yValue >= 768)
    {
        _velocity.x = -cos(DegToRad(Direction)) * -_speed;
        _velocity.y = sin(DegToRad(Direction)) * -_speed;
    }
    else
    {
        _velocity.x = 0;
        _velocity.y = 0;
    }

    FVector tempPos = Position;
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
    if (xValue <= 256)
    {
        Direction += _rotationSpeed;
    }
    else if (xValue >= 768)
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
}

