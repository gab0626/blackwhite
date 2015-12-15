#pragma once

_PRI_HYT_BEGIN

//  時間の計測に使います。
std::vector<std::chrono::time_point<std::chrono::system_clock>> g_Time_Point;

//  ゲームが起動してからのフレーム数を保存します。
int g_Frame = 0;

//  デバッグモードがオンになっているかを保存します。
//  デバッグモードはユーマヨライブラリで共通となります。
int g_Debug = FALSE;

//  AppEnvへのポインタを宣言します。
//  AppEnvを宣言した直下で、アドレスを代入してください。
//  sYuAppEnv::Set(&env)を使わないと幾つか機能しないものがあるので注意しましょう。
AppEnv* g_Env_ptr;

_PRI_HYT_END