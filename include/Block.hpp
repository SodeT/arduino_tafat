#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Utils.hpp"

struct MappedCorner;
struct Corner;

class Block 
{
public:
    Vector Position;
    byte Distance;
    MappedCorner* MappedCorners; 
    MappedCorner* VisibleCorners[3];
    Block(int x, int y);

    void SortCorners();
    void GetVisible();
};

#endif

