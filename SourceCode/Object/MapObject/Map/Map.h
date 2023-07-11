#pragma once

#include<unordered_map>
#include<string>

#include"../../ObjectBase/ObjectBase.h"

/*Mapクラス*/
class Map :public ObjBase
{
public:
    //マップタグ
    enum MapTag
    {
        TITLE = 0,
        ROOM,
        STAGE,
        ESCAPE,
        ESCAPEMAIN,
        GOAL,
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="maptag">:マップタグ</param>
    Map(MapTag tag);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Map();

    /// <summary>
    /// 読み込み処理
    /// </summary>
    void LoadModel();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;


private:
    class Sound* mapSound;      //サウンド
    MapTag mapTag;                 //タグ

    //マップファイルデータ
    std::unordered_map<MapTag, std::string> mapFile
    {
        {MapTag::TITLE,"../Assets/Map/Stage/Title.mv1"},
        {MapTag::ROOM,"../Assets/Map/Room/Room.mv1"},
        {MapTag::STAGE,"../Assets/Map/Stage/Stage.mv1"},
        {MapTag::ESCAPE,"../Assets/Map/Stage/Escape.mv1"},
        {MapTag::ESCAPEMAIN,"../Assets/Map/Stage/EscapeMain.mv1"},
        {MapTag::GOAL,"../Assets/Map/Stage/GoalRoom.mv1"},
    };

    //当たり判定ファイルデータ
    std::unordered_map<MapTag, std::string> mapColFile
    {
        {MapTag::ROOM,"../Assets/Map/Room/Room.mv1"},
        {MapTag::STAGE,"../Assets/Map/Stage/StageCol.mv1"},
        {MapTag::ESCAPE,"../Assets/Map/Stage/EscapeCol.mv1"},
        {MapTag::GOAL,"../Assets/Map/Stage/GoalRoom.mv1"},
    };
};
