float RadToDeg(float rad)
{
    return rad * (180/pi);
}

float DegToRad(float deg)
{
    return deg / (180/pi);
}

float GetAngle(Vector from, Vector to)
{
    float xDiff = to.x - from.x;
    float yDiff = to.y - from.y;

    float radAngle = atan2(yDiff, xDiff);
    float degAngle = RadToDeg(radAngle);

    return degAngle;
}

float GetDistance(Vector from, Vector to)
{
    Vector diff;
    diff.x = from.x - to.x;
    diff.y = from.y - to.y; 

    float c2 = pow(diff.x, 2) + pow(diff.y, 2);
    return sqrt(c2);
}

FVector ToFVector(Vector vec)
{
    FVector vec2;
    vec2.x = vec.x;
    vec2.y = vec.y;
    return vec2;
}

Vector ToVector(FVector vec)
{
    Vector vec2;
    vec2.x = vec.x;
    vec2.y = vec.y;
    return vec2;
}

void Recieve()
{
    if (Serial.available())
    {
        Serial.readBytes(opponentPointer, sizeof(PlayerInfo));
        opponent = *(PlayerInfo*)opponentPointer;
    }
    return;
}

void Transmit()
{   
    player.x = cam.Position.x;
    player.y = cam.Position.y;

    Serial.write(playerPointer, sizeof(PlayerInfo));
    return;
}