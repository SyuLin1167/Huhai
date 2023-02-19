#include "MapFur.h"

// @brief MapFur�R���X�g���N�^�[ //

MapFur::MapFur()
	:ObjectBase(ObjectTag::Furniture)
{
	LoadModel();
}

// @brief MapFur�R���X�g���N�^�[(�ʒu�Z�b�g) //

MapFur::MapFur(VECTOR MapFurPos)
	:ObjectBase(ObjectTag::Furniture, MapFurPos)
{
	LoadModel();
}

// @brief MapFur�f�X�g���N�^�[ //

MapFur::~MapFur()
{
	AssetManager::ReleaseMesh(objHandle);					//���b�V���̍폜
}

// @brief MapFur���f���ǂݍ��ݏ��� //

void MapFur::LoadModel()
{
	//---�}�b�v���f���ǂݍ���---//
	objHandle = AssetManager::GetMesh("../Assets/Map/Furniture/MapFur.mv1");
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, VGet(0.11f,0.12f,0.11f));

	// �����蔻�胂�f���ǂݍ��݁��X�P�[�����O�������蔻����\�z
	colModel = AssetManager::GetMesh("../Assets/Map/Furniture/FurnitureCol.mv1");
	MV1SetScale(colModel, VGet(0.11f,0.12f,0.11f));
	MV1SetOpacityRate(colModel, 0.3f);

	// �\�����f���Ɠ����蔻�胂�f���̈ʒu�������
	MV1SetPosition(colModel, objPos);

	MV1SetupCollInfo(colModel);
}

// @brief MapFur�X�V���� //

void MapFur::Update(float deltaTime)
{
}

// @brief MapFur�`�揈�� //

void MapFur::Draw()
{
	MV1DrawModel(objHandle);
}