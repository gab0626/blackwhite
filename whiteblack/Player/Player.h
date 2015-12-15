#include "../Top/Top.h"
///藤吉
//ここはいつも通りのアクションの処理を描いて
///プレイヤーの仕様をよく見てやってね
///プレイヤーの大きさはブロックの一回り小さい
//(140,190)くらいでいいと思う
//playerは選択しているマス目が合ってVec2iで
//プレイヤーの位置だったら（０，０）みたいな
//プレイヤーのみぎだったら（1,0）みたいな
//ギャーみたいな
//もちろんgetもね
//後選択範囲がプレイヤーから2マス先までだよ
//吸収放出した時にtrueを返すゲッター
//
//キーは移動はZC選択はWASDジャンプはK吸収はJ
//放出はL全変えはIでとりあえずは頼む
//プレイヤーの初期位置はマップからもらってくる予定だ
//

enum class SELECTDIR{
	Y,
	X,
	NON
};


class Player
{
public:
    Player();
    void update();
    void draw();
    void setup(Vec2f pos);
	void move();
	void dirUpdate(SELECTDIR&);
	void animation();
	SELECTDIR select_dir;
	//ブロックが吸える状態なら選択ボタンを押せる
	//そして吸ったかどうかを返す
	bool suckColor();
	bool outColor();
	Vec2i player_pos();

	//ゲッター
	Object getObject();
	Vec2i getSelect();
	CONDITION getCondition();

	//セッター
	//ポスのセットは地面判定でやってあげてね
	void addPos(Vec2f pos);
	void addColor();
	void subColor();
private:
	Texture player_texture;
	int ColorMax;
	int animation_count;
	float cut_x;
    Object player;
	Vec2i selection;
	Vec2i p_pos;
	Vec2f speed;
	float g;
	int color_abs;
	int change_count;
	bool jump_flag;
	CONDITION condition;
	DIRECTION direction;

	
};
