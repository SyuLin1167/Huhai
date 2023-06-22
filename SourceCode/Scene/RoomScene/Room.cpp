#include "Room.h"

#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include "../../Object/MapObject/Bed/Bed.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/CharaObject/Player/Player.h"
#include "../../UI/Reamarks/Remarks.h"
#include "../PlayScene/Play.h"
#include"../Save/Save.h"

// �R���X�g���N�^ //

Room::Room()
    :SceneBase()
    , roomBlend(nullptr)
{
    //�J��������
    ObjManager::Entry(new CameraFps);

    //�}�b�v����
    ObjManager::Entry(new Map(Map::MapTag::ROOM));

    //�Ƌ��
    ObjManager::Entry(new Furniture(Furniture::FurName::Room));

    //�x�b�h����
    ObjManager::Entry(new Bed);

    //�Ɩ�����
    ObjManager::Entry(new NomalLight(VGet(40, 32, 0)));

    //�v���C���[����
    ObjManager::Entry(new Player);

    //�䎌����
    ObjManager::Entry(new Remarks(TextType::Opening));

    //�u�����h���[�h����
    roomBlend = new BlendMode;
}

// �f�X�g���N�^ //

Room::~Room()
{
}

// �X�V���� //

SceneBase* Room::Update(float deltaTime)
{
    //�I�u�W�F�N�g�X�V
    ObjManager::Update(deltaTime);

    //�I�u�W�F�N�g�����蔻��
    ObjManager::Collision();

    //�A�N�V�����{�^���������ꂽ��
    ObjBase* action = ObjManager::GetFirstObj(ObjectTag::UI);
    if (!action->IsVisible())
    {
        //�t�F�[�h�A�E�g
        roomBlend->AddFade(deltaTime);

        //�V�[���ڍs���̉��o���I�������
        if (!roomBlend->NowFade())
        {
            //�Ǘ��N���X���̊m�ۂ����f�[�^���
            AssetManager::ReleaseAllAsset();
            ObjManager::ReleaseAllObj();

            //�V�[�������̏�ʂɂ���
            SaveScene::Save(this);
            return new Play;
        }
    }
    return this;
}

// �`�揈�� //

void Room::Draw()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();

    //�t�F�[�h����
    roomBlend->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    roomBlend->NoBlend();
}