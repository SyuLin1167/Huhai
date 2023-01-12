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
	objHandle = AssetManager::GetMesh("../SourceCode/Assets/Map/Map/HuhaiMap.mv1");
	colModel = objHandle;
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, objScale);
	ColUpdate();

}

// @brief Map更新処理 //

void Map::Update(float deltaTime)
{
}

// @brief Map描画処理 //

void Map::Draw()
{
	MV1DrawModel(objHandle);
}