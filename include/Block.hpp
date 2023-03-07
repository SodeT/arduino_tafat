#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Utils.hpp"

struct MappedCorner;
struct Corner;

class Block 
{
public:
    BlockCullInfo CullInfo;
    Vector Middle;
    char Distance;
    MappedCorner* VisibleCorners[3];
    Corner* Corners;
    MappedCorner* MappedCorners; 
    Block(int x, int z);

    void SortCorners();
    void GetVisible();
};

#endif

