#include "DoubleBlock.h"

DoubleBlock::DoubleBlock()
{
	setup();
}

DoubleBlock::~DoubleBlock()
{

}

void DoubleBlock::setup()
{
	block.size = Vec2f(static_cast<float>(BLOCKSIZE::WIDTH),
		static_cast<float>(BLOCKSIZE::HEIGHT));

	block.vec = Vec2f::Zero();
}

void DoubleBlock::update()
{

}

void DoubleBlock::draw()
{
	if (color_type == CONDITION::WHITE)
		drawTextureBox(block.pos.x(), block.pos.y(), block.size.x(), block.size.y(),0,0,32,32, image_white);

	if (color_type == CONDITION::BLACK)
		drawTextureBox(block.pos.x(), block.pos.y(), block.size.x(), block.size.y(), 0, 0, 32, 32, image_black);
}
