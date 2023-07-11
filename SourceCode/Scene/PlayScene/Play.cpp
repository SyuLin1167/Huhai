#include "Play.h"

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
#include"../TitleScene/Title.h"
#include"../EscapeScene/Escape.h"
#include"../Save/Save.h"

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
    ObjManager::Entry(new Door(VGet(22, 0, 0), VGet(0, 180, 0)));
    ObjManager::Entry(new Door(VGet(110, 0, 0), VGet(0, 0, 0)));
    ObjManager::Entry(new Door(VGet(0, 0, 66), VGet(0, 0, 0)));

    //�C�X����
    ObjManager::Entry(new Chair);

    //�Ɩ�����
    ObjManager::Entry(new NomalLight(VGet(-10, 33, 0)));
    ObjManager::Entry(new LitLight(VGet(65, 33, 0), 50.0f));
    ObjManager::Entry(new LitLight(VGet(121, 33, 25), 40.0f));

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

SceneBase* PlayScene::Update(float deltaTime)
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
        AssetManager::ReleaseAllAsset();
        ObjManager::ReleaseAllObj();

        //�V�[�������̏�ʂɂ���
        SaveScene::Save(this);
        return new EscapeScene;
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

void PlayScene::Draw()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();
}