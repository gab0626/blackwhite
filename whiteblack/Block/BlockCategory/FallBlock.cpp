#include "FallBlock.h"

FallBlock::FallBlock()
{
	setup();
}

FallBlock::~FallBlock()
{

}

void FallBlock::setup()
{
	block.size = Vec2f(static_cast<float>(BLOCKSIZE::WIDTH),
		static_cast<float>(BLOCKSIZE::HEIGHT));

	block.vec = Vec2f(0.0f, -10.0f);

	fall_flag = false;
	fall_count = 60;
}

void FallBlock::update()
{
	if (fall_flag == true)
	{
		fall_count--;
	}

	if (fall_count <= 0)
	{
		block.pos.y() += block.vec.y();
	}

	/*if (block.pos.y() <= (env.viewSize.y() / 2) - block.size.y() * 5)
	{
		fall_flag = false;
	}*/
}

void FallBlock::draw()
{
	if (color_type == CONDITION::WHITE)
		drawTextureBox(block.pos.x(), block.pos.y(), block.size.x(), block.size.y(), 0, 0, 32, 32, image_white);

	if (color_type == CONDITION::BLACK)
		drawTextureBox(block.pos.x(), block.pos.y(), block.size.x(), block.size.y(), 0, 0, 32, 32, image_black);
}
