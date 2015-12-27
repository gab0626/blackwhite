#include "Title.h"

// イージングの関数群
//   t 媒介変数(0.0~1.0)
//   b 開始値
//   e 終了値

float EasingLinear(float t, float b, float e) {
    return (e - b) * t + b;
}


float EasingBackIn(float t, float b, float e) {
    float s = 1.70158;
    return (e - b) * t * t * ((s + 1) * t - s) + b;
}

float EasingBackOut(float t, float b, float e) {
    float s = 1.70158;
    t -= 1.0;
    return (e - b) * (t * t * ((s + 1) * t + s) + 1) + b;
}

float EasingBackInOut(float t, float b, float e) {
    float s = 1.70158 * 1.525;
    if ((t /= 0.5) < 1) return (e - b) / 2 * (t * t * ((s + 1) * t - s)) + b;
    t -= 2;
    return (e - b) / 2 * (t * t * ((s + 1) * t + s) + 2) + b;
}


float EasingBounceOut(float t, float b, float e) {
    if (t < (1 / 2.75)) {
        return (e - b) * (7.5625 * t * t) + b;
    }
    else if (t < (2 / 2.75)) {
        t -= (1.5 / 2.75);
        return (e - b) * (7.5625 * t * t + 0.75) + b;
    }
    else if (t < (2.5 / 2.75)) {
        t -= (2.25 / 2.75);
        return (e - b) * (7.5625 * t * t + 0.9375) + b;
    }
    else {
        t -= (2.625 / 2.75);
        return (e - b) * (7.5625 * t * t + 0.984375) + b;
    }
}

float EasingBounceIn(float t, float b, float e) {
    return (e - b) - EasingBounceOut(1.0 - t, 0, e - b) + b;
}

float EasingBounceInOut(float t, float b, float e) {
    if (t < 0.5) return EasingBounceIn(t * 2, 0, e - b) * 0.5 + b;
    else         return EasingBounceOut(t * 2 - 1.0, 0, e - b) * 0.5 + (e - b) * 0.5 + b;
}


float EasingCircIn(float t, float b, float e) {
    return -(e - b) * (std::sqrt(1 - t * t) - 1) + b;
}

float EasingCircOut(float t, float b, float e) {
    t -= 1.0;
    return (e - b) * std::sqrt(1 - t * t) + b;
}

float EasingCircInOut(float t, float b, float e) {
    if ((t /= 0.5) < 1) return -(e - b) / 2 * (std::sqrt(1 - t * t) - 1) + b;
    t -= 2;
    return (e - b) / 2 * (std::sqrt(1 - t * t) + 1) + b;
}


float EasingCubicIn(float t, float b, float e) {
    return (e - b) * t * t * t + b;
}

float EasingCubicOut(float t, float b, float e) {
    t -= 1.0;
    return (e - b) * (t * t * t + 1) + b;
}

float EasingCubicInOut(float t, float b, float e) {
    if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t + b;
    t -= 2;
    return (e - b) / 2 * (t * t * t + 2) + b;
}


float EasingElasticIn(float t, float b, float e) {
    if (t == 0) return b;
    if (t == 1) return e;

    float p = 0.3;
    float a = e - b;
    float s = p / 4;
    t -= 1;
    return -(a * std::pow(2, 10 * t) * std::sin((t - s) * (2 * M_PI) / p)) + b;
}

float EasingElasticOut(float t, float b, float e) {
    if (t == 0) return b;
    if (t == 1) return e;

    float p = 0.3;
    float a = e - b;
    float s = p / 4;
    return (a * std::pow(2, -10 * t) * std::sin((t - s) * (2 * M_PI) / p) + a + b);
}

float EasingElasticInOut(float t, float b, float e) {
    if (t == 0) return b;
    if ((t /= 0.5) == 2) return e;

    float p = 0.3 * 1.5;
    float a = e - b;
    float s = p / 4;
    if (t < 1) {
        t -= 1;
        return -0.5 * (a * std::pow(2, 10 * t) * std::sin((t - s) * (2 * M_PI) / p)) + b;
    }
    t -= 1;
    return a * std::pow(2, -10 * t) * std::sin((t - s) * (2 * M_PI) / p) * 0.5 + a + b;
}


float EasingExpoIn(float t, float b, float e) {
    return (t == 0) ? b : (e - b) * std::pow(2, 10 * (t - 1)) + b;
}

float EasingExpoOut(float t, float b, float e) {
    return (t == 1) ? e : (e - b) * (-std::pow(2, -10 * t) + 1) + b;
}

float EasingExpoInOut(float t, float b, float e) {
    if (t == 0) return b;
    if (t == 1) return e;
    if ((t /= 0.5) < 1) return (e - b) / 2 * std::pow(2, 10 * (t - 1)) + b;
    return (e - b) / 2 * (-std::pow(2, -10 * --t) + 2) + b;
}


float EasingQuadIn(float t, float b, float e) {
    return (e - b) * t * t + b;
}

float EasingQuadOut(float t, float b, float e) {
    return -(e - b) * t * (t - 2) + b;
}

float EasingQuadInOut(float t, float b, float e) {
    if ((t /= 0.5) < 1) return (e - b) / 2 * t * t + b;
    --t;
    return -(e - b) / 2 * (t * (t - 2) - 1) + b;
}


float EasingQuartIn(float t, float b, float e) {
    return (e - b) * t * t * t * t + b;
}

