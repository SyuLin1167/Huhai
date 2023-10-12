#include "EscapeScene.h"

#include "../../Object/ObjectManager/ObjManager.h"
#include "../../Asset/AssetManager/AssetManager.h"
#include "../../Object/CharaObject/Camera/FpsCamera/FpsCamera.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Table/Table.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/BlinkingLight/BlinkingLight.h"
#include "../../Object/MapObject/Light/FlashLight/FlashLight.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/CharaObject/Ghost/Ghost.h"
#include"../PauseMenu/PauseMenu.h"
#include "../EndingScene/EndingScene.h"
#include"../TitleScene/TitleScene.h"
#include"../RoomScene/RoomScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EscapeScene::EscapeScene()
    :SceneBase()
{
    //�J��������
    ObjManager::AddObj(new FpsCamera);

    //�}�b�v����
    ObjManager::AddObj(new Map(Map::MapTag::ESCAPE));
    ObjManager::AddObj(new Map(Map::MapTag::ESCAPEMAIN));
    ObjManager::AddObj(new Map(Map::MapTag::GOAL));

    //�h�A����
    class Door* door = new Door("escape");
    ObjManager::AddObj(door);
    door->MoveAnim(Door::AnimType::OPEN);
    ObjManager::AddObj(new Door("escape", "1"));
    ObjManager::AddObj(new Door("escape", "2"));

    //������
    for (int i = 0; i < TableNum; i++)
    {
        ObjManager::AddObj(new Table(i));
    }

    //�Ɩ�����
    ObjManager::AddObj(new BlinkingLight("escape"));
    ObjManager::AddObj(new NomalLight("escape", "1"));
    ObjManager::AddObj(new FlashLight);

    //�v���C���[����
    ObjManager::AddObj(new Player);

    //�S�[�X�g����
    ObjManager::AddObj(new Ghost);

    //�T�E���h����
    sound->AddSound("../Assets/Sound/GameOverSE.mp3", SoundTag::GameOver);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EscapeScene::~EscapeScene()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
/// <returns></returns>
SceneBase* EscapeScene::UpdateScene(float deltaTime)
{
    //�I�u�W�F�N�g�X�V
    ObjManager::UpdateAllObj(deltaTime);

    //�I�u�W�F�N�g�����蔻��
    ObjManager::OnCollision();

    //�N���A������
    if (!ObjManager::GetObj(ObjTag::Map, 2))
    {
        //�Ǘ��N���X���̊m�ۂ����f�[�^���
        ObjManager::DeleteAllObj();

        //�V�[�������̏�ʂɂ���
        return new EndingScene;
    }
    //�Q�[���I�[�o�[������
    else if (!ObjManager::GetFirstObj(ObjTag::Player)->IsVisible())
    {
        //�t�F�[�h�A�E�g
        blendMode->AddFade(deltaTime);

        //�V�[���ڍs���̉��o���I�������
        sound->StartSoundOnce(SoundTag::GameOver, DX_PLAYTYPE_BACK);
        if (!sound->IsPlaying(SoundTag::GameOver))
        {
            if (!blendMode->NowFade())
            {
                //�Ǘ��N���X���̊m�ۂ����f�[�^���
                AssetManager::ReleaseAllAsset();
                ObjManager::DeleteAllObj();

                //�V�[�������̏�ʂɂ���
                return new TitleScene;
            }
        }
    }

    //�^�C�g���ֈړ�����ꍇ
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
void EscapeScene::DrawScene()
{
    //�I�u�W�F�N�g�`��
    ObjManager::DrawAllObj();

    //�t�F�[�h����
    blendMode->Fade();
    DrawBox(bgX, bgY, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK_SCREEN_COLOR, true);
    blendMode->NoBlend();
}