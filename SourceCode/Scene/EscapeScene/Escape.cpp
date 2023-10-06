#include "Escape.h"

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
#include "../Ending/Ending.h"
#include"../TitleScene/TitleScene.h"
#include"../RoomScene/RoomScene.h"

// �R���X�g���N�^ //

EscapeScene::EscapeScene()
    :SceneBase()
{
    //�J��������
    ObjManager::Entry(new FpsCamera);

    //�}�b�v����
    ObjManager::Entry(new Map(Map::MapTag::ESCAPE));
    ObjManager::Entry(new Map(Map::MapTag::ESCAPEMAIN));
    ObjManager::Entry(new Map(Map::MapTag::GOAL));

    //�h�A����
    class Door* door = new Door("escape");
    ObjManager::Entry(door);
    door->MoveAnim(Door::AnimType::OPEN);
    ObjManager::Entry(new Door("escape", "1"));
    ObjManager::Entry(new Door("escape", "2"));

    //������
    for (int i = 0; i < TableNum; i++)
    {
        ObjManager::Entry(new Table(i));
    }

    //�Ɩ�����
    ObjManager::Entry(new BlinkingLight("escape"));
    ObjManager::Entry(new NomalLight("escape", "1"));
    ObjManager::Entry(new FlashLight);

    //�v���C���[����
    ObjManager::Entry(new Player);

    //�S�[�X�g����
    ObjManager::Entry(new Ghost);

    //�T�E���h����
    sound->AddSound("../Assets/Sound/GameOverSE.mp3", SoundTag::GameOver);
}

// �f�X�g���N�^ //

EscapeScene::~EscapeScene()
{
    //�����Ȃ�
}

// �X�V���� //

SceneBase* EscapeScene::UpdateScene(float deltaTime)
{
    //�I�u�W�F�N�g�X�V
    ObjManager::Update(deltaTime);

    //�I�u�W�F�N�g�����蔻��
    ObjManager::Collision();

    //�N���A������
    if (!ObjManager::GetObj(ObjectTag::Map, 2))
    {
        //�Ǘ��N���X���̊m�ۂ����f�[�^���
        ObjManager::ReleaseAllObj();

        //�V�[�������̏�ʂɂ���
        return new Ending;
    }
    //�Q�[���I�[�o�[������
    else if (!ObjManager::GetFirstObj(ObjectTag::Player)->IsVisible())
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
                ObjManager::ReleaseAllObj();

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
        ObjManager::ReleaseAllObj();

        //�V�[�����^�C�g���ɂ���
        return new TitleScene;
    }
    return this;
}

// �`�揈�� //

void EscapeScene::DrawScene()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();

    //�t�F�[�h����
    blendMode->Fade();
    DrawBox(bgX, bgY, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK_SCREEN_COLOR, true);
    blendMode->NoBlend();
}