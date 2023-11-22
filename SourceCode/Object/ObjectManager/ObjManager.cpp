#include<assert.h>

#include"../../Shade/Bloom/Bloom.h"
#include "ObjManager.h"

std::unique_ptr<ObjManager> ObjManager::singleton = nullptr;

ObjManager::ObjManager()
    :object()
    , bloom(new Bloom)
{
    //�����Ȃ�
}

ObjManager::~ObjManager()
{
    DeleteAllObj();
}

void ObjManager::Init()
{
    //�C���X�^���X����
    if (!singleton)
    {
        singleton.reset(new ObjManager);
    }
}

void ObjManager::AddObj(ObjBase* newObj)
{
    ObjTag tag = newObj->GetTag();
    singleton->object[tag].emplace_back(newObj);
}

void ObjManager::UpdateAllObj(const float deltaTime)
{
    //�S�^�O���X�V�������܂Ƃ߂čs��
    for (auto& tag : ObjTagAll)
    {
        for (auto& obj : singleton->object[tag])
        {
            obj->Update(deltaTime);
        }
    }

    //�u���[���p���
    singleton->bloom->SetColoerScreen();

    singleton->OnDeadObj();
}

void ObjManager::DrawAllObj()
{
    //�S�^�O���`�揈�����܂Ƃ߂čs��
    for (auto& tag : ObjTagAll)
    {
        for (auto& obj : singleton->object[tag])
        {
            //�I�u�W�F�N�g�����Ȃ�`�悳����
            if (obj->IsVisible())
            {
                obj->Draw();
            }
        }
    }

    //�u���[���`��
    singleton->bloom->SetBloomGraph();
    singleton->bloom->Draw();
}

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
                singleton->DeleteObj(dead);
            }
        }
    }
}

void ObjManager::DeleteObj(std::shared_ptr<ObjBase>& deleteObj)
{
    //�폜�I�u�W�F�N�g�̃^�O�擾
    ObjTag tag = deleteObj->GetTag();

    //�I�u�W�F�N�g������
    auto endObj = singleton->object[tag].end();
    auto findObj = std::find(singleton->object[tag].begin(), endObj, deleteObj);

    //���������疖���Ɉړ������č폜
    if (findObj != endObj)
    {
        std::swap(findObj, endObj);
        singleton->object[tag].pop_back();
    }
}

void ObjManager::DeleteAllObj()
{
    //�󂶂�Ȃ�������I�u�W�F�N�g�폜
    for (auto& tag : ObjTagAll)
    {
        if (!singleton->object[tag].empty())
        {
            singleton->object[tag].clear();
        }
    }
}

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