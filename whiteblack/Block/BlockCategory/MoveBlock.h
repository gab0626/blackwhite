#pragma once
#include "../BlockBase.h"

class MoveBlock : public BlockBase
{
public:

	MoveBlock();
	~MoveBlock();

	void update();
	void draw();
	void setup();

private:

};