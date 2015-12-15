#include "yumayoLib.hpp"
#include "yumayoGlobal.hpp"

_PRI_HYT_BEGIN

YuTick_System::YuTick_System() :
    is_Open_(TRUE)
{}
void YuTick_System::synchronize_Aside()
{
    thread_ = std::thread([&]()
    {
        for (;;)
        {
            if (!pri_hyt::g_Env_ptr->isOpen())
            {
                is_Open_ = FALSE;
                break;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(50000));
            ++tick_Counter_;
        }
    });
}
void YuTick_System::synchronize_Bside()
{
    prev_tick_Counter_ = tick_Counter_;
}
int YuTick_System::is_Tick()
{
    if (prev_tick_Counter_ != tick_Counter_)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int YuTick_System::is_Open()
{
    if (!is_Open_)
    {
        thread_.join();
    }
    return is_Open_;
}

int YuFrame::Get()
{
    return g_Frame;
}
void YuFrame::countUP()
{
    g_Frame++;

    if (g_Frame >= 0x77359400)
    {
        if (g_Frame % 600)
        {
            yuPrintln("frame over 2000000000 [" + std::to_string(g_Frame) + "] : YuFrame::countUP");
        }
    }
    if (g_Frame == 0x7FFFFFFF)
    {
        g_Frame = 0;
    }
}

_PRI_HYT_END

void sYuAppEnv::Set(AppEnv* env)
{
    pri_hyt::g_Env_ptr = env;
}

void yuFillBox(const Vec2f& start,
               const Vec2f& size,
               const Color& color) {

    const float end_x = start.x() + size.x();
    const float end_y = start.y() + size.y();

    GLfloat vtx[] = {
        start.x(), start.y(),
        end_x, start.y(),
        start.x(), end_y,
        end_x, end_y
    };

    glVertexPointer(2, GL_FLOAT, 0, vtx);

    // 色を設定
    color.setToGl();

    glEnableClientState(GL_VERTEX_ARRAY);

    // OpenGLに線分の描画を指示
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void yuFillBox(const Vec2f& start,
               const Vec2f& size,
               const bool mode,
               const Color& color) {

    const Vec2f start_ = mode ? Vec2f(start.x() - size.x() / 2.0f, start.y() - size.y() / 2.0f) : start;

    const float end_x = start_.x() + size.x();
    const float end_y = start_.y() + size.y();

    GLfloat vtx[] = {
        start_.x(), start_.y(),
        end_x, start_.y(),
        start_.x(), end_y,
        end_x, end_y
    };

    glVertexPointer(2, GL_FLOAT, 0, vtx);

    // 色を設定
    color.setToGl();

    glEnableClientState(GL_VERTEX_ARRAY);

    // OpenGLに線分の描画を指示
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void yuFillBox(const Vec2f& start,
               const Vec2f& size,
               const float angle_Rad,
               const Vec2f& scale,
               const bool mode,
               const Color& color) {

    // 回転、拡大縮小の行列を生成
    auto matrix = transformMatrix2D(angle_Rad,
                                    Vec3f(start.x(), start.y(), 0.0f),
                                    Vec3f(scale.x(), scale.y(), 1.0f));

    // 行列をOpenGLに設定
    glPushMatrix();
    glMultMatrixf(matrix.data());

    // 描画
    yuFillBox(Vec2f::Zero(),
              size,
              mode,
              color);

    // 行列を元に戻す
    glPopMatrix();
}

void yuCheckPosition(const Vec2f & start,
                     const Vec2f & size,
                     const Color & color)
{
    yuFillBox(start, size, true, color);
    if (sYuFrame::Get().Get() % 60 == 0)
    {
        yuPrintln(" x : [" + std::to_string(start.x()) + "] y : [" + std::to_string(start.y()) + "]");
    }
}

void yuTextureBox(const Vec2f& start,
                  const Texture& texture,
                  const bool mode,
                  const Color& color) {

    const Vec2f cut_Start = Vec2f::Zero();
    const Vec2f size = Vec2f(texture.width(), texture.height());

    const Vec2f start_ = mode ? Vec2f(start.x() - size.x() / 2.0f, start.y() - size.y() / 2.0f) : start;

    const float end_x = start_.x() + size.x();
    const float end_y = start_.y() + size.y();

    GLfloat vtx[] = {
        start_.x(), start_.y(),
        end_x, start_.y(),
        start_.x(), end_y,
        end_x, end_y
    };

    glVertexPointer(2, GL_FLOAT, 0, vtx);

    GLfloat uv[] = {
        cut_Start.x() / size.x(), (cut_Start.y() + size.y()) / size.y(),
        (cut_Start.x() + size.x()) / size.x(), (cut_Start.y() + size.y()) / size.y(),
        cut_Start.x() / size.x(), cut_Start.y() / size.y(),
        (cut_Start.x() + size.x()) / size.x(), cut_Start.y() / size.y(),
    };

    glTexCoordPointer(2, GL_FLOAT, 0, uv);

    // 色を設定
    color.setToGl();

    glEnable(GL_TEXTURE_2D);
    texture.bind();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // OpenGLに線分の描画を指示
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_TEXTURE_2D);
    texture.unbind();
}

void yuTextureBox(const Vec2f & start,
                  const Texture & texture,
                  const float angle_Rad,
                  const Vec2f& scale,
                  const bool mode,
                  const Color & color)
{
    // 回転、拡大縮小の行列を生成
    auto matrix = transformMatrix2D(angle_Rad,
                                    Vec3f(start.x(), start.y(), 0.0f),
                                    Vec3f(scale.x(), scale.y(), 1.0f));

    // 行列をOpenGLに設定
    glPushMatrix();
    glMultMatrixf(matrix.data());

    // 描画
    yuTextureBox(Vec2f::Zero(),
                 texture,
                 mode,
                 color);

    // 行列を元に戻す
    glPopMatrix();

}

void yuTextureBox(const Vec2f& start,
                  const Vec2f& cut_Size,
                  const Texture& texture,
                  const int animation_Index,
                  const bool mode,
                  const Color& color) {

    const Vec2f start_ = mode ? Vec2f(start.x() - cut_Size.x() / 2.0f, start.y() - cut_Size.y() / 2.0f) : start;

    const float end_x = start_.x() + cut_Size.x();
    const float end_y = start_.y() + cut_Size.y();

    const int n_Cut_x = texture.width() / cut_Size.x();
    const int n_Cut_y = texture.height() / cut_Size.y();

    const float x_Offset = (animation_Index % n_Cut_x) * cut_Size.x();
    const float y_Offset = (animation_Index / n_Cut_y) * cut_Size.y();

    GLfloat vtx[] = {
        start_.x(), start_.y(),
        end_x, start_.y(),
        start_.x(), end_y,
        end_x, end_y
    };

    glVertexPointer(2, GL_FLOAT, 0, vtx);

    GLfloat uv[] = {
        x_Offset / texture.width(), (y_Offset + cut_Size.y()) / texture.height(),
        (x_Offset + cut_Size.x()) / texture.width(), (y_Offset + cut_Size.y()) / texture.height(),
        x_Offset / texture.width(), y_Offset / texture.height(),
        (x_Offset + cut_Size.x()) / texture.width(), y_Offset / texture.height(),
    };

    glTexCoordPointer(2, GL_FLOAT, 0, uv);

    // 色を設定
    color.setToGl();

    glEnable(GL_TEXTURE_2D);
    texture.bind();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // OpenGLに線分の描画を指示
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_TEXTURE_2D);
    texture.unbind();
}

void yuTextureBox(const Vec2f & start,
                  const Vec2f & cut_Size,
                  const Texture & texture,
                  const int animation_Index,
                  const float angle_Rad,
                  const Vec2f& scale,
                  const bool mode,
                  const Color & color)
{
    // 回転、拡大縮小の行列を生成
    auto matrix = transformMatrix2D(angle_Rad,
                                    Vec3f(start.x(), start.y(), 0.0f),
                                    Vec3f(scale.x(), scale.y(), 1.0f));

    // 行列をOpenGLに設定
    glPushMatrix();
    glMultMatrixf(matrix.data());

    // 描画
    yuTextureBox(Vec2f::Zero(),
                 cut_Size,
                 texture,
                 animation_Index,
                 mode,
                 color);

    // 行列を元に戻す
    glPopMatrix();
}

#define MASK_FUNK(Origin, mask)                         \
    glEnable(GL_STENCIL_TEST);                          \
        glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);   \
         glColorMask(false, false, false, false);       \
            glStencilFunc(GL_ALWAYS, 0, 1);             \
            Origin;                                     \
            glEnable(GL_ALPHA_TEST);                    \
                glAlphaFunc(GL_GREATER, 0.0f);          \
                glStencilFunc(GL_ALWAYS, 1, 1);         \
                mask;                                   \
            glDisable(GL_ALPHA_TEST);                   \
        glColorMask(true, true, true, true);            \
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);         \
        glStencilFunc(GL_EQUAL, 0, 1);                  \
        Origin;                                         \
    glDisable(GL_STENCIL_TEST);                         \

