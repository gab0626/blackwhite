#pragma once

#include "../../../lib/framework.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <memory>
#include <vector>
#include <list>
#include <chrono>
#include <thread>

#define _PRI_HYT_BEGIN	namespace pri_hyt {
#define _PRI_HYT_END	}

_PRI_HYT_BEGIN

class YuTick_System
{
public:
    YuTick_System();
    void synchronize_Aside();
    void synchronize_Bside();
    int is_Tick();
    int is_Open();

private:
    int tick_Counter_;
    int prev_tick_Counter_;
    int is_Open_;
    std::thread thread_;
};

class YuFrame
{
public:
    int operator()()
    {
        return Get();
    }
    void operator++(int)
    {
        countUP();
    }
    int Get();
    void countUP();
};

_PRI_HYT_END

class sYuAppEnv
{
public:
    static void Set(AppEnv* env);
};

class YuCounter
{
public:
    YuCounter();

    enum
    {
        INIT,
        UPDATE,
        END,
        NONE = 'y'
    };

    //	���� : �t���[����
    //	���̊֐��́A�����ɓ�͎g���Ȃ��̂ŁA
    //	�ǂ����Ă��g�������ꍇ�͔z��Ȃǂɂ��Ďg���܂��傤�B
    int Get(const int count);
    int Get_Frame();
    void clear();

private:
    int tick_;
    int frame_Count_;
};

class sYuFrame
{
public:
    static pri_hyt::YuFrame& Get()
    {
        static pri_hyt::YuFrame frame;
        return frame;
    }
};

template <typename _Ty>
void yuPrint(const _Ty str)
{
    std::cout << str;
}

template <typename _Ty>
void yuPrintln(const _Ty str)
{
    std::cout << str << std::endl;
}

//  �h��ׂ���`
//  �n�_
//  ���A����
//  �F
void yuFillBox(const Vec2f& start,
               const Vec2f& size,
               const Color& color);

//  �h��ׂ���`
//  �n�_
//  ���A����
//  �^�񒆂ɂ���
//  �F
void yuFillBox(const Vec2f& start,
               const Vec2f& size,
               const bool mode,
               const Color& color);

//  �h��ׂ���`(��]�A�g��k��)
//  �n�_
//  ���A����
//  ��]�p�x(���W�A��)
//  �g�嗦
//  �^�񒆂ɂ���
//  �F
void yuFillBox(const Vec2f& start,
               const Vec2f& size,
               const float angle_Rad,
               const Vec2f& scale,
               const bool mode,
               const Color& color);

//  �`�F�b�N�|�C���g�𐶐�
//  �n�_
//  ���A���� = (Vec2f(16.0f, 16.0f))
//  �F = (white)
void yuCheckPosition(const Vec2f& start,
                     const Vec2f& size = Vec2f(16.0f, 16.0f),
                     const Color& color = Color::white);

//  �摜����`�̕`��
//  �n�_
//  �摜
//  �^�񒆂ɂ��� = (true)
//  �F = (white)
void yuTextureBox(const Vec2f& start,
                  const Texture& texture,
                  const bool mode = false,
                  const Color& color = Color::white);
//  �摜����`�̕`��(��]�A�g��k��)
//  �n�_
//  �摜
//  �^�񒆂ɂ��� = (true)
//  �F = (white)
void yuTextureBox(const Vec2f& start,
                  const Texture& texture,
                  const float angle_Rad,
                  const Vec2f& scale,
                  const bool mode = false,
                  const Color& color = Color::white);
//  �摜����`�̕`��
//  �n�_
//  ���A����
//  �摜
//  �A�j���[�V�����ԍ�
//  �^�񒆂ɂ��� = (true)
//  �F = (white)
void yuTextureBox(const Vec2f& start,
                  const Vec2f& cut_Size,
                  const Texture& texture,
                  const int animation_Index,
                  const bool mode = false,
                  const Color& color = Color::white);
//  �摜����`�̕`��(��]�A�g��k��)
//  �n�_
//  ���A����
//  �摜
//  �A�j���[�V�����ԍ�
//  ��]�p�x(���W�A��)
//  �g�嗦
//  �^�񒆂ɂ��� = (true)
//  �F = (white)
void yuTextureBox(const Vec2f& start,
                  const Vec2f& cut_Size,
                  const Texture& texture,
                  const int animation_Index,
                  const float angle_Rad,
                  const Vec2f& scale,
                  const bool mode = false,
                  const Color& color = Color::white);

//  �ȉ��}�N�X�t���̉摜�`��

