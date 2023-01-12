#pragma once
#include<vector>

/*種類別タグクラス*/
enum class ObjectTag :unsigned char
{
    Camera,     //カメラ
    Block,      //ブロック
    Map,        //マップ
    Door,       //ドア
    Player,     //プレイヤー
    Enemy,      //エネミー
};

/*ループ制御用*/
constexpr static ObjectTag ObjTagAll[] =
{
    ObjectTag::Camera,
    ObjectTag::Map,
    ObjectTag::Door,
    ObjectTag::Block,
    ObjectTag::Player,
    ObjectTag::Enemy,
};

