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
    /// Bedコンストラクタ
    /// </summary>
    Bed();

    /// <summary>
    /// Bedデストラクタ
    /// </summary>
    ~Bed();

    /// <summary>
    /// Bed読み込み処理
    /// </summary>
    void Load();

    /// <summary>
    /// Bed更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Bed描画処理
    /// </summary>
    void Draw()override;
};

