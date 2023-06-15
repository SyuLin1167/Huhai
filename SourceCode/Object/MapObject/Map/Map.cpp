#include "Map.h"
#include"../../../Asset/Sound/Sound.h"

        // �R���X�g���N�^ //

Map::Map(int maptag)
    :ObjectBase(ObjectTag::Map)
    , mapModel(nullptr)
    , mapSound(nullptr)
    , mapTag(maptag)
{
    LoadModel();
}

        // �f�X�g���N�^ //

Map::~Map()
{
    AssetManager::ReleaseMesh(objHandle);					//���b�V���̍폜
}

        // �ǂݍ��ݏ��� //

void Map::LoadModel()
{
    //���f���ǂݍ���
    mapModel = new Model;
    mapModel->AddModel("../Assets/Map/Stage/Title.mv1");
    mapModel->AddModel("../Assets/Map/Room/Room.mv1");
    mapModel->AddModel("../Assets/Map/Stage/StageDay1.mv1");
    mapModel->AddModel("../Assets/Map/Stage/Escape.mv1");
    mapModel->AddModel("../Assets/Map/Stage/EscapeMain.mv1");
    mapModel->AddModel("../Assets/Map/Stage/GoalRoom.mv1");
    objHandle = mapModel->SetModel(mapTag);

    colModel = objHandle;																	//�����蔻�胂�f���̓��f����
    MV1SetPosition(objHandle, objPos);														//�ʒu�Z�b�g
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));										//�X�P�[���Z�b�g

    MV1SetupCollInfo(colModel);																//�����蔻����ݒ�

    mapSound = new Sound;
    mapSound->AddSound("../Assets/Sound/InDoorSE.mp3", SoundTag::InDoor, 150);
    mapSound->StartSound(SoundTag::InDoor, DX_PLAYTYPE_LOOP);
}

        // �X�V���� //

void Map::Update(float deltaTime)
{
    if (mapTag == GOAL)
    {
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
}

        // �`�揈�� //

void Map::Draw()
{
    MV1DrawModel(objHandle);
}