float EasingQuartOut(float t, float b, float e) {
    t -= 1.0;
    return -(e - b) * (t * t * t * t - 1) + b;
}

float EasingQuartInOut(float t, float b, float e) {
    if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t * t + b;
    t -= 2;
    return -(e - b) / 2 * (t * t * t * t - 2) + b;
}


float EasingQuintIn(float t, float b, float e) {
    return (e - b) * t * t * t * t * t + b;
}

float EasingQuintOut(float t, float b, float e) {
    t -= 1.0;
    return (e - b) * (t * t * t * t * t + 1) + b;
}

float EasingQuintInOut(float t, float b, float e) {
    if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t * t * t + b;
    t -= 2;
    return (e - b) / 2 * (t * t * t * t * t + 2) + b;
}


float EasingSineIn(float t, float b, float e) {
    return -(e - b) * std::cos(t * (M_PI / 2)) + (e - b) + b;
}

float EasingSineOut(float t, float b, float e) {
    return (e - b) * std::sin(t * (M_PI / 2)) + b;
}

float EasingSineInOut(float t, float b, float e) {
    return -(e - b) / 2 * (std::cos(M_PI * t) - 1) + b;
}

namespace hyt
{
    Media g_Title_AND_StageSelect_Bgm;
}

Title::Title()
    : font_(YuFont("src/whiteblack/Top/yumayoLib/meiryo.ttc"))
{
    hyt::g_Title_AND_StageSelect_Bgm = (Media("res/sound/title.wav"));
    setup();
}
void Title::update()
{
    sYuFrame::Get()++;
    frame_++;
    fade_In_();
}
void Title::draw()
{
    yuTextureBox(Vec2f::Zero(),
                 tex_,
                 true);

    font_.textSize(300);
    font_.textColor(Color::white);
    yuFillBox(Vec2f(title_Pos_.x() + 0.0f, title_Pos_.y() + 150.0f - 30.0f),
              Vec2f(1000, 300.0f),
              true,
              Color(0.0f, 0.0f, 0.0f, 0.5f));
    font_.textAlign(YuFont::CENTER);
    font_.text("TITLE", Vec2f(title_Pos_.x(), title_Pos_.y()));

    font_.textSize(200);
    if (is_Pushed_)
        font_Col_.a() = (sin(sYuFrame::Get()() / 2.0f) + 1.0f) / 2.0f;
    else
        font_Col_.a() = (sin(sYuFrame::Get()() / 20.0f) + 1.0f) / 2.0f;
    font_.textColor(font_Col_);
    yuFillBox(Vec2f(start_Button_Pos_.x() + 0.0f, start_Button_Pos_.y() - -100.0f - 30.0f),
              Vec2f(800, 200.0f),
              true,
              Color(0.0f, 0.0f, 0.0f, 0.5f));
    font_.text("START", start_Button_Pos_);

    if (45 <= frame_)
    {
        font_.textSize(32);
        float _time = float(frame_ - 45.0f) / 60.0f;
        Vec2f _pos = Vec2f(WIDTH / 2 - 150.0f, EasingExpoOut(_time, -HEIGHT / 2.0f - 300.0f, -HEIGHT / 2.0f + 100.0f));
        font_.textColor(Color::white);
        font_.text("Enterでスタート", _pos);
    }

    //fadeに使います。
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
    alpha_ = (1.0f);
    title_Pos_ = (Vec2f(0.0f, HEIGHT / 2 + 30.0f));
    start_Button_Pos_ = (Vec2f(WIDTH, -200.0f));
    frame_ = 0;
    font_Col_ = (Color(1.0f, 1.0f, 1.0f, 1.0f));
}
SCENE Title::shift()
{
    if (is_Fade_)
        ;
    else
    {
        if (env.isPushKey(GLFW_KEY_ENTER))
        {
            is_Pushed_ = true;
        }
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
            env.bgColor(Color::black);
            col_ = Color(0.0f, 0.0f, 0.0f, 1.0f);
            if (hyt::g_Title_AND_StageSelect_Bgm.isPlaying())
                ;
            else
            {
                hyt::g_Title_AND_StageSelect_Bgm.play();
                hyt::g_Title_AND_StageSelect_Bgm.looping(true);
                hyt::g_Title_AND_StageSelect_Bgm.gain(0.0f);
            }
            break;
        case YuCounter::UPDATE:
            alpha_ -= 1.0f / 30;
            col_.a() -= 1.0f / 30;
            hyt::g_Title_AND_StageSelect_Bgm.gain(1.0f - alpha_);
            break;
        case YuCounter::END:
            col_ = Color(0.0f, 0.0f, 0.0f, 0.0f);
            hyt::g_Title_AND_StageSelect_Bgm.gain(1.0f);
            is_Fade_ = false;
            break;
        }
    }
    if (15 <= frame_ && frame_ <= 15 + 120)
    {
        float _time = float(frame_ - 15.0f) / 120.0f;
        title_Pos_.y() = EasingBounceOut(_time, HEIGHT / 2 + 30.0f, 0.0f);
    }
    if (30 <= frame_ && frame_ <= 30 + 60)
    {
        float _time = float(frame_ - 30.0f) / 60.0f;
        start_Button_Pos_.x() = EasingQuartOut(_time, WIDTH, 0.0f);
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
            alpha_ += 1.0f / 30;
            col_.a() += 1.0f / 30;
            break;
        case YuCounter::END:
            setup();
            return SCENE::STAGESELECT;
            break;
        }
    }
    return SCENE::TITLE;
}

