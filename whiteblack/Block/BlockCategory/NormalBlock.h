#pragma once
#include "../BlockBase.h"

class NormalBlock : public BlockBase
{
public:

	NormalBlock();
	~NormalBlock();

	virtual void setImageStripe(Texture image){ image_stripe = image; };

	void update();
	void draw();
	void setup();

private:

	Texture image_stripe;

};