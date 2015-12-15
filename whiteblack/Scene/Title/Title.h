
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
private:    //  setup()�ŉ�����Ă΂�܂��B
    Texture tex_;
    Color col_;
    bool is_Fade_;
    bool is_Pushed_;
private:    //  setup()�ɂ��R���X�g���N�^�ɂ�������܂���B
    YuCounter counter_;

private:
    void fade_In_();
    SCENE fade_Out_();
};
