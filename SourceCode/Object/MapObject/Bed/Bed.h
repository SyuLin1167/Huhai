#pragma once
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectBase/ObjectBase.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Scene/TitleScene/Title.h"

        /*Bedクラス*/
class Bed :public ObjectBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Bed();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Bed();

    /// <summary>
    /// 読み込み処理
    /// </summary>
    void Load();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;
};
