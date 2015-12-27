#include "StageSelect.h"

// イージングの関数群
//   t 媒介変数(0.0~1.0)
//   b 開始値
//   e 終了値

extern float EasingLinear(float t, float b, float e);


extern float EasingBackIn(float t, float b, float e);

extern float EasingBackOut(float t, float b, float e);

extern float EasingBackInOut(float t, float b, float e);


extern float EasingBounceOut(float t, float b, float e);

extern float EasingBounceIn(float t, float b, float e);

extern float EasingBounceInOut(float t, float b, float e);


extern float EasingCircIn(float t, float b, float e);

extern float EasingCircOut(float t, float b, float e);

extern float EasingCircInOut(float t, float b, float e);


extern float EasingCubicIn(float t, float b, float e);

extern float EasingCubicOut(float t, float b, float e);

extern float EasingCubicInOut(float t, float b, float e);


extern float EasingElasticIn(float t, float b, float e);

extern float EasingElasticOut(float t, float b, float e);

extern float EasingElasticInOut(float t, float b, float e);


extern float EasingExpoIn(float t, float b, float e);

extern float EasingExpoOut(float t, float b, float e);

extern float EasingExpoInOut(float t, float b, float e);


extern float EasingQuadIn(float t, float b, float e);

extern float EasingQuadOut(float t, float b, float e);

extern float EasingQuadInOut(float t, float b, float e);


extern float EasingQuartIn(float t, float b, float e);

extern float EasingQuartOut(float t, float b, float e);

extern float EasingQuartInOut(float t, float b, float e);


extern float EasingQuintIn(float t, float b, float e);

extern float EasingQuintOut(float t, float b, float e);

extern float EasingQuintInOut(float t, float b, float e);


extern float EasingSineIn(float t, float b, float e);

extern float EasingSineOut(float t, float b, float e);

extern float EasingSineInOut(float t, float b, float e);

namespace hyt
{
    extern Media g_Title_AND_StageSelect_Bgm;
}

StageSelect::StageSelect()
    : stage_No_(1)
    , stage_Max_No_(0)
    , font_(YuFont("src/whiteblack/Top/yumayoLib/meiryo.ttc"))
{
    setup();
    Setup_map_Data_();
    Setup_map_Comment_();
    menu_ = std::vector<Sub_Menu>(2);
    menu_[0].setup(Vec2f(WIDTH / 2 - 150.0f, -HEIGHT / 2 + 60.0f * (2.0f * 1.1f) + 150.0f));
    menu_[1].setup(Vec2f(WIDTH / 2 - 150.0f, -HEIGHT / 2 + 60.0f + 150.0f));
}
void StageSelect::update()
{
    sYuFrame::Get()++;
    frame_++;
    if (is_Pushed_)
        ;
    else
    {
        if (is_Menu_)
            ;
        else
            Update_map_Select_();
    }
    if (is_Exit_)
    {
        game_Exit_();
    }
    fade_In_();
}
void StageSelect::draw()
{
    Draw_map_Button_();
    Draw_miniMap_();
    Draw_Side_Menu_();

    //fadeに使います。
    yuFillBox(Vec2f::Zero(), Vec2f(WIDTH, HEIGHT),
              true,
              col_);
}
void StageSelect::setup()
{
    col_ = (Color(0.0f, 0.0f, 0.0f, 1.0f));
    is_Fade_ = (true);
    is_Pushed_ = (false);
    alpha_ = (1.0f);
    is_Bgm_Setup_ = (false);
    frame_ = (0);
    select_Frame_ = (0);
    select_SE_ = (Media("res/sound/selectSE.wav"));
    press_Select_Frame_ = (0);
    is_Menu_ = (false);
    is_Exit_ = (false);
}
SCENE StageSelect::shift()
{
    if (is_Fade_)
        ;
    else
    {
        if (stage_No_ < stage_Max_No_)
        {
            if (env.isPushKey(GLFW_KEY_ENTER))
            {
                is_Pushed_ = true;
            }
        }
    }
    if (is_Pushed_)
    {
        return fade_Out_();
    }
    return SCENE::STAGESELECT;
}

