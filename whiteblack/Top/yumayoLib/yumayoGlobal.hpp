#pragma once

_PRI_HYT_BEGIN

//  ���Ԃ̌v���Ɏg���܂��B
std::vector<std::chrono::time_point<std::chrono::system_clock>> g_Time_Point;

//  �Q�[�����N�����Ă���̃t���[������ۑ����܂��B
int g_Frame = 0;

//  �f�o�b�O���[�h���I���ɂȂ��Ă��邩��ۑ����܂��B
//  �f�o�b�O���[�h�̓��[�}�����C�u�����ŋ��ʂƂȂ�܂��B
int g_Debug = FALSE;

//  AppEnv�ւ̃|�C���^��錾���܂��B
//  AppEnv��錾���������ŁA�A�h���X�������Ă��������B
//  sYuAppEnv::Set(&env)���g��Ȃ��Ɗ���@�\���Ȃ����̂�����̂Œ��ӂ��܂��傤�B
AppEnv* g_Env_ptr;

_PRI_HYT_END