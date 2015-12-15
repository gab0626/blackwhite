
#include "../whiteblack/Top/Top.h"
#include "Scene/SceneManager/SceneManager.h"
int main() {
	env;
    SceneManager scenemanager;
  while (env.isOpen()) {
    env.begin();

    scenemanager.update();
    scenemanager.draw();
    scenemanager.Shift();   

    env.end();
  }
}


