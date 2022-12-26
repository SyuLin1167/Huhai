#pragma once
#include<vector>

/*種類別タグクラス*/
enum class ObjectTag :unsigned char
{
    Camera,     //カメラ
    Player,     //プレイヤー
    Enemy,      //エネミー
};

/*ループ制御用*/
constexpr static ObjectTag ObjTagAll[] =
{
    ObjectTag::Camera,
    ObjectTag::Player,
    ObjectTag::Enemy,
};

