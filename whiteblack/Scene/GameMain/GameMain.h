#include "../../Top/Top.h"

#include "../../Map/Map.h"
#include "../../Player/Player.h"

class GameMain
{
public:
    void update();
    void draw();
    void setup(int);
    SCENE shift();
    GameMain();
private:
    Map map;
    Player player;
    
    Media BGM;
    Media gameover;
    Media clear;
    Texture bg;
    int count;
    
    bool isGoal();

   
    bool isFieldOut();

};

