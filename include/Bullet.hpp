#ifndef BULLET_HPP
#define BULLET_HPP

class Bullet
{
private:
    Vector _position;
    Vector _velocity;

public:
    bool Active = true;

    Bullet(int x, int y, float direction);
    void DrawBullet();
    void UpdateBullet();
};

#endif