//  �摜����`�̕`��
//  �n�_
//  �摜
//  �摜(�}�X�N)
//  �^�񒆂ɂ��� = (true)
//  �F = (white)
void yuTextureBox(const Vec2f& start,
                  const Texture& texture,
                  const Texture& mask_Texture,
                  const bool mode = false,
                  const Color& color = Color::white);
//  �摜����`�̕`��(��]�A�g��k��)
//  �n�_
//  �摜
//  �摜(�}�X�N)
//  �^�񒆂ɂ��� = (true)
//  �F = (white)
void yuTextureBox(const Vec2f& start,
                  const Texture& texture,
                  const Texture& mask_Texture,
                  const float angle_Rad,
                  const Vec2f& scale,
                  const bool mode = false,
                  const Color& color = Color::white);
//  �摜����`�̕`��
//  �n�_
//  ���A����
//  �摜
//  �摜(�}�X�N)
//  �A�j���[�V�����ԍ�
//  �^�񒆂ɂ��� = (true)
//  �F = (white)
void yuTextureBox(const Vec2f& start,
                  const Vec2f& cut_Size,
                  const Texture& texture,
                  const Texture& mask_Texture,
                  const int animation_Index,
                  const bool mode = false,
                  const Color& color = Color::white);

//  �摜����`�̕`��(��]�A�g��k��)
//  �n�_
//  ���A����
//  �摜
//  �摜(�}�X�N)
//  �A�j���[�V�����ԍ�
//  ��]�p�x(���W�A��)
//  �g�嗦
//  �^�񒆂ɂ��� = (true)
//  �F = (white)
void yuTextureBox(const Vec2f& start,
                  const Vec2f& cut_Size,
                  const Texture& texture,
                  const Texture& mask_Texture,
                  const int animation_Index,
                  const float angle_Rad,
                  const Vec2f& scale,
                  const bool mode = false,
                  const Color& color = Color::white);

//  �摜�ɌŒ肵�Ȃ��A�}�X�N�摜�������܂�
void yuTextureBox(void yuTextureBox(),
                  void mask_YuTextureBox());

//	���Ԃ̌v��

//	yuPushTime() �� yuPopTime() �ŋ��񂾂Ƃ���̎��Ԃ��v���ł��܂��B
void yuPushTime();

//	yuPopTime() �ł͂��̎��Ԃ�Ԃ��܂��B
//	�t���[�����[�g�ŕԂ�(true)
int yuPopTime(const bool mode = false);


// �����R�[�h��ϊ����邽�߂�C++�W�����C�u����
#include <codecvt>
class YuFont
{
public:
    enum
    {
        LEFT,
        CENTER,
        RIGHT
    };
    YuFont(const std::string& path = "src/yumayoLib/meiryo.ttc");
    void textFont(const std::string& path);
    void textFont(const std::string& path, const int size);
    void textSize(const int size);
    void textColor(const Color& color);
    void textAlign(const int mode);
    void text(const std::string& str, const Vec2f& position = Vec2f::Zero());
    void text(const std::string& str, const Vec2f& position, const Color& color);
    void text(const int str, const Vec2f& position = Vec2f::Zero());
    void text(const int str, const Vec2f& position, const Color& color);
    //	�X�R�A��0�l�߂ŕ\��
    //	���ۂ̃X�R�A
    //	����
    void drawScore(const int str, const int no, const Vec2f& position = Vec2f::Zero());


private:
    int     size_;
    int     mode_;
    Color   color_;
    Font    font_;
};

class sYuFont
{
public:
    static YuFont& Get()
    {
        static YuFont _font;
        return _font;
    }
};

class YuNovelFont
{
public:
    enum
    {
        LEFT,
        CENTER,
        RIGHT
    };
    YuNovelFont(const std::string& path = "src/yumayoLib/meiryo.ttc");
    //	���R�搶�̎���������̂܂܈�̊֐��ɂ��܂����B
    void text(const std::string& str, const Vec2f& position = Vec2f::Zero());
private:
    int     size_;
    int     mode_;
    Color   color_;
    Font    font_;

    //  �ȉ����R�搶�̊֐����g�����߂ɕK�v�Ȃ��̂ł��B
    // �\�����镶�����𑝂₷�Ԋu
    YuCounter counter_;
    int framelate_;
    // �\��������
    size_t disp_length_;
    // utf8������̕��������J�E���g
    size_t strlen_(const std::string& s)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
        return conv.from_bytes(s).size();
    }
    // utf8�����񂩂畔������������o��
    // s   ������
    // pos ���o���ʒu
    // len ���o��������
    std::string substr_(const std::string& s,
                        const size_t pos = 0, const size_t len = std::string::npos)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;

        auto u32string = conv.from_bytes(s);            // UTF8 -> UTF32
        auto sub = u32string.substr(pos, len);          // �����擾

        return conv.to_bytes(sub);                      // UTF32 -> UTF8�ɂ��ĕԂ�
    }
};

