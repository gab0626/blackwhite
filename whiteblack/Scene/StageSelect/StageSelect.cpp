#include "StageSelect.h"

StageSelect::StageSelect()
    : stage_No_(1)
    , stage_Max_No_(0)
    , font_(YuFont("src/whiteblack/Top/yumayoLib/meiryo.ttc"))
{
    setup();
    Setup_map_Data_();
    Setup_map_Comment_();
}
void StageSelect::update()
{
    sYuFrame::Get()++;
    if (is_Pushed_)
        ;
    else
    Update_map_Select_();
    fade_In_();
}
void StageSelect::draw()
{
    Draw_map_Button_();
    Draw_miniMap_();

    yuFillBox(Vec2f::Zero(), Vec2f(WIDTH, HEIGHT),
              true,
              col_);
}
void StageSelect::setup()
{
    col_ = (Color(0.0f, 0.0f, 0.0f, 1.0f));
    is_Fade_ = (true);
    is_Pushed_ = (false);
}
SCENE StageSelect::shift()
{
    if (env.isPushKey(GLFW_KEY_ENTER))
    {
        is_Pushed_ = true;
    }
    if (is_Pushed_)
    {
        return fade_Out_();
    }
    return SCENE::GAME;
}

void StageSelect::Setup_map_Comment_()
{
    std::vector<std::string> _temp =
    {
        { "一番最初だから簡単だよ" },
        { "ちょっと頭を捻るコースです" },
        { "息抜きコース" }
    };

    for (size_t i = 0; i < stage_Max_No_; ++i)
    {
        if (i < _temp.size())
            map_Coment_.push_back(_temp[i]);
        else
            map_Coment_.push_back(std::string("ステージ情報がありません"));
    }

}
void StageSelect::Setup_map_Data_()
{
    stage_No_ = 1;
    for (std::string _file_name = "res/map/stage" + std::to_string(stage_No_) + ".txt"; isValidPath(_file_name); _file_name = "res/map/stage" + std::to_string(++stage_No_) + ".txt")
    {
        std::ifstream* _ifstream_ptr = new std::ifstream(_file_name);

        Vec2i _map_Size;
        *_ifstream_ptr >> _map_Size.y();
        *_ifstream_ptr >> _map_Size.x();

        std::vector<std::vector<int>> _buf_2D_Map_Chip_Data;
        for (size_t y = 0; y < _map_Size.y(); ++y)
        {
            std::vector<int> _chip_1D = std::vector<int>(_map_Size.x());
            for (size_t x = 0; x < _map_Size.x(); ++x)
            {
                *_ifstream_ptr >> _chip_1D[x];
            }
            _buf_2D_Map_Chip_Data.push_back(_chip_1D);
        }
        delete _ifstream_ptr;

        std::vector<std::vector<int>> _chip_2D;
        for (size_t y = _map_Size.y() - 1; y != -1; --y)
        {
            std::vector<int> _chip_1D;
            for (size_t x = 0; x < _map_Size.x(); ++x)
            {
                _chip_1D.push_back(_buf_2D_Map_Chip_Data[y][x]);
            }
            _chip_2D.push_back(_chip_1D);
        }
        map_Chip_Data_.push_back(_chip_2D);
    }

    stage_Max_No_ = stage_No_ - 1;
    stage_No_ = 0;

    draw_Map_Size_ = Vec2i(500, 300);

    draw_Select_Box_Size_ = Vec2i(100, 100);

    block_Window_Size_ = Vec2f(draw_Map_Size_.x() / map_Chip_Data_[0][0].size(), draw_Map_Size_.y() / map_Chip_Data_[0].size());
}
void StageSelect::Draw_miniMap_()
{
    glPushMatrix();
    {
        glTranslated(-draw_Map_Size_.x() - 64.0, 0.0, 0.0);

        for (size_t y = 0; y < map_Chip_Data_[stage_No_].size(); ++y)
        {
            for (size_t x = 0; x < map_Chip_Data_[stage_No_][y].size(); ++x)
            {
                float _col = 1.0f * map_Chip_Data_[stage_No_][y][x] / 17.0f;
                yuFillBox(Vec2f(x * block_Window_Size_.x(), y * block_Window_Size_.y()),
                          block_Window_Size_,
                          false,
                          Color(_col, _col, _col, 1.0f));
            }
        }
        drawBox(0, 0, draw_Map_Size_.x(), draw_Map_Size_.y(),
                2,
                Color::white);

        font_.textAlign(YuFont::RIGHT);
        font_.text("STAGE", Vec2f(draw_Map_Size_.x() - 16.0f - std::to_string(stage_No_ + 1).size() * 64.0f, 16.0f));
        font_.text(stage_No_ + 1, Vec2f(draw_Map_Size_.x() - 16.0f, 16.0f));

        font_.textAlign(YuFont::CENTER);
        font_.text(map_Coment_[stage_No_], Vec2f(draw_Map_Size_.x() / 2.0f, -64.0f));

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
                yuFillBox(Vec2f::Zero(), Vec2f(draw_Select_Box_Size_.x(), draw_Select_Box_Size_.y()),
                          false,
                          color256(40, 88, 207));
                font_.textColor(Color::white);
                font_.text(z + 1, Vec2f(draw_Select_Box_Size_.x() / 2.0f, (draw_Select_Box_Size_.y() - 64.0f) / 2.0f));
            }
            else
            {
                yuFillBox(Vec2f::Zero(), Vec2f(draw_Select_Box_Size_.x(), draw_Select_Box_Size_.y()),
                          false,
                          Color::white);
                font_.textColor(color256(40, 88, 207));
                font_.text(z + 1, Vec2f(draw_Select_Box_Size_.x() / 2.0f, (draw_Select_Box_Size_.y() - 64.0f) / 2.0f));
            }
            drawBox(0, 0, draw_Select_Box_Size_.x(), draw_Select_Box_Size_.y(),
                    2,
                    Color::black);
            glTranslated(draw_Select_Box_Size_.x(), 0.0, 0.0);
        }
    }
    glPopMatrix();
    font_.textColor(Color::white);
}
void StageSelect::Update_map_Select_()
{
    if (env.isPushKey('A') || env.isPushKey(GLFW_KEY_LEFT))
        stage_No_--;

    if (env.isPushKey('D') || env.isPushKey(GLFW_KEY_RIGHT))
        stage_No_++;

    Vec2f _mouse_Pos = env.mousePosition();
    if(_mouse_Pos != Vec2f::Zero())
    for (size_t z = 0; z < map_Chip_Data_.size(); ++z)
    {
        if (0 <= _mouse_Pos.x() && _mouse_Pos.x() <= draw_Select_Box_Size_.x() &&
            0 <= _mouse_Pos.y() && _mouse_Pos.y() <= draw_Select_Box_Size_.y())
        {
            stage_No_ = z;
        }
        _mouse_Pos.x() += -draw_Select_Box_Size_.x();
    }


    if (stage_No_ < 0)
    {
        stage_No_ = 0;
    }
    if (stage_Max_No_ - 1 <= stage_No_)
    {
        stage_No_ = stage_Max_No_ - 1;
    }
}
void StageSelect::fade_In_()
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
            break;
        case YuCounter::UPDATE:
            //col_.a() += 1.0f / 30;
            break;
        case YuCounter::END:
            setup();
            return SCENE::TITLE;
            break;
        }
    }
    return SCENE::STAGESELECT;
}