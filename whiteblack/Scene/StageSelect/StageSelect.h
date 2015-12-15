
#include "../../Top/Top.h"

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

    //  �X�e�[�W�ԍ���0����X�^�[�g�ɂȂ��Ă��܂��B
    int Get_Stage_Number()
    {
        return stage_No_;
    }

    //****************************************//
    //  private:
    //****************************************//
private:    //  �R���X�g���N�^�ɂ��������܂���B
    int stage_No_;
    int stage_Max_No_;
    YuFont font_;
private:    //  setup()�ŉ�����Ă΂�܂��B
    Color col_;
    bool is_Fade_;
    bool is_Pushed_;
private:    //  setup()�ɂ��R���X�g���N�^�ɂ�������܂���B
    std::vector<std::vector<std::vector<int>>> map_Chip_Data_;
    std::vector<std::string> map_Coment_;
    YuCounter counter_;
private:
    void Setup_map_Comment_();
    void Setup_map_Data_();
private:
    Vec2i draw_Map_Size_;
    Vec2i draw_Select_Box_Size_;
    Vec2f block_Window_Size_;
private:
    void Draw_miniMap_();
    void Draw_map_Button_();
private:
    void Update_map_Select_();
private:
    void fade_In_();
    SCENE fade_Out_();
};
