#include "RoomScene.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include "../../Object/CharaObject/Camera/FpsCamera/FpsCamera.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../../Object/MapObject/Bed/Bed.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../UI/Reamarks/Remarks.h"
#include"../PauseMenu/PauseMenu.h"
#include"../TitleScene/TitleScene.h"
#include "../PlayScene/Play.h"
#include"../SaveScene/SaveScene.h"

// �R���X�g���N�^ //

RoomScene::RoomScene()
    :SceneBase()
{
    //�T�E���h����
    sound->AddSound("../Assets/Sound/InDoorSE.mp3", SoundTag::InDoor);
    sound->StartSound(SoundTag::InDoor, DX_PLAYTYPE_LOOP);

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
}

// �f�X�g���N�^ //

RoomScene::~RoomScene()
{
    //�����Ȃ�
}

// �X�V���� //

SceneBase* RoomScene::UpdateScene(const float deltaTime)
{
    //�I�u�W�F�N�g�X�V
    ObjManager::Update(deltaTime);

    //�I�u�W�F�N�g�����蔻��
    ObjManager::Collision();
    //�A�N�V�����{�^���������ꂽ��
    ObjBase* action = ObjManager::GetFirstObj(ObjectTag::UI);
    if (action)
    {
        if (!action->IsVisible())
        {
            //�t�F�[�h�A�E�g
            blendMode->AddFade(deltaTime);

            //�V�[���ڍs���̉��o���I�������
            if (!blendMode->NowFade())
            {

                //�Ǘ��N���X���̊m�ۂ����f�[�^���
                ObjManager::ReleaseAllObj();

                //�V�[�������̏�ʂɂ���
                return new PlayScene;
            }
        }
    }

    //�^�C�g���ֈړ�
    if (PauseMenu::BackToTitle())
    {
        PauseMenu::ResetTitleButton();

        //�Ǘ��N���X���̊m�ۂ����f�[�^���
        AssetManager::ReleaseAllAsset();
        ObjManager::ReleaseAllObj();

        //�V�[�����^�C�g���ɂ���

        return new TitleScene;
    }
    return this;
}

// �`�揈�� //

void RoomScene::DrawScene()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();

    //�t�F�[�h����
    blendMode->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    blendMode->NoBlend();
}