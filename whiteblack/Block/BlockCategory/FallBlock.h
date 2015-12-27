#pragma once
#include "../BlockBase.h"

class FallBlock : public BlockBase
{
public:

	FallBlock();
	~FallBlock();

	void update();
	void draw();
	void setup();

	bool getFallFlag(){ return fall_flag; }

private:

	int fall_count;

};