#include "Room.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/Wipe.h"
#include "../../Asset/Sound/Sound.h"
#include "../../Object/CharaObject/Camera/FpsCamera/FpsCamera.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../../Object/MapObject/Bed/Bed.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../UI/Reamarks/Remarks.h"
#include "../PlayScene/Play.h"
#include"../Save/Save.h"

// �R���X�g���N�^ //

RoomScene::RoomScene()
    :SceneBase()
    , roomBlend(nullptr)
{
    //�T�E���h����
    roomSound = new Sound;
    roomSound->AddSound("../Assets/Sound/InDoorSE.mp3", SoundTag::InDoor);
    roomSound->StartSound(SoundTag::InDoor, DX_PLAYTYPE_LOOP);

    //�J��������
    ObjManager::Entry(new FpsCamera);

    //�}�b�v����
    ObjManager::Entry(new Map(Map::MapTag::ROOM));

    //�Ƌ��
    ObjManager::Entry(new Furniture(Furniture::FurName::Room));

    //�x�b�h����
    ObjManager::Entry(new Bed);

    //�Ɩ�����
    ObjManager::Entry(new NomalLight(VGet(40, 33, 0)));

    //�v���C���[����
    ObjManager::Entry(new Player);

    //�䎌����
    ObjManager::Entry(new Remarks(TextType::Opening));

    //�u�����h���[�h����
    roomBlend = new Wipe;

}

// �f�X�g���N�^ //

RoomScene::~RoomScene()
{
}

// �X�V���� //

SceneBase* RoomScene::Update(float deltaTime)
{
    //�I�u�W�F�N�g�X�V
    ObjManager::Update(deltaTime);

    //�I�u�W�F�N�g�����蔻��
    ObjManager::Collision();
    //�A�N�V�����{�^���������ꂽ��
    ObjBase* action = ObjManager::GetFirstObj(ObjectTag::UI);

    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        SaveScene::Save(this);
    }

    if (!action->IsVisible())
    {
        //�t�F�[�h�A�E�g
        SetDrawMode(DX_DRAWMODE_BILINEAR);
        roomBlend->AddFade(deltaTime);

        //�V�[���ڍs���̉��o���I�������
        if (!roomBlend->NowFade())
        {
            //�Ǘ��N���X���̊m�ۂ����f�[�^���
            AssetManager::ReleaseAllAsset();
            ObjManager::ReleaseAllObj();

            //�V�[�������̏�ʂɂ���
            return new PlayScene;
        }
    }
    return this;
}

// �`�揈�� //

void RoomScene::Draw()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();

    //�t�F�[�h����
    roomBlend->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    roomBlend->NoBlend();
}