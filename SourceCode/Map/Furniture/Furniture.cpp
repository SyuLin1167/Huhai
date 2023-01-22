#include "Furniture.h"

// @brief Furniture�R���X�g���N�^�[ //

Furniture::Furniture()
	:ObjectBase(ObjectTag::Furniture)
{
	Load();
}

// @brief Furniture�R���X�g���N�^�[(�ʒu�Z�b�g) //

Furniture::Furniture(VECTOR FurniturePos)
	:ObjectBase(ObjectTag::Furniture, FurniturePos)
{
	Load();
}

// @brief Furniture�f�X�g���N�^�[ //

Furniture::~Furniture()
{
	AssetManager::ReleaseMesh(objHandle);					//���b�V���̍폜
}

// @brief Furniture�ǂݍ��ݏ��� //

void Furniture::Load()
{
	//---�}�b�v���f���ǂݍ���---//
	objHandle = AssetManager::GetMesh("../SourceCode/Assets/Map/Furniture/untitled.mv1");
	colModel = objHandle;
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, objScale);

	MV1SetupCollInfo(colModel);
}

// @brief Furniture�X�V���� //

void Furniture::Update(float deltaTime)
{
}

// @brief Furniture�`�揈�� //

void Furniture::Draw()
{
	MV1DrawModel(objHandle);
}