void yuTextureBox(const Vec2f & start,
                  const Texture & texture,
                  const Texture & mask_Texture,
                  const bool mode,
                  const Color & color)
{
    //  ステンシル処理を有効にします。
    glEnable(GL_STENCIL_TEST);
    {
        //  ステンシル値の書き込みをできるようにします。
        glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
        glColorMask(false, false, false, false);
        {
            //  元の画像を ID[0]番に登録します。
            glStencilFunc(GL_ALWAYS, 0, 1);
            yuTextureBox(start,
                         texture,
                         mode,
                         color);
            //  アルファ処理を有効にします。
            glEnable(GL_ALPHA_TEST);
            {
                //  アルファ値がないものを無効なピクセルにします。
                glAlphaFunc(GL_GREATER, 0.0f);
                //  マスク処理をする画像を ID[1]番に登録します。
                glStencilFunc(GL_ALWAYS, 1, 1);
                yuTextureBox(start,
                             mask_Texture,
                             mode,
                             color);
            }
            //  アルファ処理を無効にします。
            glDisable(GL_ALPHA_TEST);
        }
        //  ステンシル値の書き込みをできないようにします。
        glColorMask(true, true, true, true);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

        //  マスク処理の終わった ID[0]番を描画します。
        glStencilFunc(GL_EQUAL, 0, 1);
        yuTextureBox(start,
                     texture,
                     mode,
                     color);
    }
    //  ステンシル処理を無効にします。
    glDisable(GL_STENCIL_TEST);
}

