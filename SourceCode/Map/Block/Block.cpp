#include "Block.h"

// @brief Blockコンストラクター //

Block::Block()
	:ObjectBase(ObjectTag::Map)
{
	Load();
}

// @brief Blockコンストラクター //

Block::Block(VECTOR blkPos)
	:ObjectBase(ObjectTag::Map,blkPos)
{
	Load();
}

// @brief Blockデストラクター //

Block::~Block()
{
	AssetManager::ReleaseMesh(objHandle);
}

// @brief Block読み込み処理 //

void Block::Load()
{
	objHandle = AssetManager::GetMesh("../SourceCode/Assets/Map/Block/block.mv1");		//モデル読み込み
	colModel = objHandle;
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, objScale);
	ColUpdate();
}

// @brief Block更新処理 //

void Block::Update(float deltaTime)
{
}

// @brief Block描画処理 //

void Block::Draw()
{
	MV1SetPosition(objHandle, objPos);			//ポジションセット
	MV1DrawModel(objHandle);						//モデル描画
}