void StageSelect::Setup_map_Comment_()
{
    std::vector<std::vector<std::string>> _temp =
    {
        {
            { "一番最初だから簡単だよ" },
            { "改行らくらく" }
        },
        {
            { "ちょっと頭を捻るコースです" }
        },
        {
            { "息抜きコース" },
            { "改行改行" },
            { "改行改行" },
            { "改行いえーい" }
        }
    };

    for (int i = 0; i < stage_Max_No_; ++i)
    {
        if (i < (int)_temp.size())
            map_Coment_.push_back(_temp[i]);
        else
        {
            std::vector<std::string> __temp = { { "ステージコメントがありません" } };
            map_Coment_.push_back(__temp);
        }
    }

}
void StageSelect::Setup_map_Data_()
{
    draw_Map_Size_ = Vec2i(500, 300);

    draw_Select_Box_Size_ = Vec2i(100, 100);

    stage_No_ = 1;
    for (
        std::string _file_name = "res/map/stage" + std::to_string(stage_No_) + ".txt";
        isValidPath(_file_name);
        _file_name = "res/map/stage" + std::to_string(++stage_No_) + ".txt"
        )
    {
        std::ifstream* _ifstream_ptr = new std::ifstream(_file_name);

        Vec2i _map_Size;
        *_ifstream_ptr >> _map_Size.y();
        *_ifstream_ptr >> _map_Size.x();

        std::vector<std::vector<int>> _buf_2D_Map_Chip_Data;
        for (int y = 0; y < _map_Size.y(); ++y)
        {
            std::vector<int> _chip_1D = std::vector<int>(_map_Size.x());
            for (int x = 0; x < _map_Size.x(); ++x)
            {
                *_ifstream_ptr >> _chip_1D[x];
            }
            _buf_2D_Map_Chip_Data.push_back(_chip_1D);
        }
        delete _ifstream_ptr;

        std::vector<std::vector<int>> _chip_2D;
        for (int y = _map_Size.y() - 1; y != -1; --y)
        {
            std::vector<int> _chip_1D;
            for (int x = 0; x < _map_Size.x(); ++x)
            {
                _chip_1D.push_back(_buf_2D_Map_Chip_Data[y][x]);
            }
            _chip_2D.push_back(_chip_1D);
        }
        map_Chip_Data_.push_back(_chip_2D);

        block_Window_Size_.push_back(Vec2f(draw_Map_Size_.x() / _map_Size.x(), draw_Map_Size_.y() / _map_Size.y()));
    }

    stage_Max_No_ = stage_No_ - 1;
    stage_No_ = 0;
}
void StageSelect::Draw_miniMap_()
{
    glPushMatrix();
    {
        glTranslated(-draw_Map_Size_.x() - 64.0, 0.0, 0.0);

        if (stage_No_ < stage_Max_No_)
        {
            for (size_t y = 0; y < map_Chip_Data_[stage_No_].size(); ++y)
            {
                for (size_t x = 0; x < map_Chip_Data_[stage_No_][y].size(); ++x)
                {
                    float _col = 1.0f * map_Chip_Data_[stage_No_][y][x] / 17.0f;
                    yuFillBox(Vec2f(x * block_Window_Size_[stage_No_].x(), y * block_Window_Size_[stage_No_].y()),
                              block_Window_Size_[stage_No_],
                              false,
                              Color(_col, _col, _col, 1.0f));
                }
            }
            drawBox(0, 0, draw_Map_Size_.x(), draw_Map_Size_.y(),
                    2,
                    Color::white);
            font_.textSize(64);
            font_.textAlign(YuFont::RIGHT);
            font_.text("STAGE", Vec2f(draw_Map_Size_.x() - 16.0f - std::to_string(stage_No_ + 1).size() * 64.0f, 16.0f));
            font_.text(stage_No_ + 1, Vec2f(draw_Map_Size_.x() - 16.0f, 16.0f));

            font_.textSize(32);
            for (size_t i = 0; i < map_Coment_[stage_No_].size(); ++i)
            {
                font_.text(map_Coment_[stage_No_][i], Vec2f(draw_Map_Size_.x(), -32.0f * (i + 1)));
            }
        }
        else
        {
            drawBox(0, 0, draw_Map_Size_.x(), draw_Map_Size_.y(),
                    2,
                    Color::white);

            font_.textAlign(YuFont::RIGHT);
            if (stage_No_ == stage_Max_No_ + 0)
            {
                font_.textSize(64);
                font_.text("操作説明", Vec2f(draw_Map_Size_.x() - 16.0f, 16.0f));
                font_.textSize(32);
                font_.text("ゲームの操作方法を", Vec2f(draw_Map_Size_.x(), -32.0f * (1)));
                font_.text("説明します", Vec2f(draw_Map_Size_.x(), -32.0f * (2)));
            }
            if (stage_No_ == stage_Max_No_ + 1)
            {
                font_.textSize(64);
                font_.text("ゲーム終了", Vec2f(draw_Map_Size_.x() - 16.0f, 16.0f));
                font_.textSize(32);
                font_.text("またねー", Vec2f(draw_Map_Size_.x(), -32.0f * (1)));
            }
        }
    }
    glPopMatrix();
}
void StageSelect::Draw_map_Button_()
{
    font_.textAlign(YuFont::CENTER);
    glPushMatrix();
    {
        for (size_t z = 0; z < map_Chip_Data_.size(); ++z)
        {
            if (z == stage_No_)
            {
                ;
            }
            else
            {
                yuFillBox(Vec2f::Zero(), Vec2f(draw_Select_Box_Size_.x(), draw_Select_Box_Size_.y()),
                          true,
                          Color::white);
                font_.textColor(color256(40, 88, 207));
                font_.text(z + 1, Vec2f(0.0f, -draw_Select_Box_Size_.y() / 4.0f));

                drawBox(0, 0, draw_Select_Box_Size_.x(), draw_Select_Box_Size_.y(),
                        2,
                        Color::black,
                        0.0f,
                        Vec2f(1.0f, 1.0f),
                        Vec2f(draw_Select_Box_Size_.x() / 2.0f, draw_Select_Box_Size_.y() / 2.0f));
            }
            glTranslated(draw_Select_Box_Size_.x(), 0.0, 0.0);
            if (z % 5 == 5 - 1)
            {
                glPopMatrix();
                glPushMatrix();
                int _scale = ((z + 1) / 5);
                glTranslated(0.0, -draw_Select_Box_Size_.y() * _scale, 0.0);
            }
        }
    }
    glPopMatrix();
    glPushMatrix();
    {
        for (size_t z = 0; z < map_Chip_Data_.size(); ++z)
        {
            if (z == stage_No_)
            {
                Vec2f _size = Vec2f(draw_Select_Box_Size_.x(), draw_Select_Box_Size_.y());
                if (select_Frame_ < 20)
                {
                    select_Frame_++;
                }
                _size.x() = EasingExpoOut(select_Frame_ / 20.0f, draw_Select_Box_Size_.x() + 100, draw_Select_Box_Size_.x());
                _size.y() = EasingExpoOut(select_Frame_ / 20.0f, draw_Select_Box_Size_.y() + 100, draw_Select_Box_Size_.y());
                yuFillBox(Vec2f::Zero(), _size,
                          true,
                          color256(40, 88, 207));
                font_.textColor(Color::white);
                font_.text(z + 1, Vec2f(0.0f, -draw_Select_Box_Size_.y() / 4.0f));

                drawBox(0, 0, _size.x(), _size.y(),
                        2,
                        Color::black,
                        0.0f,
                        Vec2f(1.0f, 1.0f),
                        Vec2f(_size.x() / 2.0f, _size.y() / 2.0f));
            }
            else
            {
                ;
            }
            glTranslated(draw_Select_Box_Size_.x(), 0.0, 0.0);
            if (z % 5 == 5 - 1)
            {
                glPopMatrix();
                glPushMatrix();
                int _scale = ((z + 1) / 5);
                glTranslated(0.0, -draw_Select_Box_Size_.y() * _scale, 0.0);
            }
        }
    }
    glPopMatrix();
    font_.textColor(Color::white);
}
void StageSelect::Draw_Side_Menu_()
{
    int _i = 0;
    for (auto& obj : menu_)
    {
        int _buf_Stage_No = stage_No_;
        if (obj.hit())
        {
            stage_No_ = _i + stage_Max_No_;
            if (_buf_Stage_No != stage_No_)
            {
                select_Frame_ = 0;
                select_SE_.play();
            }
        }
        _i++;
    }
    if (stage_No_ == stage_Max_No_ + 0)
    {
        menu_[0].hit_ = true;
    }
    if (stage_No_ == stage_Max_No_ + 1)
    {
        menu_[1].hit_ = true;
    }
    for (auto& obj : menu_)
    {
        obj.draw();
    }
    menu_[0].drawFont("操作説明");
    if (stage_No_ == stage_Max_No_ + 0)
    {
        if (env.isPushKey(GLFW_KEY_ENTER))
        {
            is_Menu_ = !is_Menu_;
        }
    }
    menu_[1].drawFont("ゲーム終了");
    if (stage_No_ == stage_Max_No_ + 1)
    {
        if (env.isPushKey(GLFW_KEY_ENTER))
        {
            is_Exit_ = true;
        }
    }

    if (is_Menu_)
    {
        yuFillBox(Vec2f::Zero(), Vec2f(WIDTH, HEIGHT),
                  true,
                  Color(0.0f, 0.0f, 0.0f, 0.9f));
        font_.textSize(64);
        font_.textAlign(YuFont::CENTER);
        font_.text("ここに、操作説明が貼られます。");
        font_.textSize(32);
        font_.text("Enterで戻る←", Vec2f(WIDTH / 2 - 150.0f, -HEIGHT / 2.0f + 100.0f));
        font_.textSize(64);
    }
    else
    {
        font_.textAlign(YuFont::CENTER);
        font_.textSize(32);
        font_.text("Z←→Cで選択", Vec2f(WIDTH / 2 - 150.0f, -HEIGHT / 2.0f + 100.0f));
        font_.text("Enterでスタート", Vec2f(WIDTH / 2 - 150.0f, -HEIGHT / 2.0f + 100.0f - 32.0f));
        font_.textSize(64);
    }

    for (auto& obj : menu_)
    {
        obj.size_ = Vec2f(300.0f, 60.0f);
    }
    if (stage_No_ < stage_Max_No_)
        ;
    else
    {
        if (select_Frame_ < 20)
        {
            select_Frame_++;
        }
        menu_[stage_No_ - stage_Max_No_].size_.x() = EasingExpoOut(select_Frame_ / 20.0f, 300.0f + 100.0f, 300.0f);
        menu_[stage_No_ - stage_Max_No_].size_.y() = EasingExpoOut(select_Frame_ / 20.0f, 60.0f + 20.0f, 60.0f);
    }
}
void StageSelect::Update_map_Select_()
{
    if (env.isPushKey('A') || env.isPushKey('Z') || env.isPushKey(GLFW_KEY_LEFT))
    {
        stage_No_--;
        select_Frame_ = 0;
        select_SE_.play();
    }
    if (env.isPressKey('A') || env.isPressKey('Z') || env.isPressKey(GLFW_KEY_LEFT))
    {
        press_Select_Frame_++;
        if (20 < press_Select_Frame_)
        {
            if (sYuFrame::Get()() % 4 == 0)
            {
                stage_No_--;
                select_Frame_ = 0;
                select_SE_.play();
            }
        }
    }
    if (env.isPushKey('W') || env.isPushKey(GLFW_KEY_UP))
    {
        stage_No_ -= 5;
        select_Frame_ = 0;
        select_SE_.play();
    }
    if (env.isPressKey('W') || env.isPressKey(GLFW_KEY_UP))
    {
        press_Select_Frame_++;
        if (20 < press_Select_Frame_)
        {
            if (sYuFrame::Get()() % 4 == 0)
            {
                stage_No_ -= 5;
                select_Frame_ = 0;
                select_SE_.play();
            }
        }
    }

    if (env.isPushKey('D') || env.isPushKey('C') || env.isPushKey(GLFW_KEY_RIGHT))
    {
        stage_No_++;
        select_Frame_ = 0;
        select_SE_.play();
    }
    if (env.isPressKey('D') || env.isPressKey('C') || env.isPressKey(GLFW_KEY_RIGHT))
    {
        press_Select_Frame_++;
        if (20 < press_Select_Frame_)
        {
            if (sYuFrame::Get()() % 4 == 0)
            {
                stage_No_++;
                select_Frame_ = 0;
                select_SE_.play();
            }
        }
    }
    if (env.isPushKey('S') || env.isPushKey(GLFW_KEY_DOWN))
    {
        stage_No_ += 5;
        select_Frame_ = 0;
        select_SE_.play();
    }
    if (env.isPressKey('S') || env.isPressKey(GLFW_KEY_DOWN))
    {
        press_Select_Frame_++;
        if (20 < press_Select_Frame_)
        {
            if (sYuFrame::Get()() % 4 == 0)
            {
                stage_No_ += 5;
                select_Frame_ = 0;
                select_SE_.play();
            }
        }
    }

    if (env.isPullKey('A') || env.isPullKey('Z') || env.isPullKey(GLFW_KEY_LEFT) || env.isPullKey('W') || env.isPullKey(GLFW_KEY_UP) ||
        env.isPullKey('D') || env.isPullKey('C') || env.isPullKey(GLFW_KEY_RIGHT) || env.isPullKey('S') || env.isPullKey(GLFW_KEY_DOWN))
    {
        press_Select_Frame_ = 0;
    }

    Vec2f _mouse_Pos = env.mousePosition() + Vec2f(draw_Select_Box_Size_.x() / 2.0f, draw_Select_Box_Size_.y() / 2.0f);
    if (_mouse_Pos != Vec2f(draw_Select_Box_Size_.x() / 2.0f, draw_Select_Box_Size_.y() / 2.0f))
    {
        for (size_t z = 0; z < map_Chip_Data_.size(); ++z)
        {
            if (0 <= _mouse_Pos.x() && _mouse_Pos.x() <= draw_Select_Box_Size_.x() &&
                0 <= _mouse_Pos.y() && _mouse_Pos.y() <= draw_Select_Box_Size_.y())
            {
                int _buf_Stage_No = stage_No_;
                stage_No_ = z;
                if (_buf_Stage_No != stage_No_)
                {
                    select_Frame_ = 0;
                    select_SE_.play();
                }
            }
            _mouse_Pos.x() += -draw_Select_Box_Size_.x();
            if (z % 5 == 5 - 1)
            {
                _mouse_Pos = env.mousePosition() + Vec2f(draw_Select_Box_Size_.x() / 2.0f, draw_Select_Box_Size_.y() / 2.0f);
                int _scale = ((z + 1) / 5);
                _mouse_Pos.y() += draw_Select_Box_Size_.y() * _scale;
            }
        }
    }

    if (stage_No_ < 0)
    {
        stage_No_ = 0;
    }
    if (stage_Max_No_ - 1 + (int)menu_.size() <= stage_No_)
    {
        stage_No_ = stage_Max_No_ - 1 + menu_.size();
    }
}
void StageSelect::fade_In_()
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
                is_Bgm_Setup_ = true;
                hyt::g_Title_AND_StageSelect_Bgm.play();
                hyt::g_Title_AND_StageSelect_Bgm.looping(true);
                hyt::g_Title_AND_StageSelect_Bgm.gain(0.0f);
            }
            break;
        case YuCounter::UPDATE:
            alpha_ -= 1.0f / 30;
            col_.a() -= 1.0f / 30;
            if (is_Bgm_Setup_)
                hyt::g_Title_AND_StageSelect_Bgm.gain(1.0f - alpha_);
            break;
        case YuCounter::END:
            col_ = Color(0.0f, 0.0f, 0.0f, 0.0f);
            hyt::g_Title_AND_StageSelect_Bgm.gain(1.0f);
            is_Fade_ = false;
            break;
        }
    }
}
SCENE StageSelect::fade_Out_()
{
    if (is_Fade_)
        ;
    else
    {
        switch (counter_.Get(30))
        {
        case YuCounter::INIT:
            col_ = Color(0.0f, 0.0f, 0.0f, 0.0f);
            hyt::g_Title_AND_StageSelect_Bgm.gain(1.0f);
            break;
        case YuCounter::UPDATE:
            alpha_ += 1.0f / 30;
            col_.a() += 1.0f / 30;
            hyt::g_Title_AND_StageSelect_Bgm.gain(1.0f - alpha_);
            break;
        case YuCounter::END:
            hyt::g_Title_AND_StageSelect_Bgm.gain(0.0f);
            if (hyt::g_Title_AND_StageSelect_Bgm.isPlaying())
            {
                hyt::g_Title_AND_StageSelect_Bgm.stop();
            }
            setup();
            return SCENE::GAME;
            break;
        }
    }
    return SCENE::STAGESELECT;
}
void StageSelect::game_Exit_()
{
    if (is_Fade_)
        ;
    else
    {
        switch (counter_.Get(60))
        {
        case YuCounter::INIT:
            col_ = Color(0.0f, 0.0f, 0.0f, 0.0f);
            hyt::g_Title_AND_StageSelect_Bgm.gain(1.0f);
            break;
        case YuCounter::UPDATE:
            alpha_ += 1.0f / 30;
            col_.a() += 1.0f / 30;
            hyt::g_Title_AND_StageSelect_Bgm.gain(1.0f - alpha_);
            break;
        case YuCounter::END:
            if (hyt::g_Title_AND_StageSelect_Bgm.isPlaying())
            {
                hyt::g_Title_AND_StageSelect_Bgm.stop();
            }
            exit(0);
            break;
        }
    }
}