//�@CSV�t�@�C���̓��o�͎͂�ɂ��̃T�C�g���Q�l�ɂ��܂����B
//	http://futurismo.biz/archives/1782
class YuCsvIO
{
public:
    YuCsvIO() {}
    //	���� : �t�@�C���p�X, �������~����(default : ����)
    YuCsvIO(const std::string& file_Name, const bool mode = true);
    void operator = (const std::string& file_Name)
    {
        reset_For(file_Name);
    }
    std::vector<std::vector<int>> read()
    {
        return map_;
    }
    std::vector<int> read_Line(int line_Number)
    {
        return map_[line_Number];
    }
    std::vector<std::vector<std::string>> read_String()
    {
        return map_string_;
    }
    std::vector<std::string> read_String_Line(int line_Number)
    {
        return map_string_[line_Number];
    }
    void reWrite(const Vec2i& array_Number, const int data)
    {
        if (0 <= array_Number.x() && 0 <= array_Number.y() &&
            array_Number.x() < (int)map_[array_Number.y()].size() && array_Number.y() < (int)map_.size())
        {
            map_[array_Number.y()][array_Number.x()] = data;
        }
    }
    void reWrite(const std::vector<std::vector<int>>& map_Data)
    {
        map_ = map_Data;
    }
    void save_For();
    void save_For(const std::string& file_Name);
    void save_Forr();
    void save_Forr(const std::string& file_Name);
    void reset_For(const std::string& file_Name);
    void reset_Forr(const std::string& file_Name);
    void reset_String_For(const std::string & file_Name);

private:
    std::vector<std::vector<int>> map_;
    std::vector<std::vector<std::string>> map_string_;
    std::string save_File_Name_;
};

class YuCsv_Editor
{
public:
    YuCsv_Editor(const std::string& edit_File_Name_, const std::string& read_Map_File_Name);
    std::vector<std::vector<int>> read()
    {
        return map_Data_.read();
    }
    void edit(const Vec2f& origin, const Vec2f& camera_Position, int chip_Size);
    void Set_Save_File_Name(const std::string& save_File_Name) { save_File_Name_ = save_File_Name; }

private:
    float scale_;                           //  �`�b�v�̊g�嗦��ۑ����܂�
    int is_Animation_;
    int edit_Mode_;
    int grid_Draw_;
    int texture_Animation_Number_;
    int set_Chip_Number_;
    Vec2f right_Box_Size_;
    Vec2f top_Box_Size_;
    std::string default_Save_File_Name_;
    std::string save_File_Name_;
    Texture edge_Base_;
    Texture edge_;
    Vec2f scroll_Bar_Position_;             //  �ȉ��X�N���[���o�[�̃X�e�[�^�X�l�ł�
    float scroll_Bar_Buf_Position_Y_;
    Vec2f scroll_Bar_Size_;

    YuCsvIO edit_;
    YuCsvIO map_Data_;
    YuCounter counter_;
    std::vector<Texture> chip_Texture_;

    class YuAnimation_Texture_
    {
    public:
        YuAnimation_Texture_(Vec2f position, Texture* texture)
            :
            position_(position),
            angle_(0.0f),
            texture_(texture),
            check_(false),
            is_Mouse_Over_(false)
        {}
        void update()
        {
            mouse_Over_();
        }
        void draw(const YuCsv_Editor& csv_Editor)
        {
            yuTextureBox(position_,
                         csv_Editor.edge_Base_,
                         true);
            yuTextureBox(position_,
                         *texture_,
                         angle_,
                         Vec2f(1.0f, 1.0f),
                         true);

            if (check_ == true)
            {
                yuTextureBox(position_,
                             csv_Editor.edge_,
                             angle_,
                             Vec2f(1.0f, 1.0f),
                             true);
            }
            else
            {
                drawBox(position_.x(), position_.y(),
                        64.0f, 64.0f,
                        2,
                        Color::gray,
                        angle_,
                        Vec2f(1.0f, 1.0f),
                        Vec2f(64.0f / 2.0f, 64.0f / 2.0f));
            }
        }
        bool Get_Clicked() { return check_; }
        bool Get_Mouse_Over() { return is_Mouse_Over_; }
        void check_Out() { check_ = false; }
        void Set_Position(const Vec2f& position) { position_ = position; }
        void Set_Scroll_Position_Y(const float position) { position_.y() = position; }
    private:
        void mouse_Over_();
        Vec2f position_;
        float angle_;
        Texture* texture_;
        bool check_;
        bool is_Mouse_Over_;
        YuCounter counter_;
    };
    std::vector<YuAnimation_Texture_> edit_Texture_;

