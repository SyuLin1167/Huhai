#include "Map.h"

// @brief Mapコンストラクター //

Map::Map()
	:ObjectBase(ObjectTag::Map)
{
	Load();
}

// @brief Mapコンストラクター(位置セット) //

Map::Map(VECTOR pos)
	:ObjectBase(ObjectTag::Map,pos)
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
	objPos = { 0,-5,0 };
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, objScale);
	ColUpdate();

	//---当たり判定モデル読み込み---//
	//colModel = AssetManager::GetMesh("../SourceCode/Assets/Map/Map/HitMesh2rot.mv1");
	//MV1SetScale(colModel, objScale);
	//MV1SetOpacityRate(colModel, 0.3f);					//モデルの不透明度設定
	//MV1SetPosition(colModel, objPos + VGet(-5, 20, -5));
	//MV1SetupCollInfo(colModel);
}

// @brief Map更新処理 //

void Map::Update(float deltaTime)
{
}

// @brief Map描画処理 //

void Map::Draw()
{
	MV1DrawModel(objHandle);
	ColDraw();
}