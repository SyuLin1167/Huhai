#include "PlayScene.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include "../../Object/CharaObject/Camera/FpsCamera/FpsCamera.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Chair/Chair.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Light/LightingLight/LitLight.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../Object/CharaObject/Ghost/MoveGimmic/GhostWalkGim.h"
#include"../../Object/CharaObject/Man/Man.h"
#include "../../UI/Reamarks/Remarks.h"
#include"../PauseMenu/PauseMenu.h"
#include"../TitleScene/TitleScene.h"
#include"../EscapeScene/Escape.h"
#include"../SaveScene/SaveScene.h"

// �R���X�g���N�^ //

PlayScene::PlayScene()
    :SceneBase()
{
    //�J��������
    ObjManager::Entry(new FpsCamera);

    //�}�b�v����
    ObjManager::Entry(new Map(Map::MapTag::STAGE));

    //�Ƌ��
    ObjManager::Entry(new Furniture(Furniture::FurName::Stage));

    //�h�A����
    ObjManager::Entry(new Door("play"));
    ObjManager::Entry(new Door("play", "1"));
    ObjManager::Entry(new Door("play", "2"));

    //�C�X����
    ObjManager::Entry(new Chair);

    //�Ɩ�����
    ObjManager::Entry(new NomalLight("play"));
    ObjManager::Entry(new LitLight("play","1"));
    ObjManager::Entry(new LitLight("play", "2"));
    ObjManager::Entry(new NomalLight("play", "3"));
    ObjManager::Entry(new NomalLight("play", "4"));

    //�v���C���[����
    ObjManager::Entry(new Player);

    //�L�����M�~�b�N����
    ObjManager::Entry(new GhostWalkGim);
    ObjManager::Entry(new Man);

    //�䎌����
    ObjManager::Entry(new Remarks(TextType::Stage));
}

// �f�X�g���N�^ //

PlayScene::~PlayScene()
{
}

// �X�V���� //

SceneBase* PlayScene::UpdateScene(const float deltaTime)
{
    //�I�u�W�F�N�g�X�V
    ObjManager::Update(deltaTime);

    //�I�u�W�F�N�g�����蔻��
    ObjManager::Collision();

    //�L�����N�^�[�̃M�~�b�N���쓮���I�������
    ObjBase* man = ObjManager::GetFirstObj(ObjectTag::Man);
    if (!man)
    {
        //�Ǘ��N���X���̊m�ۂ����f�[�^���
        ObjManager::ReleaseAllObj();

        //�V�[�������̏�ʂɂ���
        SaveScene::Save(this);
        return new EscapeScene;
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

void PlayScene::DrawScene()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();
}