    //  ���܂�ɂ�edit�֐����撣�肷���Ă����̂ŕ��U�����܂���
    void edit_Open_();
    void edit_Close_();
    void edit_Chip_Texture_Draw_(const Vec2f& origin, const Vec2f& camera_Position, const int chip_Size, const std::vector<std::vector<int>>& map_Data);
    void edit_Chip_Texture_Update_(const Vec2f& origin, const Vec2f& camera_Position, const int chip_Size, const std::vector<std::vector<int>>& map_Data);
    void edit_Grid_Draw_(const Vec2f& origin, const Vec2f& camera_Position, const int chip_Size);
    void edit_Texture_Animation_Draw_(const Vec2f& camera_Position);
    void edit_Save_();
};

class sYuTick_System
{
public:
    static pri_hyt::YuTick_System& Get()
    {
        static pri_hyt::YuTick_System tick;
        return tick;
    }
};

#define YU_TICK sYuTick_System::Get().is_Tick()

class sYuCsvIO
{
public:
    static YuCsvIO& get()
    {
        static YuCsvIO csvIO("");
        return csvIO;
    }
};

class sYuRandom
{
public:
    static Random& Get()
    {
        static Random _random;
        return _random;
    }
};

class sYuTexture
{
public:
    static Texture* Get(const int texture_Number)
    {
        static YuCsvIO _edit;
        static std::vector<Texture> _texture;
        static bool _init = true;
        if (_init == true)
        {
            _edit.reset_String_For("res/data/texture.csv");
            for (int n = 0; n < (int)_edit.read_String().size(); ++n)
            {
                _texture.push_back(Texture("res/texture/" + _edit.read_String()[n][1] + ".png"));
            }
            _init = false;
        }
        return &_texture[texture_Number];
    }
};

class YuScene_Base
{
public:
    YuScene_Base()
    {
        /*nothing*/
    }
    virtual ~YuScene_Base()
    {
        /*nothing*/
    }
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual int shift() = 0;
};

class YuClass_Base
{
public:
    YuClass_Base()
    {
        /*nothing*/
    }
    virtual ~YuClass_Base()
    {
        /*nothing*/
    }
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void reset()
    {
        /*nothing*/
    }
};

class YuDyc_Obj_Base
{
    Vec2f position_;
    Vec2f speed_;
    Vec2f size_;

public:
    YuDyc_Obj_Base()
        :
        position_(Vec2f::Zero()),
        speed_(Vec2f::Zero()),
        size_(Vec2f::Zero())
    {
        /*nothing*/
    }
    YuDyc_Obj_Base(const Vec2f& position, const Vec2f& speed, const Vec2f& size)
        :
        position_(position),
        speed_(speed),
        size_(size)
    {
        /*nothing*/
    }
    ~YuDyc_Obj_Base()
    {
        /*nothing*/
    }

    void Set(const Vec2f& position, const Vec2f& speed, const Vec2f& size)
    {
        position_ = position;
        speed_ = speed;
        size_ = size;
    }
};

class YuStc_Obj_Base
{
    Vec2f position_;
    Vec2f size_;

public:
    YuStc_Obj_Base()
        :
        position_(Vec2f::Zero()),
        size_(Vec2f::Zero())
    {
        /*nothing*/
    }
    YuStc_Obj_Base(const Vec2f& position, const Vec2f& size)
        :
        position_(position),
        size_(size)
    {
        /*nothing*/
    }
    ~YuStc_Obj_Base()
    {
        /*nothing*/
    }

    void Set(const Vec2f& position, const Vec2f& size)
    {
        position_ = position;
        size_ = size;
    }
};

class YuMessage_Window
{
public:
    YuMessage_Window(Vec2f position, Vec2f size)
        :
        title_Bar_(YuStc_Obj_Base(position, size)),
        main_Window_(YuStc_Obj_Base(position, size))
    { }
private:
    YuStc_Obj_Base title_Bar_;
    YuStc_Obj_Base main_Window_;

    YuCounter counter_;
};