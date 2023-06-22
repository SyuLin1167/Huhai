#pragma once
#include"../../ObjectBase/ObjectBase.h"

/*Furnitureクラス*/
class Furniture :public ObjBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="furtag">:家具タグ</param>
    Furniture(int furtag);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Furniture();

    /// <summary>
    /// 読み込み処理
    /// </summary>
    /// <param name="tag">:タグ</param>
    void Load(int tag);

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

    enum FurName
    {
        Room = 0,
        Stage,
    };

private:
    class Model* furModel;
    class Model* furColModel;
};