void yuTextureBox(const Vec2f & start,
                  const Texture & texture,
                  const Texture & mask_Texture,
                  const float angle_Rad,
                  const Vec2f& scale,
                  const bool mode,
                  const Color & color)
{
    MASK_FUNK(yuTextureBox(start,
                           texture,
                           angle_Rad,
                           scale,
                           mode,
                           color),
              yuTextureBox(start,
                           mask_Texture,
                           angle_Rad,
                           scale,
                           mode,
                           color));
}

void yuTextureBox(const Vec2f& start,
                  const Vec2f& cut_Size,
                  const Texture& texture,
                  const Texture& mask_Texture,
                  const int animation_Index,
                  const bool mode,
                  const Color& color)
{
    MASK_FUNK(yuTextureBox(start,
                           cut_Size,
                           texture,
                           animation_Index,
                           mode,
                           color),
              yuTextureBox(start,
                           cut_Size,
                           mask_Texture,
                           animation_Index,
                           mode,
                           color));
}

void yuTextureBox(const Vec2f & start,
                  const Vec2f & cut_Size,
                  const Texture & texture,
                  const Texture & mask_Texture,
                  const int animation_Index,
                  const float angle_Rad,
                  const Vec2f & scale,
                  const bool mode,
                  const Color & color)
{
    MASK_FUNK(yuTextureBox(start,
                           cut_Size,
                           texture,
                           animation_Index,
                           angle_Rad,
                           scale,
                           mode,
                           color),
              yuTextureBox(start,
                           cut_Size,
                           mask_Texture,
                           animation_Index,
                           angle_Rad,
                           scale,
                           mode,
                           color));
}
void yuTextureBox(void yuTextureBox(), 
                  void mask_YuTextureBox())
{
    MASK_FUNK(yuTextureBox(),
              mask_YuTextureBox());
}
#undef MASK_FUNK

void yuPushTime()
{
    if (10 < pri_hyt::g_Time_Point.size())
    {
        yuPrintln("PushMax(10) fallOut : yuPushTime");
    }
    else
    {
        pri_hyt::g_Time_Point.push_back(std::chrono::system_clock::now());
    }
}
int yuPopTime(const bool mode)
{
    std::chrono::microseconds elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - pri_hyt::g_Time_Point[pri_hyt::g_Time_Point.size() - 1]);
    if (mode)
    {
        int framelate = elapsed.count() != 0 ? 1000000 / elapsed.count() : 0;
        pri_hyt::g_Time_Point.pop_back();
        return framelate;
    }
    else
    {
        pri_hyt::g_Time_Point.pop_back();
        return elapsed.count();
    }
}

YuFont::YuFont(const std::string& path) :
    size_(64),
    mode_(LEFT),
    color_(Color::white),
    font_(path)
{
    font_.size(size_);
}
void YuFont::textFont(const std::string& path)
{
    font_.read(path);
    font_.size(size_);
}
void YuFont::textFont(const std::string& path, const int size)
{
    font_.read(path);
    size_ = size;
    font_.size(size_);
}
void YuFont::textSize(const int size)
{
    size_ = size;
    font_.size(size_);
}
void YuFont::textColor(const Color& color)
{
    color_ = color;
}
void YuFont::textAlign(const int mode)
{
    mode_ = mode;
}
void YuFont::text(const std::string& str, const Vec2f& position)
{
    switch (mode_)
    {
    case LEFT:
        font_.draw(str, position, color_);
        break;
    case CENTER:
        font_.draw(str,
                   Vec2f(position.x() - font_.drawSize(str).x() / 2,
                         position.y()),
                   color_);
        break;
    case RIGHT:
        font_.draw(str,
                   Vec2f(position.x() - font_.drawSize(str).x(),
                         position.y()),
                   color_);
        break;
    }
}
void YuFont::text(const std::string& str, const Vec2f& position, const Color& color)
{
    textColor(color);
    switch (mode_)
    {

    case LEFT:
        font_.draw(str, position, color_);
        break;
    case CENTER:
        font_.draw(str,
                   Vec2f(position.x() - font_.drawSize(str).x() / 2,
                         position.y()),
                   color_);
        break;
    case RIGHT:
        font_.draw(str,
                   Vec2f(position.x() - font_.drawSize(str).x(),
                         position.y()),
                   color_);
        break;
    }
}
void YuFont::text(const int str, const Vec2f& position)
{
    std::string str_ = std::to_string(str);
    switch (mode_)
    {
    case LEFT:
        font_.draw(str_, position, color_);
        break;
    case CENTER:
        font_.draw(str_,
                   Vec2f(position.x() - str_.size() / 2.0 * font_.drawSize("_").x(),
                         position.y()),
                   color_);
        break;
    case RIGHT:
        font_.draw(str_,
                   Vec2f(position.x() - str_.size() * font_.drawSize("_").x(),
                         position.y()),
                   color_);
        break;
    }
}
void YuFont::text(const int str, const Vec2f& position, const Color& color)
{
    textColor(color);
    std::string str_ = std::to_string(str);
    switch (mode_)
    {
    case LEFT:
        font_.draw(str_, position, color_);
        break;
    case CENTER:
        font_.draw(str_,
                   Vec2f(position.x() - str_.size() / 2.0 * font_.drawSize("_").x(),
                         position.y()),
                   color_);
        break;
    case RIGHT:
        font_.draw(str_,
                   Vec2f(position.x() - str_.size() * font_.drawSize("_").x(),
                         position.y()),
                   color_);
        break;
    }
}
void YuFont::drawScore(const int str, const int no, const Vec2f& position)
{
    std::string str_;
    std::ostringstream ostr_;

    ostr_ << std::setw(no) << std::setfill('0') << std::to_string(str);
    str_ = ostr_.str();

    text(str_, position);
}

