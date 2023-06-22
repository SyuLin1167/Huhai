#include "Map.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Model/Model.h"
#include"../../../Asset/Sound/Sound.h"

// �R���X�g���N�^ //

Map::Map(int maptag)
    :ObjBase(ObjectTag::Map)
    , mapModel(nullptr)
    , mapSound(nullptr)
    , mapTag(maptag)
{
    LoadModel();
}

// �f�X�g���N�^ //

Map::~Map()
{
    //���b�V���폜
    AssetManager::ReleaseMesh(objHandle);
}

        // �ǂݍ��ݏ��� //

void Map::LoadModel()
{
    //���f���ݒ�
    mapModel = new Model;
    mapModel->AddModel("../Assets/Map/Stage/Title.mv1");
    mapModel->AddModel("../Assets/Map/Room/Room.mv1");
    mapModel->AddModel("../Assets/Map/Stage/StageDay1.mv1");
    mapModel->AddModel("../Assets/Map/Stage/Escape.mv1");
    mapModel->AddModel("../Assets/Map/Stage/EscapeMain.mv1");
    mapModel->AddModel("../Assets/Map/Stage/GoalRoom.mv1");
    objHandle = mapModel->GetModel(mapTag);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));

    //�����蔻��ݒ�
    colModel = objHandle;
    MV1SetupCollInfo(colModel);

    //�T�E���h�ݒ�
    mapSound = new Sound;
    mapSound->AddSound("../Assets/Sound/InDoorSE.mp3", SoundTag::InDoor, 150);
    mapSound->StartSound(SoundTag::InDoor, DX_PLAYTYPE_LOOP);
}

// �X�V���� //

void Map::Update(float deltaTime)
{
    //�S�[���n�_�̏���
    if (mapTag == GOAL)
    {
        //�S�[���ɋ߂Â�����\�����Ă��ǂ蒅�����玀�S�ɂ���
        MV1SetMaterialEmiColor(objHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
        if (ObjManager::GetFirstObj(ObjectTag::Player)->GetPos().x > 730)
        {
            isVisible = true;
            if (ObjManager::GetFirstObj(ObjectTag::Player)->GetPos().x > 770)
            {
                isAlive = false;
            }
        }
        else
        {
            isVisible = false;
        }
    }

    //�����蔻��X�V
    ColUpdate();
}

// �`�揈�� //

void Map::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}