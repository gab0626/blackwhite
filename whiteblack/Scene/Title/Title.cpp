#include "Title.h"

Title::Title()
{
    setup();
}
void Title::update()
{
    sYuFrame::Get()++;
    fade_In_();
}
void Title::draw()
{
    yuTextureBox(Vec2f::Zero(),
                 tex_,
                 true);

    yuFillBox(Vec2f::Zero(), Vec2f(WIDTH, HEIGHT),
              true,
              col_);
}
void Title::setup()
{
    tex_ = (Texture("res/Texture/chara.png"));
    col_ = (Color(0.0f, 0.0f, 0.0f, 1.0f));
    is_Fade_ = (true);
    is_Pushed_ = (false);
}
SCENE Title::shift()
{
    if (env.isPushKey(GLFW_KEY_ENTER))
    {
        is_Pushed_ = true;
    }
    if (is_Pushed_)
    {
        return fade_Out_();
    }
    return SCENE::TITLE;
}

void Title::fade_In_()
{
    if (is_Fade_)
    {
        switch (counter_.Get(30))
        {
        case YuCounter::INIT:
            col_ = Color(0.0f, 0.0f, 0.0f, 1.0f);
            break;
        case YuCounter::UPDATE:
            //col_.a() -= 1.0f / 30;
            break;
        case YuCounter::END:
            col_ = Color(0.0f, 0.0f, 0.0f, 0.0f);
            is_Fade_ = false;
            break;
        }
    }
}
SCENE Title::fade_Out_()
{
    if (is_Fade_)
        ;
    else
    {
        switch (counter_.Get(30))
        {
        case YuCounter::INIT:
            col_ = Color(0.0f, 0.0f, 0.0f, 0.0f);
            break;
        case YuCounter::UPDATE:
            //col_.a() += 1.0f / 30;
            break;
        case YuCounter::END:
            setup();
            return SCENE::STAGESELECT;
            break;
        }
    }
    return SCENE::TITLE;
}

