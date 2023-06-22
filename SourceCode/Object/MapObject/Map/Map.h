#pragma once
#include"../../ObjectBase/ObjectBase.h"

/*Mapクラス*/
class Map :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="maptag">:マップタグ</param>
    Map(int tag);

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

private:
    class Model* mapModel;      //モデル
    class Sound* mapSound;      //サウンド
    int mapTag;                 //タグ
};
