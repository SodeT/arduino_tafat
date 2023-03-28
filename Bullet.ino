Bullet::Bullet(int x, int y, int direction)
{
    _position = {x * Scale, y * Scale};
    _velocity.x = -cos(DegToRad(direction));
    _velocity.y = sin(DegToRad(direction));
    return;
}

void Bullet::DrawBullet()
{
    if (!Active)
    {
        return;
    }

    Vector playerPos = ToVector(cam.Position);

    int distance = GetDistance(_position, playerPos);
    float dir = GetAngle(_position, playerPos) + cam.Direction;
    
    if (dir > 180)
        dir -= 360;

    int xOffset = HMid + dir * _fovPixels;
    float height = (_depthEffect / distance) / 2;

    if (xOffset < 0 || xOffset > Width)
    {
        return;
    }

    oled.drawPixel(xOffset, VMid);
    return;
}

void Bullet::UpdateBullet()
{
    if (!Active)
    {
        return;
    }

    _position.x += _velocity.x;
    _position.y += _velocity.y;

    int gridX = _position.x / Scale;
    int gridY = _position.y / Scale;

    // Collision detection in world map
    if (gridX >= 0 && gridX < WorldSize && gridY >= 0 && gridY < WorldSize)
    {
        if (World[gridY][gridX] == 1)
        {
            Active = false;
        }
    }

    return;
}
