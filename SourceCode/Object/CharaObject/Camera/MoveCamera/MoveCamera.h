#pragma once
#include"../../../ObjectBase/ObjectBase.h"

    /*MoveCameraクラス*/
class MoveCamera :public ObjectBase
{
public:
    /// <summary>
    /// MoveCameraコンストラクタ
    /// </summary>
    MoveCamera();

    /// <summary>
    /// MoveCameraデストラクタ
    /// </summary>
    ~MoveCamera() {};

    /// <summary>
    /// MoveCamera更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override {};

    /// <summary>
    /// MoveCamera描画
    /// </summary>
    void Draw()override {};

};

