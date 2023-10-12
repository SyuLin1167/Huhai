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
#include "../PlayScene/PlayScene.h"
#include"../SaveScene/SaveScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
RoomScene::RoomScene()
    :SceneBase()
{
    //�T�E���h����
    sound->AddSound("../Assets/Sound/InDoorSE.mp3", SoundTag::InDoor);
    sound->StartSound(SoundTag::InDoor, DX_PLAYTYPE_LOOP);

    //�J��������
    ObjManager::AddObj(new FpsCamera);

    //�}�b�v����
    ObjManager::AddObj(new Map(Map::MapTag::ROOM));

    //�Ƌ��
    ObjManager::AddObj(new Furniture(Furniture::FurName::Room));

    //�x�b�h����
    ObjManager::AddObj(new Bed);

    //�Ɩ�����
    ObjManager::AddObj(new NomalLight("room"));

    //�v���C���[����
    ObjManager::AddObj(new Player);

    //�䎌����
    ObjManager::AddObj(new Remarks(TextType::Opening));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RoomScene::~RoomScene()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
/// <returns>���t���[���̃V�[��</returns>
SceneBase* RoomScene::UpdateScene(const float deltaTime)
{
    //�I�u�W�F�N�g�X�V
    ObjManager::UpdateAllObj(deltaTime);

    //�I�u�W�F�N�g�����蔻��
    ObjManager::OnCollision();

    //�A�N�V�����{�^���������ꂽ��
    ObjBase* action = ObjManager::GetFirstObj(ObjTag::UI);
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
                ObjManager::DeleteAllObj();

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
        ObjManager::DeleteAllObj();

        //�V�[�����^�C�g���ɂ���

        return new TitleScene;
    }
    return this;
}

/// <summary>
/// �`�揈��
/// </summary>
void RoomScene::DrawScene()
{
    //�I�u�W�F�N�g�`��
    ObjManager::DrawAllObj();

    //�t�F�[�h����
    blendMode->Fade();
    DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK_SCREEN_COLOR, true);
    blendMode->NoBlend();
}