
#include "../../Top/Top.h"

class Title
{
    //****************************************//
    //  public:
    //****************************************//
public:
    Title();
public:
    void update();
    void draw();
    void setup();
    SCENE shift();

    //****************************************//
    //  private:
    //****************************************//
private:    //  setup()で何回も呼ばれます。
    Texture tex_;
    Color col_;
    bool is_Fade_;
    bool is_Pushed_;
private:    //  setup()にもコンストラクタにも書かれません。
    YuCounter counter_;

private:
    void fade_In_();
    SCENE fade_Out_();
};
