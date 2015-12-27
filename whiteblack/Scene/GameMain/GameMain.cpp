#include "GameMain.h"




GameMain::GameMain(){
    //setup();
    BGM = Media("res/sound/stage1.wav");
    gameover = Media("res/sound/gameover.wav");
    clear = Media("res/sound/clear.wav");
    bg = Texture("res/Texture/bg/orora.png");


}
void GameMain::update(){
    if (count == 0){
    if (!BGM.isPlaying())BGM.play();
        player.update();
        map.update();
        player.addPos(map.isHitPlayerToBlock(player.getObject(), player.getCondition()));
        //std::cout << (int)player.getCondition() << std::endl;
        //•úo
        if (player.outColor()){
            if (map.sucked(player.getSelect())){
                player.subColor();
            }
        }
        //‹zŽû
        if (player.suckColor()){
            if (map.released(player.getSelect())){
                player.addColor();
            }
        }

    }
}
void GameMain::draw(){
    env.bgColor(Color::blue);
    drawTextureBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, bg);

    //Vec2f cpos = Vec2f(-player.getObject().pos.x(), -player.getObject().pos.y());
    // cpos.x() = std::max(player.getObject().pos.x(), map.pos().x() + WIDTH / 2);
    // cpos.y() = std::max(player.getObject().pos.y(), map.pos().y() + HEIGHT / 2);
    //std::cout << "pos" << map.pos() << std::endl;

    // std::cout << "size" <<map.size() << std::endl;

    glPushMatrix();
    glTranslated(-player.getObject().pos.x(), -player.getObject().pos.y(), 0);

#ifdef DEBUG
    drawFillBox(map.pos().x(), map.pos().y(), map.size().x(), map.size().y(), Color::cyan);
#endif;
    map.draw();
    map.selected(player.getSelect());
    glPopMatrix();

    player.draw();
}

void GameMain::setup(int stage_num){
    map.setup(stage_num);


    player.setup(map.getPlayerStartPos());
    //player.setPos(map.getPlayerStartPos());

    count = 0;
}

SCENE GameMain::shift(){

    if (isGoal()){
        BGM.stop();
        if (!clear.isPlaying())clear.play();
        if (count++ > 60 * 7)
            return SCENE::STAGESELECT;
    }


    if (isFieldOut()){
        BGM.stop();
        if (!gameover.isPlaying())gameover.play();
        if (count++ > 60 * 7)
            return SCENE::STAGESELECT;
    }
    return SCENE::GAME;
}

bool GameMain::isGoal()
{
    if (player.getObject().pos.x() + player.getObject().size.x() >= map.getGoalPos().x() &&
        player.getObject().pos.x() <= map.getGoalPos().x() + map.getGoalSize().x())
    {
        if (player.getObject().pos.y() + player.getObject().size.y() >= map.getGoalPos().y() &&
            player.getObject().pos.y() <= map.getGoalPos().y() + map.getGoalSize().y())
        {
            return true;
        }
    }
    return false;
}

bool is_hitg(Vec2f pos, Vec2f floor_pos, Vec2f floor_size){
    return (
        pos.x() >= floor_pos.x() &&
        pos.x() <= floor_pos.x() + floor_size.x() &&
        pos.y() >= floor_pos.y() &&
        pos.y() <= floor_pos.y() + floor_size.y());

}
bool GameMain::isFieldOut(){
    return !is_hitg
        (player.getObject().
        pos, map.pos() - player.getObject().size,
        map.size() + player.getObject().size);
}