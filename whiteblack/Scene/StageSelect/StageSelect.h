
#pragma once

#include "../../Top/Top.h"
#include <cmath>
#include <functional>

class Sub_Menu
{
public:
    Sub_Menu()
        : font_(YuFont("src/whiteblack/Top/yumayoLib/meiryo.ttc"))
    { }
    void setup(const Vec2f& pos)
    {
        size_ = Vec2f(300.0f, 60.0f);
        pos_ = pos;
        frame_ = 0;
        hit_ = false;
        font_.textSize(40);
        font_.textAlign(YuFont::CENTER);
    }
    bool hit(Vec2f drawPos = Vec2f::Zero())
    {
        Vec2f _mouse_Pos = env.mousePosition() + size_ / 2.0f;
        if (pos_.x() + drawPos.x() <= _mouse_Pos.x() && _mouse_Pos.x() <= pos_.x() + drawPos.x() + size_.x() &&
            pos_.y() + drawPos.y() <= _mouse_Pos.y() && _mouse_Pos.y() <= pos_.y() + drawPos.y() + size_.y())
        {
            hit_ = true;
            return true;
        }
        hit_ = false;
        return false;
    }
    void draw()
    {
        if (hit_)
        {
            yuFillBox(pos_, size_,
                      true,
                      color256(160, 216, 50));
            drawBox(pos_.x(), pos_.y(),
                    size_.x(), size_.y(),
                    2,
                    Color::white,
                    0.0f,
                    Vec2f(1.0f, 1.0f),
                    Vec2f(size_.x() / 2.0f, size_.y() / 2.0f));
        }
        else
            yuFillBox(pos_, size_,
                      true,
                      color256(160, 216, 50, 192));
    }
    void drawFont(const std::string& str)
    {
        font_.text(str, Vec2f(pos_.x(), pos_.y() - 60.0f / 2.0f + 5.0f));
    }
public:
    Vec2f pos_;
    Vec2f size_;
    int frame_;
    bool hit_;
    YuFont font_;
};

class StageSelect
{
    //****************************************//
    //  public:
    //****************************************//
public:
    StageSelect();
public:
    void update();
    void draw();
    void setup();
    SCENE shift();
    //  ステージ番号は0からスタートになっています。
    int Get_Stage_Number()
    {
        return stage_No_;
    }

    //****************************************//
    //  private:
    //****************************************//
private:    //  コンストラクタにしか書きません。
    int stage_No_;
    int stage_Max_No_;
    YuFont font_;
    std::vector<Sub_Menu> menu_;
private:    //  setup()で何回も呼ばれます。
    Color col_;
    bool is_Fade_;
    bool is_Pushed_;
    float alpha_;
    bool is_Bgm_Setup_;
    int frame_;
    int select_Frame_;
    Media select_SE_;
    int press_Select_Frame_;
    bool is_Menu_;
    bool is_Exit_;
private:    //  setup()にもコンストラクタにも書かれません。
    std::vector<std::vector<std::vector<int>>> map_Chip_Data_;
    std::vector<std::vector<std::string>> map_Coment_;
    YuCounter counter_;
private:
    void Setup_map_Comment_();
    void Setup_map_Data_();
private:
    Vec2i draw_Map_Size_;
    Vec2i draw_Select_Box_Size_;
    std::vector<Vec2f> block_Window_Size_;
private:
    void Draw_miniMap_();
    void Draw_map_Button_();
    void Draw_Side_Menu_();
private:
    void Update_map_Select_();
private:
    void fade_In_();
    SCENE fade_Out_();
    void game_Exit_();
};

