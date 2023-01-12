#include "Door.h"

// @brief Door�R���X�g���N�^�[

Door::Door()
	:ObjectBase(ObjectTag::Door)
	,doorAnim(nullptr)
{
	Load();
}

// @brief Door�R���X�g���N�^�[

Door::Door(VECTOR doorPos)
	:ObjectBase(ObjectTag::Door,doorPos)
	,doorAnim(nullptr)
{
	Load();
}

// @brief Door�f�X�g���N�^�[

Door::~Door()
{
	AssetManager::ReleaseMesh(objHandle);
}

// @brief Door�ǂݍ��ݏ��� //

void Door::Load()
{
	objHandle = AssetManager::GetMesh("../SourceCode/Assets/Map/Door/Door.mv1");		//���f���ǂݍ���
	colModel = objHandle;
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, objScale);
	ColUpdate();

	doorAnim = new Animation(objHandle);
	doorAnim->AddAnimation("../SourceCode/Assets/Map/Door/DoorOpen.mv1");
	doorAnim->AddAnimation("../SourceCode/Assets/Map/Door/DoorClose.mv1");
}

// @brief Door�X�V���� //

void Door::Update(float deltaTime)
{
}

// @brief Door�`�揈�� //

void Door::Draw()
{
	MV1DrawModel(objHandle);						//���f���`��
}