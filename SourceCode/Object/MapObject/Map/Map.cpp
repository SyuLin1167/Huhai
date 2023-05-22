#include "Map.h"

// @brief Mapコンストラクター //

Map::Map(int maptag)
	:ObjectBase(ObjectTag::Map)
	,mapModel(nullptr)
{
	LoadModel(maptag);
}

// @brief Mapデストラクター //

Map::~Map()
{
	AssetManager::ReleaseMesh(objHandle);					//メッシュの削除
}

// @brief Map読み込み処理 //

void Map::LoadModel (int maptag)
{
	//---マップモデル読み込み---//
	mapModel = new Model;
	mapModel->AddModel("../Assets/Map/Stage/Huhai.mv1");
	mapModel->AddModel("../Assets/Map/Room/Room.mv1");						//モデル読み込み
	mapModel->AddModel("../Assets/Map/Stage/StageDay1.mv1");						//モデル読み込み
	mapModel->AddModel("../Assets/Map/Stage/Escape.mv1");
	mapModel->AddModel("../Assets/Map/Stage/EscapeMain.mv1");
	objHandle = mapModel->SetModel(maptag);

	colModel = objHandle;																	//当たり判定モデルはモデルに
	MV1SetPosition(objHandle, objPos);														//位置セット
	MV1SetScale(objHandle, VGet(0.11f,0.12f,0.11f));										//スケールセット

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