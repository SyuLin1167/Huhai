#pragma once
#include"../../ObjectBase/ObjectBase.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Model/Model.h"

        /*Furnitureクラス*/
class Furniture :public ObjectBase
{
public:
    /// <summary>
    /// Furnitureコンストラクター
    /// </summary>
    /// <param name="furtag">:家具タグ</param>
    Furniture(int furtag);

    /// <summary>
    /// Furnitureデストラクター
    /// </summary>
    ~Furniture();

    /// <summary>
    /// Furnitureモデル読み込み処理
    /// </summary>
    /// <param name="furtag">:家具タグ</param>
    void LoadModel(int furtag);

    /// <summary>
    /// Furniture更新処理
    /// </summary>
    /// <param name="deltaTime">:フレームレート</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// Furniture描画処理
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