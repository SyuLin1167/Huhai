#pragma once

#include<unordered_map>
#include<string>

#include"../../ObjectBase/ObjectBase.h"

/*Furnitureクラス*/
class Furniture :public ObjBase
{
public:
    //家具タグ
    enum FurName
    {
        Room = 0,
        Stage,
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="tag">:タグ</param>
    Furniture(FurName tag);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Furniture();

    /// <summary>
    /// 読み込み処理
    /// </summary>
    /// <param name="tag">:タグ</param>
    void Load(FurName tag);

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
    //家具モデルファイルデータ
    std::unordered_map<FurName, std::string> furModel
    {
        {FurName::Room,"../Assets/Map/Furniture/RoomFur.mv1"},
        {FurName::Stage,"../Assets/Map/Furniture/StageFur.mv1"},
    };

    //家具当たり判定ファイルデータ
    std::unordered_map<FurName, std::string> furColModel
    {
        {FurName::Room,"../Assets/Map/Furniture/RoomFurCol.mv1"},
        {FurName::Stage,"../Assets/Map/Furniture/StageFurCol.mv1"},
    };
};