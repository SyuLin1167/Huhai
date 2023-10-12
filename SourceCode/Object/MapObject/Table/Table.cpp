#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<fstream>

#include "Table.h"
#include"../../../Asset/AssetManager/AssetManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="objNum">:オブジェクト番号</param>
Table::Table(const int objNum)
    :ObjBase(ObjTag::Furniture)
{
    //ファイル読み込み
    std::ifstream ifs("../SourceCode/Object/MapObject/Table/TableData.json");
    rapidjson::Document doc;

    //ファイル解析
    if (ifs.good())
    {
        rapidjson::IStreamWrapper isw(ifs);

        doc.ParseStream(isw);
    }
    ifs.close();

    //データを読み取って座標・向きに代入
    const std::string key = std::to_string(objNum);
    auto& data = doc["data"][key.c_str()];

    objPos.x = data["pos"].GetArray()[0].GetFloat();
    objPos.y = data["pos"].GetArray()[1].GetFloat();
    objPos.z = data["pos"].GetArray()[2].GetFloat();
    objDir.y = data["dir"].GetFloat();

    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Table/Table.mv1");
    MV1SetScale(objHandle, objScale);
    MV1SetPosition(objHandle, objPos);
    MV1SetRotationXYZ(objHandle, VGet(0.0f, objDir.y / ONE_HALF_PI * DX_PI_F, 0.0f));

    //当たり判定設定
    colModel = AssetManager::GetMesh("../Assets/Map/Table/ColTable.mv1");
    MV1SetPosition(colModel, objPos);
    MV1SetScale(colModel, VGet(0.1f, 0.1f, 0.1f));
    MV1SetRotationXYZ(colModel, VGet(0.0f, objDir.y / ONE_HALF_PI * DX_PI_F, 0.0f));            //モデルの向き設定
}

/// <summary>
/// デストラクタ
/// </summary>
Table::~Table()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:フレームレート</param>
void Table::Update(float delataTime)
{
    //当たり判定更新
    ColUpdate();
}

/// <summary>
/// 描画処理
/// </summary>
void Table::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}