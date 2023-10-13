#include<assert.h>

#include"../../Shade/Bloom/Bloom.h"
#include "ObjManager.h"

//���Ԃւ̃|�C���^��`
std::unique_ptr<ObjManager> ObjManager::singleton = nullptr;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjManager::ObjManager()
    :object()
    , bloom(new Bloom)
{
    //�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjManager::~ObjManager()
{
    DeleteAllObj();
}

/// <summary>
/// ����������
/// </summary>
void ObjManager::Init()
{
    //�C���X�^���X����
    if (!singleton)
    {
        singleton.reset(new ObjManager);
    }
}

/// <summary>
/// �I�u�W�F�N�g�ǉ�����
/// </summary>
/// <param name="newObj">:�ǉ��I�u�W�F�N�g</param>
void ObjManager::AddObj(ObjBase* newObj)
{
    ObjTag tag = newObj->GetTag();
    singleton->object[tag].emplace_back(newObj);
}

/// <summary>
/// �S�I�u�W�F�N�g�X�V����
/// </summary>
/// <param name="deltaTime">:�f���^�^�C��</param>
void ObjManager::UpdateAllObj(const float deltaTime)
{
    //�S�^�O���X�V�������܂Ƃ߂čs��
    for (auto& tag : ObjTagAll)
    {
        for (int i = 0; i < singleton->object[tag].size(); i++)
        {
            singleton->object[tag][i]->Update(deltaTime);
        }
    }

    //�u���[���p���
    singleton->bloom->SetColoerScreen();

    OnDeadObj();
}

/// <summary>
/// �S�I�u�W�F�N�g�`�揈��
/// </summary>
void ObjManager::DrawAllObj()
{
    //�S�^�O���`�揈�����܂Ƃ߂čs��
    for (auto& tag : ObjTagAll)
    {
        for (int i = 0; i < singleton->object[tag].size(); i++)
        {
            //�I�u�W�F�N�g�����Ȃ�`�悳����
            if (singleton->object[tag][i]->IsVisible())
            {
                singleton->object[tag][i]->Draw();
            }
        }
    }

    //�u���[���`��
    singleton->bloom->SetBloomGraph();
    singleton->bloom->Draw();
}

/// <summary>
///�I�u�W�F�N�g���S����
/// </summary>
void ObjManager::OnDeadObj()
{
    //�S�^�O�����S�I�u�W�F�N�g��T���č폜
    for (auto& tag : ObjTagAll)
    {
        for (auto& dead : singleton->object[tag])
        {
            //����ł�����I�u�W�F�N�g�폜
            if (!dead->IsAlive())
            {
                DeleteObj(dead);
            }
        }
    }
}

/// <summary>
/// �I�u�W�F�N�g�폜����
/// </summary>
/// <param name="deleteObj">:�폜�I�u�W�F�N�g</param>
void ObjManager::DeleteObj(std::shared_ptr<ObjBase> deleteObj)
{
    //�폜�I�u�W�F�N�g�̃^�O�擾
    ObjTag tag = deleteObj->GetTag();

    //�I�u�W�F�N�g������
    auto endObj = singleton->object[tag].end();
    auto findObj = std::find(singleton->object[tag].begin(), endObj, deleteObj);
    assert(findObj != endObj);

    //���������疖���Ɉړ������č폜
    if (findObj != endObj)
    {
        std::swap(findObj, endObj);
        singleton->object[tag].pop_back();
        singleton->object[tag].shrink_to_fit();
    }
}

/// <summary>
/// �S�I�u�W�F�N�g�폜����
/// </summary>
void ObjManager::DeleteAllObj()
{
    //�󂶂�Ȃ�������I�u�W�F�N�g�폜
    for (auto& tag : ObjTagAll)
    {
        if (!singleton->object[tag].empty())
        {
            singleton->object[tag].clear();
            singleton->object[tag].shrink_to_fit();
        }
    }
}

/// <summary>
/// �����蔻�菈��
/// </summary>
void ObjManager::OnCollision()
{
    //�����蔻��̑g�ݍ��킹
    //Ghost
    for (auto& gstCol: singleton->object[ObjTag::Ghost])
    {
        for (auto& mapCol :singleton->object[ObjTag::Map])
        {
            gstCol->OnCollisionEnter(mapCol.get());
        }
        for (auto& plyCol:singleton->object[ObjTag::Player])
        {
            gstCol->OnCollisionEnter(plyCol.get());
        }
    }

    //Player
    for (auto& plyCol :singleton->object[ObjTag::Player])
    {
        for (auto& mapCol:singleton->object[ObjTag::Map])
        {
            plyCol->OnCollisionEnter(mapCol.get());
        }
        for (auto& furCol : singleton->object[ObjTag::Furniture])
        {
            plyCol->OnCollisionEnter(furCol.get());
        }
        for (auto& gstCol : singleton->object[ObjTag::Ghost])
        {
            plyCol->OnCollisionEnter(gstCol.get());
        }
    }
}

/// <summary>
/// �^�O�̐擪�I�u�W�F�N�g�擾
/// </summary>
/// <param name="tag">:�I�u�W�F�N�g�^�O</param>
/// <returns>�I�u�W�F�N�g</returns>
ObjBase* ObjManager::GetFirstObj(ObjTag tag)
{
    //�I�u�W�F�N�g�̐���0��������nullptr��Ԃ�
    if (singleton->object[tag].size() == 0)		
    {
        return nullptr;
    }

    //�^�O��̍ŏ��̃I�u�W�F�N�g��Ԃ�
    return singleton->object[tag][0].get();
}

// �^�O�̎w��I�u�W�F�N�g�擾 //

ObjBase* ObjManager::GetObj(ObjTag tag, int tagNum)
{
    //�I�u�W�F�N�g�̐����w�萔��菭�Ȃ�������nullptr��Ԃ�
    if (singleton->object[tag].size() < static_cast<unsigned long long>(tagNum) + 1)
    {
        return nullptr;
    }

    //�^�O���tagNum�Ԗڂ̃I�u�W�F�N�g��Ԃ�
    return singleton->object[tag][tagNum].get();
}