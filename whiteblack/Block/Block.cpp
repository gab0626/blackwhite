#include "Block.h"


Block::Block(){
    setup();
    
}

void Block::update(){
    switch (status)
    {
    case BLOCK::FALL_:
        break;
    case BLOCK::MOVE_:
        break;
    default:


        break;
    }
    
}

void Block::draw(){

}

void Block::setup(){
    block.size = Vec2f((float)BLOCKSIZE::WIDTH, 
        (float)BLOCKSIZE::HEIGTH);
    block.vec = Vec2f(0, 0);

}
///�u���b�N�̃|�W�V�����̃Z�b�g
void Block::setPos(Vec2f _pos){
    block.pos = _pos;
}
//�u���b�N�̃X�e�[�^�X�̃Z�b�g
void Block::setStatus(BLOCK _status){
    status = _status;
}

//�v���C���[�̏��
//��̃u���b�N�̏��
//���̃u���b�N�̏��
//�������Ƃ��̌���
//���}�X�������̂��H
Vec2f Block::Collision(Object _player, 
    BLOCK _up, BLOCK _down,
    DIRECTION _direction = DIRECTION::NON,
    int move_vector = 0){



    switch (status)
    {
    case BLOCK::FALL_:
        break;
    case BLOCK::MOVE_:
        break;
    default:
        break;
    }







    return Vec2f(0,0);
}
