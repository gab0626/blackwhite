#pragma once
#include "����.h"
#include "GamePad.h"

//����
//�g���Ƃ��͌^�w������Ă�����
enum class DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NON
};
//�u���b�N�̑傫��
enum class BLOCKSIZE
{
    WIDTH = 100,
    HEIGHT = 100
};
//��ʑ傫��
enum WINDOW
{
    WIDTH = 1920,
    HEIGHT = 1080,
};
///�V�[��
enum class SCENE
{
    TITLE,
    STAGESELECT,
    GAME,
};
//�u���b�N�̎��
enum class BLOCK
{
    NORMAL = 1,
    
    MOVE,
    FALL,
    DOUBLE,

    PLAYER_START_POS =10

};
//�v���C���[�̏��
enum class CONDITION{
    BLACK,
    WHITE,
	STRIPE,
    NONE
};


//�ʒu
//�傫��
//�ړ���
struct Object
{
    Vec2f pos;
    Vec2f size;
    Vec2f vec;
};


//env�̃V���O���g��
class App
{
public:
    static AppEnv& get()
    {
        static AppEnv env(WIDTH, HEIGHT/*, false, true*/);

        return env;
    }
};

#define env App::get()

//�����_���̃V���O���g��
class _Random
{
public:
    static Random& get()
    {
        static Random rand;
        return rand;
    }
};
#define random _Random::get()
