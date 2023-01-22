#include "Map.h"

// @brief Mapコンストラクター //

Map::Map()
	:ObjectBase(ObjectTag::Map)
{
	Load();
}

// @brief Mapコンストラクター(位置セット) //

Map::Map(VECTOR mapPos)
	:ObjectBase(ObjectTag::Map,mapPos)
{
	Load();
}

// @brief Mapデストラクター //

Map::~Map()
{
	AssetManager::ReleaseMesh(objHandle);					//メッシュの削除
}

// @brief Map読み込み処理 //

void Map::Load()
{
	//---マップモデル読み込み---//
	objHandle = AssetManager::GetMesh("../SourceCode/Assets/Map/Map/map.mv1");			//モデル読み込み
	colModel = objHandle;																	//当たり判定モデルはモデルに
	MV1SetPosition(objHandle, objPos);														//位置セット
	MV1SetScale(objHandle, objScale);														//スケールセット

	MV1SetupCollInfo(colModel);																//当たり判定情報設定
}

// @brief Map更新処理 //

void Map::Update(float deltaTime)
{
}

// @brief Map描画処理 //

void Map::Draw()
{
	MV1DrawModel(objHandle);																//モデル描画
}