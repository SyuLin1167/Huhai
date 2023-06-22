#include "Play.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
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
#include"../EscapeScene/Escape.h"
#include"../Save/Save.h"

    // @brief PlayScene�R���X�g���N�^ //

Play::Play()
    :SceneBase()
{
    //�J��������
    ObjManager::Entry(new CameraFps);

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
    ObjManager::Entry(new NomalLight(VGet(-10, 32, 0)));
    ObjManager::Entry(new LitLight(VGet(65, 32, 0), 50.0f));
    ObjManager::Entry(new LitLight(VGet(121, 32, 25), 40.0f));

    //�v���C���[����
    ObjManager::Entry(new Player);

    //�L�����M�~�b�N����
    ObjManager::Entry(new GhostWalkGim);
    ObjManager::Entry(new Man);

    //�䎌����
    ObjManager::Entry(new Remarks(TextType::Stage));
}

// �f�X�g���N�^ //

Play::~Play()
{
}

// �X�V���� //

SceneBase* Play::Update(float deltaTime)
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

    return this;
}

// �`�揈�� //

void Play::Draw()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();
}