#include "Furniture.h"

// @brief Furnitureコンストラクター //

Furniture::Furniture()
	:ObjectBase(ObjectTag::Furniture)
{
	Load();
}

// @brief Furnitureコンストラクター(位置セット) //

Furniture::Furniture(VECTOR FurniturePos)
	:ObjectBase(ObjectTag::Furniture, FurniturePos)
{
	Load();
}

// @brief Furnitureデストラクター //

Furniture::~Furniture()
{
	AssetManager::ReleaseMesh(objHandle);					//メッシュの削除
}

// @brief Furniture読み込み処理 //

void Furniture::Load()
{
	//---マップモデル読み込み---//
	objHandle = AssetManager::GetMesh("../SourceCode/Assets/Map/Furniture/untitled.mv1");
	colModel = objHandle;
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, objScale);

	MV1SetupCollInfo(colModel);
}

// @brief Furniture更新処理 //

void Furniture::Update(float deltaTime)
{
}

// @brief Furniture描画処理 //

void Furniture::Draw()
{
	MV1DrawModel(objHandle);
}