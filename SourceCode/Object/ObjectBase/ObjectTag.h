#pragma once
#include<vector>

/*種類別タグクラス*/
enum class ObjectTag :unsigned char
{
    Camera,     //カメラ
    Map,        //マップ
    Furniture,  //家具
    Light,      //照明
    Player,     //プレイヤー
    Ghost,      //エネミー
    Man,        //男性
    UI,         //UI
};

/*ループ制御用*/
constexpr static ObjectTag ObjTagAll[] =
{
    ObjectTag::Camera,
    ObjectTag::Map,
    ObjectTag::Furniture,
    ObjectTag::Light,
    ObjectTag::Player,
    ObjectTag::Ghost,
    ObjectTag::Man,
    ObjectTag::UI,
};