YuNovelFont::YuNovelFont(const std::string& path)
    :
    size_(64),
    mode_(LEFT),
    color_(Color::white),
    font_(path, Font::CACHE),

    framelate_(8),
    disp_length_(0)
{
    font_.size(size_);
    font_.draw("render now", Vec2f::Zero(), Color(0.0f, 0.0f, 0.0f, 0.0f));
}
void YuNovelFont::text(const std::string& str, const Vec2f& position)
{
    // 文字数を調べる
    size_t _text_length = strlen_(str);

    // 表示する文字列を生成
    std::string disp_text = substr_(str, 0, disp_length_);

    switch (mode_)
    {
    case LEFT:
        font_.draw(disp_text, position, color_);
        break;
    case CENTER:
        font_.draw(disp_text,
                   Vec2f(position.x() - font_.drawSize(str).x() / 2,
                         position.y()),
                   color_);
        break;
    case RIGHT:
        font_.draw(disp_text,
                   Vec2f(position.x() - font_.drawSize(str).x(),
                         position.y()),
                   color_);
        break;
    }

    if (counter_.Get(framelate_ - 2) == YuCounter::END)
    {
        // 文字数を増やす
        disp_length_ += 1;
        if (disp_length_ > _text_length) {
            disp_length_ = 0;
        }
    }
}

YuCsvIO::YuCsvIO(const std::string& file_Name, const bool mode)
{
    if (mode == true)
    {
        reset_For(file_Name);
    }
    if (mode == false)
    {
        reset_Forr(file_Name);
    }
    save_File_Name_ = file_Name;
}
void YuCsvIO::save_For()
{
    std::ofstream ofstr(save_File_Name_);

    for (int y = 0; y < (int)map_.size(); ++y)
    {
        for (int x = 0; x < (int)map_[y].size(); ++x)
        {
            if (x != map_[y].size() - 1)
            {
                ofstr << map_[y][x] << ",";
            }
            else
            {
                ofstr << map_[y][x];
            }
        }
        ofstr << std::endl;
    }
    return;
}
void YuCsvIO::save_For(const std::string& file_Name)
{
    std::ofstream ofstr(file_Name);

    for (int y = 0; y < (int)map_.size(); ++y)
    {
        for (int x = 0; x < (int)map_[y].size(); ++x)
        {
            if (x != map_[y].size() - 1)
            {
                ofstr << map_[y][x] << ",";
            }
            else
            {
                ofstr << map_[y][x];
            }
        }
        ofstr << std::endl;
    }
    return;
}
void YuCsvIO::save_Forr()
{
    std::ofstream ofstr(save_File_Name_);

    for (int y = (int)map_.size() - 1; y >= 0; --y)
    {
        for (int x = 0; x < (int)map_[y].size(); ++x)
        {
            if (x != map_[y].size() - 1)
            {
                ofstr << map_[y][x] << ",";
            }
            else
            {
                ofstr << map_[y][x];
            }
        }
        ofstr << std::endl;
    }
    return;
}
void YuCsvIO::save_Forr(const std::string& file_Name)
{
    std::ofstream ofstr(file_Name);

    for (int y = (int)map_.size() - 1; y >= 0; --y)
    {
        for (int x = 0; x < (int)map_[y].size(); ++x)
        {
            if (x != map_[y].size() - 1)
            {
                ofstr << map_[y][x] << ",";
            }
            else
            {
                ofstr << map_[y][x];
            }
        }
        ofstr << std::endl;
    }
    return;
}
void YuCsvIO::reset_For(const std::string& file_Name)
{
    map_.clear();
    map_string_.clear();
    std::ifstream ifstr(file_Name);

    if (ifstr.fail())
    {
        yuPrintln("Not Found File : YuCsvIO::reset_For");
        map_ = std::vector<std::vector<int>>(0, std::vector<int>(0));
        return;
    }

    int position;
    std::string str;

    while (getline(ifstr, str))
    {
        if ((position = str.find("//")) != str.npos)
            continue;

        std::vector<std::string> inner;
        while ((position = str.find(",")) != str.npos)
        {
            inner.push_back(str.substr(0, position));
            str = str.substr(position + 1);
        }

        inner.push_back(str);
        map_string_.push_back(inner);
    }

    std::vector<int> temp_;
    for (int i = 0, i_Max = (int)map_string_.size(); i < i_Max; ++i)
    {
        temp_.clear();
        for (int j = 0, j_Max = (int)map_string_[i].size(); j < j_Max; ++j)
        {
            temp_.push_back(std::stoi(map_string_[i][j]));
        }
        map_.push_back(temp_);
    }
}
void YuCsvIO::reset_Forr(const std::string& file_Name)
{
    map_.clear();
    map_string_.clear();
    std::ifstream ifstr(file_Name);

    if (ifstr.fail())
    {
        yuPrintln("Not Found File : YuCsvIO::reset_For");
        map_ = std::vector<std::vector<int>>(0, std::vector<int>(0));
        return;
    }

    int position;
    std::string str;

    while (getline(ifstr, str))
    {
        if ((position = str.find("//")) != str.npos)
            continue;

        std::vector<std::string> inner;
        while ((position = str.find(",")) != str.npos)
        {
            inner.push_back(str.substr(0, position));
            str = str.substr(position + 1);
        }

        inner.push_back(str);
        map_string_.push_back(inner);
    }

    std::vector<int> temp_;
    for (int i = (int)map_string_.size() - 1, i_Min = 0; i >= i_Min; --i)
    {
        temp_.clear();
        for (int j = 0, j_Max = (int)map_string_[i].size(); j < j_Max; ++j)
        {
            temp_.push_back(std::stoi(map_string_[i][j]));
        }
        map_.push_back(temp_);
    }
}
void YuCsvIO::reset_String_For(const std::string& file_Name)
{
    map_.clear();
    map_string_.clear();
    std::ifstream ifstr(file_Name);

    if (ifstr.fail())
    {
        yuPrintln("Not Found File : YuCsvIO::reset_For");
        map_ = std::vector<std::vector<int>>(0, std::vector<int>(0));
        return;
    }

    int position;
    std::string str;

    while (getline(ifstr, str))
    {
        if ((position = str.find("//")) != str.npos)
            continue;

        std::vector<std::string> inner;
        while ((position = str.find(",")) != str.npos)
        {
            inner.push_back(str.substr(0, position));
            str = str.substr(position + 1);
        }

        inner.push_back(str);
        map_string_.push_back(inner);
    }
}

