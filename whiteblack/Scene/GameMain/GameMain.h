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
    

};

