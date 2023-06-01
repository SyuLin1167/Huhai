#pragma once
#include"../../ObjectBase/ObjectBase.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Model/Model.h"

/*Mapクラス*/
class Map:public ObjectBase
{
public:
    /// <summary>
    /// Mapコンストラクタ
    /// </summary>
    /// <param name="maptag">:マップタグ</param>
    Map(int maptag);

    /// <summary>
    /// Mapデストラクター
    /// </summary>
    ~Map();

    /// <summary>
    /// Map読み込み処理
    /// </summary>
    void LoadModel();

    /// <summary>
    /// Map更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// Map描画処理
    /// </summary>
    void Draw()override;


    enum MapName
    {
        TITLE=0,
        ROOM,
        STAGE,
        ESCAPE,
        ESCAPEMAIN,
        GOAL,
    };

private:
    class Model* mapModel;
    int mapTag;
};

