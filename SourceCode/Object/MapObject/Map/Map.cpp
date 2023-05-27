#include "Map.h"

// @brief Map�R���X�g���N�^�[ //

Map::Map(int maptag)
	:ObjectBase(ObjectTag::Map)
	,mapModel(nullptr)
	,mapTag(maptag)
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
	mapModel = new Model;
	mapModel->AddModel("../Assets/Map/Stage/Huhai.mv1");
	mapModel->AddModel("../Assets/Map/Room/Room.mv1");						//���f���ǂݍ���
	mapModel->AddModel("../Assets/Map/Stage/StageDay1.mv1");						//���f���ǂݍ���
	mapModel->AddModel("../Assets/Map/Stage/Escape.mv1");
	mapModel->AddModel("../Assets/Map/Stage/EscapeMain.mv1");
	mapModel->AddModel("../Assets/Map/Stage/GoalRoom.mv1");
	objHandle = mapModel->SetModel(mapTag);

	colModel = objHandle;																	//�����蔻�胂�f���̓��f����
	MV1SetPosition(objHandle, objPos);														//�ʒu�Z�b�g
	MV1SetScale(objHandle, VGet(0.11f,0.12f,0.11f));										//�X�P�[���Z�b�g

	MV1SetupCollInfo(colModel);																//�����蔻����ݒ�
}

// @brief Map�X�V���� //

void Map::Update(float deltaTime)
{
	if (mapTag == GOAL)
	{
		MV1SetMaterialEmiColor(objHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

// @brief Map�`�揈�� //

void Map::Draw()
{
	MV1DrawModel(objHandle);																//���f���`��
}