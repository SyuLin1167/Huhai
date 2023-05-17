#include "Map.h"

// @brief Map�R���X�g���N�^�[ //

Map::Map()
	:ObjectBase(ObjectTag::Map)
{
	LoadModel();
}

// @brief Map�R���X�g���N�^�[(�ʒu�Z�b�g) //

Map::Map(VECTOR mapPos)
	:ObjectBase(ObjectTag::Map,mapPos)
{
	LoadModel();
}

// @brief Map�f�X�g���N�^�[ //

Map::~Map()
{
	AssetManager::ReleaseMesh(objHandle);					//���b�V���̍폜
}

// @brief Map�ǂݍ��ݏ��� //

void Map::LoadModel ()
{
	//---�}�b�v���f���ǂݍ���---//
	objHandle = AssetManager::GetMesh("../Assets/Map/Map/map.mv1");			//���f���ǂݍ���
	colModel = objHandle;																	//�����蔻�胂�f���̓��f����
	MV1SetPosition(objHandle, objPos);														//�ʒu�Z�b�g
	MV1SetScale(objHandle, VGet(0.11f,0.12f,0.11f));														//�X�P�[���Z�b�g

	MV1SetupCollInfo(colModel);																//�����蔻����ݒ�
}

// @brief Map�X�V���� //

void Map::Update(float deltaTime)
{
}

// @brief Map�`�揈�� //

void Map::Draw()
{
	MV1DrawModel(objHandle);																//���f���`��
}