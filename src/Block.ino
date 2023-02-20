#include "../include/Block.hpp"

#include "../include/Utils.hpp"

Block::Block(float x, float z) 
{
	Corners = (Corner*)malloc(4 * sizeof(Corner));
	MappedCorners = (MappedCorner*)malloc(4 * sizeof(MappedCorner));

	Middle.x = x * Scale + Scale / 2;
	Middle.y = z * Scale + Scale / 2;

	Corners[0].Position.x = x * Scale;
	Corners[0].Position.y = z * Scale;

	Corners[1].Position.x = x * Scale + Scale;
	Corners[1].Position.y = z * Scale;

	Corners[2].Position.x = x * Scale;
	Corners[2].Position.y = z * Scale + Scale;

	Corners[3].Position.x = x * Scale + Scale;
	Corners[3].Position.y = z * Scale + Scale;

	return;
}

Block::~Block()
{
	free(Corners);
	free(MappedCorners);
	return;
}

// algorithm from https://en.wikipedia.org/wiki/Sorting_network
void Block::SortCorners()
{
	MappedCorner temp;

	if (MappedCorners[0].XOffset > MappedCorners[2].XOffset)
	{
		temp = MappedCorners[0];
		MappedCorners[0] = MappedCorners[2];
		MappedCorners[2] = temp;
	}

	if (MappedCorners[1].XOffset > MappedCorners[3].XOffset)
	{
		temp = MappedCorners[1];
		MappedCorners[1] = MappedCorners[3];
		MappedCorners[3] = temp;
	}

	if (MappedCorners[0].XOffset > MappedCorners[1].XOffset)
	{
		temp = MappedCorners[0];
		MappedCorners[0] = MappedCorners[1];
		MappedCorners[1] = temp;
	}

	if (MappedCorners[2].XOffset > MappedCorners[3].XOffset)
	{
		temp = MappedCorners[2];
		MappedCorners[2] = MappedCorners[3];
		MappedCorners[3] = temp;
	}

	if (MappedCorners[1].XOffset > MappedCorners[2].XOffset)
	{
		temp = MappedCorners[1];
		MappedCorners[1] = MappedCorners[2];
		MappedCorners[2] = temp;
	}
	return;
}

void Block::GetVisible()
{
	VisibleCorners[0] = &MappedCorners[0];
	VisibleCorners[2] = &MappedCorners[3];
	if (MappedCorners[1].Distance < MappedCorners[0].Distance)
	{
		VisibleCorners[1] = &MappedCorners[1];
	}
	else if (MappedCorners[2].Distance < MappedCorners[0].Distance)
	{
		VisibleCorners[1] = &MappedCorners[2];   
	}
	else 
	{
		VisibleCorners[1] = &MappedCorners[0];
	}
	
	return;
}