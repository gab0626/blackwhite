#include "SceneManager.h"

SceneManager::SceneManager(){
    scene_number = SCENE::TITLE;
   
}

void SceneManager::update(){

    
    switch (scene_number)
    {
    default:
        break;
    case SCENE::TITLE:
        title.update();
        break;
    case SCENE::STAGESELECT:
        stageselect.update();
        break;
    case SCENE::GAME:
        GameMain.update();
        break;
    }
}
void SceneManager::draw(){
    switch (scene_number)
    {
    default:
        break;
    case SCENE::TITLE:
        title.draw();
        break;
    case SCENE::STAGESELECT:
        stageselect.draw();
        break;
    case SCENE::GAME:
        GameMain.draw();
        break;
    }

}
void SceneManager::Shift(){
    
    switch (scene_number)
    {
    default:
        break;
    case SCENE::TITLE:
        scene_number = title.shift();
        break;
    case SCENE::STAGESELECT:
        scene_number = stageselect.shift();

        if (scene_number != SCENE::STAGESELECT)
        {
            GameMain.setup(stageselect.Get_Stage_Number()+1);
        }
        break;
    case SCENE::GAME:
        scene_number = GameMain.shift();

        break;
    }
            
}