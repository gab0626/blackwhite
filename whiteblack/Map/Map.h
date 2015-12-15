
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

private:

	std::vector<std::vector<BlockBase*>> map_chip;
	Vec2f player_start_pos;

	void mapDelete();

    Vec2f collsion(Object player, Object block, bool, bool);
    
};


