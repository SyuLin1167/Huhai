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
#include"../PauseScene/PauseMenu/PauseMenu.h"
#include"../TitleScene/TitleScene.h"
#include"../EscapeScene/EscapeScene.h"
#include"../SaveScene/SaveScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayScene::PlayScene()
    :SceneBase()
{
    //�J��������
    ObjManager::AddObj(new FpsCamera);

    //�}�b�v����
    ObjManager::AddObj(new Map(Map::MapTag::STAGE));

    //�Ƌ��
    ObjManager::AddObj(new Furniture(Furniture::FurName::Stage));

    //�h�A����
    ObjManager::AddObj(new Door("play"));
    ObjManager::AddObj(new Door("play", "1"));
    ObjManager::AddObj(new Door("play", "2"));

    //�C�X����
    ObjManager::AddObj(new Chair);

    //�Ɩ�����
    ObjManager::AddObj(new NomalLight("play"));
    ObjManager::AddObj(new LitLight("play","1"));
    ObjManager::AddObj(new LitLight("play", "2"));
    ObjManager::AddObj(new NomalLight("play", "3"));
    ObjManager::AddObj(new NomalLight("play", "4"));

    //�v���C���[����
    ObjManager::AddObj(new Player);

    //�L�����M�~�b�N����
    ObjManager::AddObj(new GhostWalkGim);
    ObjManager::AddObj(new Man);

    //�䎌����
    ObjManager::AddObj(new Remarks(TextType::Stage));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene()
{
    //�Ǘ��N���X���̊m�ۂ����f�[�^���
    AssetManager::ReleaseAllAsset();
    ObjManager::DeleteAllObj();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�f���^�^�C��</param>
/// <returns>���̃t���[���̃V�[��</returns>
SceneBase* PlayScene::UpdateScene(const float deltaTime)
{
    //�I�u�W�F�N�g�X�V
    ObjManager::UpdateAllObj(deltaTime);

    //�I�u�W�F�N�g�����蔻��
    ObjManager::OnCollision();

    //�L�����N�^�[�̃M�~�b�N���쓮���I�������
    ObjBase* man = ObjManager::GetFirstObj(ObjTag::Man);
    if (!man)
    {
        //�Ǘ��N���X���̊m�ۂ����f�[�^���
        ObjManager::DeleteAllObj();

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
        ObjManager::DeleteAllObj();

        //�V�[�����^�C�g���ɂ���

        return new TitleScene;
    }

    return this;
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayScene::DrawScene()
{
    //�I�u�W�F�N�g�`��
    ObjManager::DrawAllObj();
}