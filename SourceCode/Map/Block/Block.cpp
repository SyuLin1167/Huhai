#include "Block.h"

// @brief Block�R���X�g���N�^�[ //

Block::Block()
	:ObjectBase(ObjectTag::Map)
{
	Load();
}

// @brief Block�R���X�g���N�^�[ //

Block::Block(VECTOR blkPos)
	:ObjectBase(ObjectTag::Map,blkPos)
{
	Load();
}

// @brief Block�f�X�g���N�^�[ //

Block::~Block()
{
	AssetManager::ReleaseMesh(objHandle);
}

// @brief Block�ǂݍ��ݏ��� //

void Block::Load()
{
	objHandle = AssetManager::GetMesh("../SourceCode/Assets/Map/Block/block.mv1");		//���f���ǂݍ���
	colModel = objHandle;
	MV1SetPosition(objHandle, objPos);
	MV1SetScale(objHandle, objScale);
	ColUpdate();
}

// @brief Block�X�V���� //

void Block::Update(float deltaTime)
{
}

// @brief Block�`�揈�� //

void Block::Draw()
{
	MV1SetPosition(objHandle, objPos);			//�|�W�V�����Z�b�g
	MV1DrawModel(objHandle);						//���f���`��
}