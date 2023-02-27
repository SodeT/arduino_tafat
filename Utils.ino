
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
    size_t index; 
    for (size_t i = 0; i < BLOCK_COUNT -1; i++)
    {
        index = i; 
        for (size_t j = i+1; j < BLOCK_COUNT; j++)
        {
            if (blocks[j].Distance < blocks[index].Distance)
            {
                index = j;
            }
        }

        if (index != i)
        {
            Block b = blocks[i];
            blocks[i] = blocks[index];
            blocks[index] = b;
        }
    }
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


