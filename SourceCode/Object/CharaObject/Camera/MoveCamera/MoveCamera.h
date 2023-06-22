#pragma once
#include"../../../ObjectBase/ObjectBase.h"

/*MoveCameraクラス*/
class MoveCamera :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MoveCamera();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~MoveCamera() {};

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime)override {};

    /// <summary>
    /// 描画
    /// </summary>
    void Draw()override {};

};

