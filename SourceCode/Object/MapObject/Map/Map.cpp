#include "Map.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Sound/Sound.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="maptag"></param>
Map::Map(MapTag maptag)
    :ObjBase(ObjTag::Map)
    , mapSound(new Sound)
    , mapTag(maptag)
{
    //���f���ݒ�
    objHandle = AssetManager::GetMesh(mapFile[mapTag]);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));

    //�����蔻��ݒ�
    colModel = AssetManager::GetMesh(mapColFile[mapTag]);
    MV1SetPosition(colModel, objPos);
    MV1SetScale(colModel, VGet(0.11f, 0.12f, 0.11f));

    //�T�E���h�ݒ�
    mapSound->AddSound("../Assets/Sound/InDoorSE.mp3", SoundTag::InDoor);
    mapSound->StartSound(SoundTag::InDoor, DX_PLAYTYPE_LOOP);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�f���^�^�C��</param>
void Map::Update(const float deltaTime)
{
    //�S�[���n�_�̏���
    if (mapTag == GOAL)
    {
        //�S�[���ɋ߂Â�����\�����Ă��ǂ蒅�����玀�S�ɂ���
        MV1SetMaterialEmiColor(objHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
        if (ObjManager::GetFirstObj(ObjTag::Player)->GetPos().x > 730)
        {
            isVisible = true;
            if (ObjManager::GetFirstObj(ObjTag::Player)->GetPos().x > 770)
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

/// <summary>
/// �`�揈��
/// </summary>
void Map::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}