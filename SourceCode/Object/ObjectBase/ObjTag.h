#pragma once

/*オブジェクトタグ*/
enum class ObjTag :unsigned char
{
    Camera,     //カメラ
    Map,        //マップ
    Furniture,  //家具
    Light,      //照明
    Player,     //プレイヤー
    Ghost,      //エネミー
    Man,        //男性
    UI,         //UI
    Remarks,    //セリフ
};

/*全タグ*/
constexpr static ObjTag ObjTagAll[] =
{
    ObjTag::Camera,
    ObjTag::Map,
    ObjTag::Furniture,
    ObjTag::Light,
    ObjTag::Player,
    ObjTag::Ghost,
    ObjTag::Man,
    ObjTag::UI,
    ObjTag::Remarks,
};

