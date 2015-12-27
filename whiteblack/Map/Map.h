
#include "../Top/Top.h"
#include "../Block/BlockBase.h"
#include "../Block/BlockCategory/NormalBlock.h"
#include "../Block/BlockCategory/MoveBlock.h"
#include "../Block/BlockCategory/FallBlock.h"
#include "../Block/BlockCategory/DoubleBlock.h"




class Map
{
public:
    Map();
    void update();
    void draw();
	//プレイするstageの番号を引数にください
    void setup(int);

	Vec2f getPlayerStartPos() const;

	//struct型のplayerとplayerのconditionを引数でもらって
	//blockにめり込んだ文の値を(＋)の値で返します
	Vec2f isHitPlayerToBlock(Object, CONDITION);

    Vec2f getGoalPos();
    Vec2f getGoalSize();

	void isHitMoveBlockToBlock();

	//選択されているマップチップの座標を引数で獲得して
	//枠を光らせる
	void selected(Vec2i);

	//選択されているマップチップの座標を
	//引数で獲得して吸収します
	bool sucked(Vec2i);

	//選択されているマップチップの座標を
	//引数で獲得して放出します
	bool released(Vec2i);

    //マップの左下の位置を返す関数
    Vec2f pos();
    //マップ全体の大きさを返す関数
    Vec2f size();

private:

	std::vector<std::vector<BlockBase*>> map_chip;
	Vec2f player_start_pos;
    Vec2f goal_pos;
    Vec2f goal_size;

	void mapDelete();
    Vec2f collsion(Object player, Object block, bool, bool);

    
    Texture blackblock;
    Texture whiteblock;
    Texture stripeblock;
    Texture doubleblock_white;
    Texture doubleblock_black;
    Texture downblock_black;
    Texture downblock_white;
    
    Texture moveblock_up;
    Texture moveblock_down;
    Texture moveblock_left;
    Texture moveblock_right;
    Texture movedown_white;
    Texture moveleft_white;
    Texture moveright_white;
    Texture moveup_white;

};


