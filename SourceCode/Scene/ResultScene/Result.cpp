#include "Result.h"

#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include "../../UI/Reamarks/Remarks.h"
#include "../TitleScene/Title.h"
#include"../Save/Save.h"

// �R���X�g���N�^ //

ResultScene::ResultScene()
    :SceneBase()
{
    //�䎌����
    ObjManager::Entry(new Remarks(TextType::GameClear));

    //�J�����ݒ�
    SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 20.0f, 0.0f), VGet(30.0f, 10.0f, 0.0f));
}

// �f�X�g���N�^ //

ResultScene::~ResultScene()
{
}

// �X�V���� //

SceneBase* ResultScene::Update(float deltaTime)
{
    //�I�u�W�F�N�g�X�V
    ObjManager::Update(deltaTime);

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

void ResultScene::Draw()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();
}