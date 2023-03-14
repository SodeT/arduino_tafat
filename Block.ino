
Block::Block(int x, int y) 
{
	MappedCorners = (MappedCorner*)malloc(4 * sizeof(MappedCorner));

	Position.x = x * Scale;
	Position.y = y * Scale;
	return;
}

// algorithm from https://en.wikipedia.org/wiki/Sorting_network
void Block::SortCorners()
{
	MappedCorner temp;

	if (MappedCorners[0].XOffset >= MappedCorners[2].XOffset)
	{
		temp = MappedCorners[0];
		MappedCorners[0] = MappedCorners[2];
		MappedCorners[2] = temp;
	}

	if (MappedCorners[1].XOffset >= MappedCorners[3].XOffset)
	{
		temp = MappedCorners[1];
		MappedCorners[1] = MappedCorners[3];
		MappedCorners[3] = temp;
	}

	if (MappedCorners[0].XOffset >= MappedCorners[1].XOffset)
	{
		temp = MappedCorners[0];
		MappedCorners[0] = MappedCorners[1];
		MappedCorners[1] = temp;
	}

	if (MappedCorners[2].XOffset >= MappedCorners[3].XOffset)
	{
		temp = MappedCorners[2];
		MappedCorners[2] = MappedCorners[3];
		MappedCorners[3] = temp;
	}

	if (MappedCorners[1].XOffset >= MappedCorners[2].XOffset)
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
		VisibleCorners[1] = nullptr;
	}
	
	return;
}