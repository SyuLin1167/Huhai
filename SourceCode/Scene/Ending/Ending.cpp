#include "Ending.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Object/CharaObject/Camera/FixedCamera/FixedCamera.h"
#include"../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include"../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../UI/Reamarks/Remarks.h"
#include "../TitleScene/TitleScene.h"
#include"../SaveScene/SaveScene.h"

// �R���X�g���N�^ //

Ending::Ending()
    :SceneBase()
{
    //�J��������
    ObjManager::Entry(new FixedCamera);

    //�}�b�v����
    ObjManager::Entry(new Map(Map::MapTag::ROOM));
    
    //�Ƌ��
    ObjManager::Entry(new Furniture(Furniture::FurName::Room));

    //�Ɩ�����
    ObjManager::Entry(new NomalLight(VGet(40, 33, 0)));

    //�䎌����
    ObjManager::Entry(new Remarks(TextType::GameClear));
}

// �f�X�g���N�^ //

Ending::~Ending()
{
}

// �X�V���� //

SceneBase* Ending::UpdateScene(const float deltaTime)
{
    //�I�u�W�F�N�g�X�V
    ObjManager::Update(deltaTime);

    //�J�����ݒ�
    ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
    camera->SetPos(VGet(50, 10, 10));
    camera->SetDir(VGet(10, 10, -10));

    //�V�[���ڍs���̉��o���I�������
    if (!ObjManager::GetFirstObj(ObjectTag::Remarks))
    {
        //�Ǘ��N���X���̊m�ۂ����f�[�^���
        AssetManager::ReleaseAllAsset();
        ObjManager::ReleaseAllObj();

        //�V�[�������̏�ʂɂ���
        SaveScene::Save(nullptr);
        return new TitleScene;
    }
    return this;
}

// �`�揈�� //

void Ending::DrawScene()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();
}