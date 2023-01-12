#include "Map.h"

// @brief Map�R���X�g���N�^�[ //

Map::Map()
	:ObjectBase(ObjectTag::Map)
{
	Load();
}

// @brief Map�R���X�g���N�^�[(�ʒu�Z�b�g) //

Map::Map(VECTOR mapPos)
	:ObjectBase(ObjectTag::Map,mapPos)
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
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, objScale);
	ColUpdate();

}

// @brief Map�X�V���� //

void Map::Update(float deltaTime)
{
}

// @brief Map�`�揈�� //

void Map::Draw()
{
	MV1DrawModel(objHandle);
}