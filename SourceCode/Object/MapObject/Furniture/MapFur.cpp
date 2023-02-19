#include "MapFur.h"

// @brief MapFurコンストラクター //

MapFur::MapFur()
	:ObjectBase(ObjectTag::Furniture)
{
	LoadModel();
}

// @brief MapFurコンストラクター(位置セット) //

MapFur::MapFur(VECTOR MapFurPos)
	:ObjectBase(ObjectTag::Furniture, MapFurPos)
{
	LoadModel();
}

// @brief MapFurデストラクター //

MapFur::~MapFur()
{
	AssetManager::ReleaseMesh(objHandle);					//メッシュの削除
}

// @brief MapFurモデル読み込み処理 //

void MapFur::LoadModel()
{
	//---マップモデル読み込み---//
	objHandle = AssetManager::GetMesh("../Assets/Map/Furniture/MapFur.mv1");
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, VGet(0.11f,0.12f,0.11f));

	// 当たり判定モデル読み込み＆スケーリング＆当たり判定情報構築
	colModel = AssetManager::GetMesh("../Assets/Map/Furniture/FurnitureCol.mv1");
	MV1SetScale(colModel, VGet(0.11f,0.12f,0.11f));
	MV1SetOpacityRate(colModel, 0.3f);

	// 表示モデルと当たり判定モデルの位置を微調整
	MV1SetPosition(colModel, objPos);

	MV1SetupCollInfo(colModel);
}

// @brief MapFur更新処理 //

void MapFur::Update(float deltaTime)
{
}

// @brief MapFur描画処理 //

void MapFur::Draw()
{
	MV1DrawModel(objHandle);
}