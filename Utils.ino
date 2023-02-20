
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
    float zDiff = to.y - from.y;

    float radAngle = atan2(zDiff, xDiff);
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

void SelectionSort(Block* blocks) 
{ 
    Serial.println("Debug 1");
    size_t index; 
    for (size_t i = 0; i < BLOCK_COUNT -1; i++)
    {
        Serial.println("Debug 2");
        index = i; 
        for (size_t j = i+1; j < BLOCK_COUNT; j++)
        {
            Serial.println("Debug 3");
            if (blocks[j].Distance < blocks[index].Distance)
            {
                Serial.println("debug 4");
                index = j;
            }
        }

        Serial.println("Debug 5");
        if (index != i)
        {
            Serial.println("debug 6");
            Block b = blocks[i];
            Serial.println("loosefp");
            blocks[i] = blocks[index];
            Serial.println("kdjg");
            Serial.println(index);
            blocks[index] = b;
            Serial.println("loop");
        }
        Serial.println("loopedy");
    }
    Serial.println("lokdrtugöoadrihop");
    return;
} 

/*
bool InsideSpan(ViewportSpan span, float x)
{
    if (x > span.From && x < span.To)
    {
        return true;
    }
    return false;
}
*/


