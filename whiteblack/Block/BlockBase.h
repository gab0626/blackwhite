#pragma once
#include "../Top/Top.h"

class BlockBase
{
public:

	BlockBase(){};
	virtual ~BlockBase(){};

    virtual void update(){};
    virtual void draw(){};
    virtual void setup(){};

	virtual void setImageWhite(Texture image){ image_white = image; }
	virtual void setImageBlack(Texture image){ image_black = image; }
	virtual void setImageStripe(Texture image){};
	virtual void setPos(Vec2f _pos){ block.pos = _pos; }
	virtual void setVec(Vec2f _vec){ block.vec = _vec; }
	virtual void setStatus(BLOCK _block){ status = _block; }
	virtual void setCondition(CONDITION _type){ color_type = _type; }

	virtual void setFallFlag(bool fall_flag){ this->fall_flag = fall_flag; }
	virtual void setMoveFlag(bool move_flag){ this->move_flag = move_flag; }

	virtual Vec2f getPos() { return block.pos; }
	virtual Vec2f getSize() { return block.size; }
	virtual Vec2f getVectol() { return block.vec; }

    Object getObject(){

		Object obj;
		obj.pos = block.pos;
		obj.size = block.size;
		obj.vec = Vec2f(block.vec.x()*move_flag, block.vec.y()*move_flag);

		return obj;
	}
	virtual BLOCK getStatus(){ return status; }
	virtual CONDITION getCondition(){ return color_type; }

	virtual bool getFallFlag(){ return false; }
	virtual bool getMoveFlag(){ return false; }

protected:

	CONDITION color_type;
	BLOCK status;
	Object block;
	Texture image_white;
	Texture image_black;
	bool fall_flag = false;
	bool move_flag = false;
};