YuCsv_Editor::YuCsv_Editor(const std::string& edit_File_Name, const std::string& read_Map_File_Name)
    :
    scale_(1.0f),
    is_Animation_(0),
    edit_Mode_(FALSE),
    grid_Draw_(TRUE),
    texture_Animation_Number_(0),
    set_Chip_Number_(0),
    right_Box_Size_(Vec2f(128.0f, 0.0f)),
    top_Box_Size_(Vec2f(0.0f, 128.0f)),
    default_Save_File_Name_(read_Map_File_Name),
    save_File_Name_(read_Map_File_Name),
    edge_Base_("src/yumayoLib/edge_base.hyt"),
    edge_("src/yumayoLib/edge.hyt"),
    scroll_Bar_Position_(Vec2f::Zero()),
    scroll_Bar_Buf_Position_Y_(0.0f),
    scroll_Bar_Size_(Vec2f::Zero())
{
    edit_.reset_String_For(edit_File_Name);
    map_Data_.reset_Forr(read_Map_File_Name);
    //Yucounterは使用時に自動的に初期化されるため、ここでの処理はありません。

    for (int n = 0; n < (int)edit_.read_String().size(); ++n)
    {
        if (edit_.read_String()[n][1] == "air" || edit_.read_String()[n][1] == "")
        {
            chip_Texture_.push_back(Texture("src/yumayoLib/null.hyt"));
            continue;
        }
        chip_Texture_.push_back(Texture("res/texture/" + edit_.read_String()[n][1] + ".png"));
    }
    Vec2f _window_Size = pri_hyt::g_Env_ptr->viewSize();
    float _texture_Size_Y = (64 + 17);
    for (int n = 0; n < (int)edit_.read_String().size(); ++n)
    {
        edit_Texture_.push_back(YuAnimation_Texture_(Vec2f(_window_Size.x() / 2 - _texture_Size_Y,
                                                           _window_Size.y() / 2 - top_Box_Size_.y() - _texture_Size_Y / 2.0f - _texture_Size_Y * n),
                                                     &chip_Texture_[n]));
    }

    float _scroll_Bar_Size_Y = ((_window_Size.y() - top_Box_Size_.y()) / (_texture_Size_Y * (int)edit_.read_String().size())) * (_window_Size.y() - top_Box_Size_.y());
    scroll_Bar_Size_ = Vec2f(17.0f, _scroll_Bar_Size_Y);
    scroll_Bar_Position_ = Vec2f(_window_Size.x() / 2.0f - scroll_Bar_Size_.x(), _window_Size.y());
    if (_window_Size.y() / 2 - top_Box_Size_.y() <= scroll_Bar_Position_.y() + scroll_Bar_Size_.y())
    {
        scroll_Bar_Position_.y() = _window_Size.y() / 2 - top_Box_Size_.y() - scroll_Bar_Size_.y();
    }
    if (scroll_Bar_Position_.y() <= -_window_Size.y() / 2)
    {
        scroll_Bar_Position_.y() = -_window_Size.y() / 2;
    }
}
void YuCsv_Editor::edit(const Vec2f& origin, const Vec2f& camera_Position, int chip_Size)
{
    edit_Open_();

    if (edit_Mode_ == TRUE)
    {
        edit_Close_();

        chip_Size *= scale_;

        std::vector<std::vector<int>> _map_Data = map_Data_.read();

        edit_Chip_Texture_Draw_(origin, camera_Position, chip_Size, _map_Data);

        edit_Chip_Texture_Update_(origin, camera_Position, chip_Size, _map_Data);

        edit_Grid_Draw_(origin, camera_Position, chip_Size);

        edit_Texture_Animation_Draw_(camera_Position);

        edit_Save_();
    }
}
void YuCsv_Editor::edit_Open_()
{
    if (pri_hyt::g_Env_ptr->isPressKey(GLFW_KEY_LEFT_CONTROL) && pri_hyt::g_Env_ptr->isPushKey(GLFW_KEY_F3) && is_Animation_ == 0)
    {
        is_Animation_ = 1;
    }

    if (is_Animation_ == 1)
    {
        Vec2f _window_Size = pri_hyt::g_Env_ptr->viewSize();
        switch (counter_.Get(16 + (int)edit_.read_String().size() * 4))
        {
        case YuCounter::INIT:
            edit_Mode_ = TRUE;
            break;
        case YuCounter::UPDATE:
            if (counter_.Get_Frame() <= 16)
            {
                right_Box_Size_.y() -= _window_Size.y() / 16;
                top_Box_Size_.x() -= _window_Size.x() / 16;
            }
            else
            {
                if (sYuFrame::Get()() % 4 == 0)
                {
                    ++texture_Animation_Number_;
                }
            }
            break;
        case YuCounter::END:
            texture_Animation_Number_ = (int)edit_.read_String().size();
            is_Animation_ = 2;
            break;
        default:
            break;
        }
    }
}
void YuCsv_Editor::edit_Close_()
{
    if (pri_hyt::g_Env_ptr->isPressKey(GLFW_KEY_LEFT_CONTROL) && pri_hyt::g_Env_ptr->isPushKey(GLFW_KEY_F3) && is_Animation_ == 2)
    {
        is_Animation_ = 3;
    }

    if (is_Animation_ == 3)
    {
        Vec2f _window_Size = pri_hyt::g_Env_ptr->viewSize();
        switch (counter_.Get(16 + (int)edit_.read_String().size() * 4))
        {
        case YuCounter::INIT:
            break;
        case YuCounter::UPDATE:
            if ((int)edit_.read_String().size() * 4 < counter_.Get_Frame())
            {
                right_Box_Size_.y() += _window_Size.y() / 16;
                top_Box_Size_.x() += _window_Size.x() / 16;
            }
            else
            {
                if (sYuFrame::Get()() % 4 == 0)
                {
                    --texture_Animation_Number_;
                }
            }
            break;
        case YuCounter::END:
            edit_Mode_ = FALSE;
            texture_Animation_Number_ = 0;  //  念のため
            is_Animation_ = 0;
            break;
        default:
            break;
        }
    }
}
void YuCsv_Editor::edit_Chip_Texture_Draw_(const Vec2f& origin, const Vec2f& camera_Position, const int chip_Size, const std::vector<std::vector<int>>& map_Data)
{
    Vec2i array_Position_ = Vec2i(camera_Position.x() / chip_Size, camera_Position.y() / chip_Size);
    Vec2i _window_Chip_Size_2 = Vec2i(pri_hyt::g_Env_ptr->viewSize().x() / chip_Size / 2, pri_hyt::g_Env_ptr->viewSize().y() / chip_Size / 2);
    Vec2i _map_Data_Size = Vec2i((int)map_Data_.read()[0].size(), (int)map_Data_.read().size());
    glPushMatrix();
    glScaled(scale_, scale_, 1.0f);
    for (int y = array_Position_.y() - _window_Chip_Size_2.y() - 1, y_Max = array_Position_.y() + _window_Chip_Size_2.y() + 1; y <= y_Max; ++y)
    {
        for (int x = array_Position_.x() - _window_Chip_Size_2.x() - 1, x_Max = array_Position_.x() + _window_Chip_Size_2.x() + 0; x <= x_Max; ++x)
        {
            if (y < 0 || x < 0 || _map_Data_Size.y() <= y || _map_Data_Size.x() <= x)
                ;
            else
            {
                yuTextureBox(Vec2f(x * chip_Size / scale_, y * chip_Size / scale_),
                             chip_Texture_[map_Data[y][x]]);
            }
        }
    }
    glPopMatrix();
}
void YuCsv_Editor::edit_Chip_Texture_Update_(const Vec2f& origin, const Vec2f& camera_Position, const  int chip_Size, const std::vector<std::vector<int>>& map_Data)
{
    Vec2f _mouse_Position = pri_hyt::g_Env_ptr->mousePosition();
    Vec2i _mouse_Array_Position = Vec2i((camera_Position.x() + _mouse_Position.x()) / chip_Size, (camera_Position.y() + _mouse_Position.y()) / chip_Size);
    if (_mouse_Position.x() < pri_hyt::g_Env_ptr->viewSize().x() / 2 - right_Box_Size_.x() &&
        _mouse_Position.y() < pri_hyt::g_Env_ptr->viewSize().y() / 2 - top_Box_Size_.y())
    {
        if (_mouse_Array_Position.x() < 0)
        {
            _mouse_Array_Position.x() -= 1;
        }
        if (_mouse_Array_Position.y() < 0)
        {
            _mouse_Array_Position.y() -= 1;
        }
        yuTextureBox(Vec2f(_mouse_Array_Position.x() * chip_Size, _mouse_Array_Position.y() * chip_Size),
                     chip_Texture_[set_Chip_Number_],
                     0.0f,
                     Vec2f(scale_, scale_));
        yuFillBox(Vec2f(_mouse_Array_Position.x() * chip_Size, _mouse_Array_Position.y() * chip_Size),
                  Vec2f(chip_Size, chip_Size),
                  Color(1.0f, 1.0f, 1.0f, 0.5f));
        if (pri_hyt::g_Env_ptr->isPressButton(Mouse::LEFT))
        {
            if (_mouse_Array_Position.y() < 0 || _mouse_Array_Position.x() < 0 || (int)map_Data.size() <= _mouse_Array_Position.y() || (int)map_Data[_mouse_Array_Position.y()].size() <= _mouse_Array_Position.x())
                ;
            else
            {
                map_Data_.reWrite(_mouse_Array_Position, set_Chip_Number_);
            }
        }
        if (pri_hyt::g_Env_ptr->isPressButton(Mouse::RIGHT))
        {
            if (_mouse_Array_Position.y() < 0 || _mouse_Array_Position.x() < 0 || (int)map_Data.size() <= _mouse_Array_Position.y() || (int)map_Data[_mouse_Array_Position.y()].size() <= _mouse_Array_Position.x())
                ;
            else
            {
                map_Data_.reWrite(_mouse_Array_Position, 0);
            }
        }
    }
}
void YuCsv_Editor::edit_Grid_Draw_(const Vec2f& origin, const Vec2f& camera_Position, const int chip_Size)
{
    if (pri_hyt::g_Env_ptr->isPressKey(GLFW_KEY_LEFT_ALT) && pri_hyt::g_Env_ptr->isPushKey(GLFW_KEY_G)) grid_Draw_ = !grid_Draw_;
    if (grid_Draw_ == TRUE)
    {
        Vec2i _window_Chip_Size_2 = Vec2i(pri_hyt::g_Env_ptr->viewSize().x() / chip_Size / 2, pri_hyt::g_Env_ptr->viewSize().y() / chip_Size / 2);
        Vec2i _Camera_Chip_Size = Vec2i(camera_Position.x() / chip_Size, camera_Position.y() / chip_Size);
        Vec2i _window_Size_2 = Vec2i(pri_hyt::g_Env_ptr->viewSize().x() / 2, pri_hyt::g_Env_ptr->viewSize().y() / 2);
        for (int y = -_window_Chip_Size_2.y() - 1 + _Camera_Chip_Size.y(); y < _window_Chip_Size_2.y() + 2 + _Camera_Chip_Size.y(); ++y)
        {
            drawLine(-_window_Size_2.x() + camera_Position.x() - chip_Size, y * chip_Size,
                     _window_Size_2.x() + camera_Position.x() + chip_Size, y * chip_Size,
                     2,
                     Color::white);
        }
        for (int x = -_window_Chip_Size_2.x() - 1 + _Camera_Chip_Size.x(); x < _window_Chip_Size_2.x() + 2 + _Camera_Chip_Size.x(); ++x)
        {
            drawLine(x * chip_Size, -_window_Size_2.y() + camera_Position.y() - chip_Size,
                     x * chip_Size, _window_Size_2.y() + camera_Position.y() + chip_Size,
                     2,
                     Color::white);
        }
    }
}
void YuCsv_Editor::edit_Texture_Animation_Draw_(const Vec2f& camera_Position)
{
    glPushMatrix();
    glTranslated(camera_Position.x(), camera_Position.y(), 0);
    Vec2f _window_Size = pri_hyt::g_Env_ptr->viewSize();
    Vec2f _mouse_Position = pri_hyt::g_Env_ptr->mousePosition();
    yuFillBox(Vec2f(_window_Size.x() / 2 - 128, _window_Size.y() / 2),
              right_Box_Size_,
              Color(0, 0, 0, 0.8f));
    

    if (scroll_Bar_Position_.x() <= _mouse_Position.x() && scroll_Bar_Position_.y() <= _mouse_Position.y() &&
        _mouse_Position.x() <= scroll_Bar_Position_.x() + scroll_Bar_Size_.x() && _mouse_Position.y() <= scroll_Bar_Position_.y() + scroll_Bar_Size_.y())
    {
        yuFillBox(scroll_Bar_Position_,
                  scroll_Bar_Size_,
                  Color::white);
        if (pri_hyt::g_Env_ptr->isPushButton(Mouse::LEFT))
        {
            scroll_Bar_Buf_Position_Y_ = scroll_Bar_Position_.y() - _mouse_Position.y();
        }
    }
    else
    {
        yuFillBox(scroll_Bar_Position_,
                  scroll_Bar_Size_,
                  Color(1.0f, 1.0f, 1.0f, 0.5f));
    }

    if (pri_hyt::g_Env_ptr->isPressButton(Mouse::LEFT))
    {
        if (scroll_Bar_Buf_Position_Y_ != 0.0f &&
            scroll_Bar_Position_.x() - right_Box_Size_.x() + scroll_Bar_Size_.x() <= _mouse_Position.x() &&
            _mouse_Position.x() <= scroll_Bar_Position_.x() + right_Box_Size_.x() + scroll_Bar_Size_.x())
        {
            scroll_Bar_Position_.y() = _mouse_Position.y() + scroll_Bar_Buf_Position_Y_;
        }
        if (_window_Size.y() / 2 - top_Box_Size_.y() <= scroll_Bar_Position_.y() + scroll_Bar_Size_.y())
        {
            scroll_Bar_Position_.y() = _window_Size.y() / 2 - top_Box_Size_.y() - scroll_Bar_Size_.y();
        }
        if (scroll_Bar_Position_.y() <= -_window_Size.y() / 2)
        {
            scroll_Bar_Position_.y() = -_window_Size.y() / 2;
        }
        float _texture_Size_Y = (64 + 17);
        float _scroll_Bar_Scale_Y = ((_window_Size.y() - top_Box_Size_.y()) / (_texture_Size_Y * (int)edit_.read_String().size()));
        for (auto n = 0; n < texture_Animation_Number_; ++n)
        {
            edit_Texture_[n].Set_Scroll_Position_Y(-(scroll_Bar_Position_.y() - (_window_Size.y() / 2.0f - top_Box_Size_.y() - scroll_Bar_Size_.y())) / _scroll_Bar_Scale_Y +
                                                   (_window_Size.y() / 2 - top_Box_Size_.y() - _texture_Size_Y / 2.0f - _texture_Size_Y * n));
        }
    }
    if (pri_hyt::g_Env_ptr->isPullButton(Mouse::LEFT))
    {
        scroll_Bar_Buf_Position_Y_ = 0.0f;
    }

    if (pri_hyt::g_Env_ptr->isPushButton(Mouse::LEFT))
    {
        bool _check_Out_Ok = false;
        for (auto n = 0; n < texture_Animation_Number_; ++n)
        {
            if (edit_Texture_[n].Get_Mouse_Over())
            {
                _check_Out_Ok = true;
                break;
            }
        }
        if (_check_Out_Ok)
        {
            for (auto n = 0; n < texture_Animation_Number_; ++n)
            {
                edit_Texture_[n].check_Out();
                set_Chip_Number_ = 0;
            }
        }
    }
    for (auto n = 0; n < texture_Animation_Number_; ++n)
    {
        if (edit_Texture_[n].Get_Clicked() == true)
        {
            set_Chip_Number_ = n;
        }
        edit_Texture_[n].update();
        edit_Texture_[n].draw(*this);
    }

    //  上に設置されたボックスは最後に描画します
    yuFillBox(Vec2f(_window_Size.x() / 2.0f, _window_Size.y() / 2.0f - top_Box_Size_.y()),
              top_Box_Size_,
              Color(0.0f, 0.0f, 0.0f, 0.8f));
    //  上に設置されたボックスは最後に描画します
    yuFillBox(Vec2f(_window_Size.x() / 2.0f, _window_Size.y() / 2.0f),
              Vec2f(-top_Box_Size_.y(), -top_Box_Size_.y()),
              Color(0.0f, 0.0f, 0.0f, 1.0f));

    glPopMatrix();
}
void YuCsv_Editor::edit_Save_()
{
    if (pri_hyt::g_Env_ptr->isPressKey(GLFW_KEY_LEFT_CONTROL) && pri_hyt::g_Env_ptr->isPressKey(GLFW_KEY_LEFT_SHIFT) && pri_hyt::g_Env_ptr->isPushKey(GLFW_KEY_E))
    {
        map_Data_.save_Forr(save_File_Name_);

        yuPrintln("save file (" + save_File_Name_ + ")");
        return;
    }
}
void YuCsv_Editor::YuAnimation_Texture_::mouse_Over_()
{
    Vec2f _mouse_Position = pri_hyt::g_Env_ptr->mousePosition();
    if (position_.x() - 32 <= _mouse_Position.x() && _mouse_Position.x() <= 32 + position_.x() &&
        position_.y() - 32 <= _mouse_Position.y() && _mouse_Position.y() <= 32 + position_.y())
    {
        angle_ = float(-M_PI_4 / 2.0f);
        is_Mouse_Over_ = true;
        if (pri_hyt::g_Env_ptr->isPushButton(Mouse::LEFT))
        {
            check_ = true;
        }
    }
    else
    {
        angle_ = 0.0f;
        is_Mouse_Over_ = false;
    }
}

YuCounter::YuCounter() :
    tick_(INIT),
    frame_Count_(0)
{ }
int YuCounter::Get(const int count)
{
    if (count + 1 < sYuFrame::Get().Get() - frame_Count_)
    {
        clear();
    }

    switch (tick_)
    {
    case INIT:
        //	処理A
        //	一度だけ呼ばれるので、初期化などに使いましょう。
        frame_Count_ = sYuFrame::Get().Get();
        tick_ = UPDATE;
        return INIT;

    case UPDATE:
        //	処理B
        //	カウントを待っている間ずっと呼ばれます。
        //	その間にプレイヤーの動きを止めるなどの使い方ができます。
        if (count - 1 < sYuFrame::Get().Get() - frame_Count_)
        {
            tick_ = END;
        }
        return UPDATE;

    case END:
        //	処理C
        //	カウントが終了する時に一度だけ呼ばれます。
        //	※ここで終了条件を書かないと、再び、初期化されてしまうので注意しましょう。
        tick_ = INIT;
        return END;
    }
    return NONE;
}
void YuCounter::clear()
{
    tick_ = INIT;
}
int YuCounter::Get_Frame()
{
    return sYuFrame::Get().Get() - frame_Count_;
}
