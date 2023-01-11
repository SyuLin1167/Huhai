#include "Map.h"

// @brief Map�R���X�g���N�^�[ //

Map::Map()
	:ObjectBase(ObjectTag::Map)
{
	Load();
}

// @brief Map�R���X�g���N�^�[(�ʒu�Z�b�g) //

Map::Map(VECTOR pos)
	:ObjectBase(ObjectTag::Map,pos)
{
	Load();
}

// @brief Map�f�X�g���N�^�[ //

Map::~Map()
{
	AssetManager::ReleaseMesh(objHandle);					//���b�V���̍폜
}

// @brief Map�ǂݍ��ݏ��� //

void Map::Load()
{
	//---�}�b�v���f���ǂݍ���---//
	objHandle = AssetManager::GetMesh("../SourceCode/Assets/Map/Map/HuhaiMap.mv1");
	colModel = objHandle;
	objPos = { 0,-5,0 };
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, objScale);
	ColUpdate();

	//---�����蔻�胂�f���ǂݍ���---//
	//colModel = AssetManager::GetMesh("../SourceCode/Assets/Map/Map/HitMesh2rot.mv1");
	//MV1SetScale(colModel, objScale);
	//MV1SetOpacityRate(colModel, 0.3f);					//���f���̕s�����x�ݒ�
	//MV1SetPosition(colModel, objPos + VGet(-5, 20, -5));
	//MV1SetupCollInfo(colModel);
}

// @brief Map�X�V���� //

void Map::Update(float deltaTime)
{
}

// @brief Map�`�揈�� //

void Map::Draw()
{
	MV1DrawModel(objHandle);
	ColDraw();
}