#include "MoveBlock.h"

MoveBlock::MoveBlock()
{
	setup();
}

MoveBlock::~MoveBlock()
{

}

void MoveBlock::setup()
{
	block.size = Vec2f(static_cast<float>(BLOCKSIZE::WIDTH),
		static_cast<float>(BLOCKSIZE::HEIGHT));
	
	block.vec = Vec2f::Zero();

	move_flag = false;
}

void MoveBlock::update()
{
	if (move_flag == true)
	{
		block.pos += block.vec;
	}
}

void MoveBlock::draw()
{
	if (color_type == CONDITION::WHITE)
		drawTextureBox(block.pos.x(), block.pos.y(), block.size.x(), block.size.y(), 0, 0, 32, 32, image_white);

	if (color_type == CONDITION::BLACK)
		drawTextureBox(block.pos.x(), block.pos.y(), block.size.x(), block.size.y(), 0, 0, 32, 32, image_black);
}
