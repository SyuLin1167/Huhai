#include "LightBase.h"

// @brief LightBase�R���X�g���N�^ //

LightBase::LightBase()
	:ObjectBase(ObjectTag::Light)
	, lightHandle(-1)
	, lightRange(70.0f)
	, lightAtten2(0.002f)
	, lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
	Load();
}

// @brief LightBase�R���X�g���N�^ //

LightBase::LightBase(VECTOR lightPos)
	:ObjectBase(ObjectTag::Light, lightPos)
	, lightHandle(-1)
	, lightRange(70.0f)
	, lightAtten2(0.002f)
	, lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
	Load();
}

// @brief LightBase�f�X�g���N�^ //

LightBase::~LightBase()
{
	AssetManager::ReleaseMesh(objHandle);
}

// @brief LightBase�ǂݍ��ݏ��� //

void LightBase::Load()
{
	//---���f���ǂݍ���---//
	objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");						 //���f���ǂݍ���

	MV1SetPosition(objHandle, objPos);                                                      //���f���̍��W�ݒ�
	MV1SetScale(objHandle, objScale);                                                       //���f���̃T�C�Y�ݒ�
}