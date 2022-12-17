#pragma once
#include<vector>

/*種類別タグクラス*/
enum class ObjectTag :unsigned char
{
    Player,     //プレイヤー
    Archer,     //アーチャー
    Enemy,      //エネミー
};

/*ループ制御用*/
constexpr static ObjectTag ObjTagAll[] =
{
    ObjectTag::Player,
    ObjectTag::Archer,
    ObjectTag::Enemy,
};

