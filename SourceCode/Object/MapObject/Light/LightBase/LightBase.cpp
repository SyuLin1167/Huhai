#include "LightBase.h"

// �R���X�g���N�^ //

LightBase::LightBase()
    :ObjBase(ObjectTag::Light)
    , lightHandle(-1)
    , lightRange(70.0f)
    , lightAtten2(0.002f)
    , lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
    Load();
}

// �R���X�g���N�^ //

LightBase::LightBase(VECTOR pos)
    :ObjBase(ObjectTag::Light, pos)
    , lightHandle(-1)
    , lightRange(70.0f)
    , lightAtten2(0.002f)
    , lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
    Load();
}

// �f�X�g���N�^ //

LightBase::~LightBase()
{
    //���f���폜
    AssetManager::ReleaseMesh(objHandle);
}

// �ǂݍ��ݏ��� //

void LightBase::Load()
{
    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
}