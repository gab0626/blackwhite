#include "../Top/Top.h"
////����������A�g�Y
//�����ł̓u���b�N����ǂ�ȓ���������̂�������
//�u���b�N�̃M�~�b�N�͂V��ނ���
//�ʒu�ƃu���b�N�̏��̓}�b�v���񂩂�ŏ��ɑS�����炦�܂�
//
///�}�b�v�ɂ̓v���C���[��pos��size��vec��
///����block�ɂǂꂾ���߂荞�񂾂���Ԃ��֐������


class Block 
{
public:
    Block();
    void update();
    void draw();
    void setup();

    void setPos(Vec2f _pos);
    void setStatus(BLOCK _block);

    Vec2f Collision(Object _player ,
        BLOCK _up, BLOCK _down,
        DIRECTION _direction,
        int move_vector);

private:
    BLOCK status;
    Object block;
    

    /////////////////////�g�Y//�ϐ�///////////////////////



    //////////////////////����//�ϐ�/////////////////////////



};