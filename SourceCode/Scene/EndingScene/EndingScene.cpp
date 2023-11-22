#include "EndingScene.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Object/CharaObject/Camera/FixedCamera/FixedCamera.h"
#include"../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Furniture/Furniture.h"
#include"../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../UI/Reamarks/Remarks.h"
#include "../TitleScene/TitleScene.h"
#include"../SaveScene/SaveScene.h"

EndingScene::EndingScene()
    :SceneBase()
{
    sceneName = "ending";

    //�J��������
    ObjManager::AddObj(new FixedCamera);

    //�}�b�v����
    ObjManager::AddObj(new Map(Map::MapTag::ROOM));
    
    //�Ƌ��
    ObjManager::AddObj(new Furniture(Furniture::FurName::Room));
    //�Ɩ�����
    ObjManager::AddObj(new NomalLight(sceneName));

    //�䎌����
    ObjManager::AddObj(new Remarks(TextType::GameClear));
}

EndingScene::~EndingScene()
{
    //�����Ȃ�
}

SceneBase* EndingScene::UpdateScene(const float deltaTime)
{
    //�I�u�W�F�N�g�X�V
    ObjManager::UpdateAllObj(deltaTime);

    //�J�����ݒ�
    ObjBase* camera = ObjManager::GetFirstObj(ObjTag::Camera);
    camera->SetPos(VGet(50, 10, 10));
    camera->SetDir(VGet(10, 10, -10));

    //�V�[���ڍs���̉��o���I�������
    if (!ObjManager::GetFirstObj(ObjTag::Remarks))
    {
        //�Ǘ��N���X���̊m�ۂ����f�[�^���
        AssetManager::ReleaseAllAsset();
        ObjManager::DeleteAllObj();

        //�V�[�������̏�ʂɂ���
        SaveScene::Save(nullptr);
        return new TitleScene;
    }
    return this;
}

void EndingScene::DrawScene()
{
    //�I�u�W�F�N�g�`��
    ObjManager::DrawAllObj();
}