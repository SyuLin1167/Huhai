#pragma once
#include<vector>

/*種類別タグクラス*/
enum class ObjectTag :unsigned char
{
    Camera,     //カメラ
    Block,      //ブロック
    Map,        //マップ
    Door,       //ドア
    Furniture,  //家具
    Player,     //プレイヤー
    Enemy      //エネミー
};

/*ループ制御用*/
constexpr static ObjectTag ObjTagAll[] =
{
    ObjectTag::Camera,
    ObjectTag::Map,
    ObjectTag::Door,
    ObjectTag::Furniture,
    ObjectTag::Block,
    ObjectTag::Player,
    ObjectTag::Enemy,
};

