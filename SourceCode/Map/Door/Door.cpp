#include "Door.h"

// @brief Doorコンストラクター

Door::Door()
	:ObjectBase(ObjectTag::Door)
	,doorAnim(nullptr)
{
	Load();
}

// @brief Doorコンストラクター

Door::Door(VECTOR doorPos)
	:ObjectBase(ObjectTag::Door,doorPos)
	,doorAnim(nullptr)
{
	Load();
}

// @brief Doorデストラクター

Door::~Door()
{
	AssetManager::ReleaseMesh(objHandle);
}

// @brief Door読み込み処理 //

void Door::Load()
{
	objHandle = AssetManager::GetMesh("../SourceCode/Assets/Map/Door/Door.mv1");		//モデル読み込み
	colModel = objHandle;
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, objScale);
	ColUpdate();

	doorAnim = new Animation(objHandle);
	doorAnim->AddAnimation("../SourceCode/Assets/Map/Door/DoorOpen.mv1");
	doorAnim->AddAnimation("../SourceCode/Assets/Map/Door/DoorClose.mv1");
}

// @brief Door更新処理 //

void Door::Update(float deltaTime)
{
}

// @brief Door描画処理 //

void Door::Draw()
{
	MV1DrawModel(objHandle);						//モデル描画
}