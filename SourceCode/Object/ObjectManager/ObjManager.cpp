#include "ObjManager.h"

#include"../../Shade/Bloom/Bloom.h"
#include"../../Scene/PauseMenu/PauseMenu.h"

//���Ԃւ̃|�C���^��`
ObjManager* ObjManager::objManager = nullptr;

// �R���X�g���N�^ //

ObjManager::ObjManager()
    :Object()
    , holdObj()
    , bloom(nullptr)
{
    bloom = new Bloom;
}

// �f�X�g���N�^ //

ObjManager::~ObjManager()
{
    //�C���X�^���X�폜
    if (bloom)
    {
        delete bloom;
    }
}

// ���������� //

void ObjManager::Init()
{
    //�C���X�^���X����
    if (!objManager)
    {
        objManager = new ObjManager;
    }
}

// �o�^ //

void ObjManager::Entry(ObjBase* newObj)
{
    //�ꎞ�ۑ��ꏊ�ɃI�u�W�F�N�g�ǉ�
    objManager->holdObj.emplace_back(newObj);
}

// �폜 //

void ObjManager::Release(ObjBase* releaseObj)
{
    //�ۑ��ꏊ�̃I�u�W�F�N�g����
    auto iter = find(objManager->holdObj.begin(),
        objManager->holdObj.end(), releaseObj);

    //�I�u�W�F�N�g�����������疖���Ɉڂ��č폜
    if (iter != objManager->holdObj.end())
    {
        std::iter_swap(iter, objManager->holdObj.end() - 1);
        objManager->holdObj.pop_back();
        return;
    }

	//�A�N�e�B�u�ɂ���^�O�̃I�u�W�F�N�g����
    ObjectTag tag = releaseObj->GetTag();					
    iter = find(objManager->Object[tag].begin(),
        objManager->Object[tag].end(), releaseObj);

    //�I�u�W�F�N�g�����������疖���Ɉڂ��č폜
    if (iter != objManager->Object[tag].end())
    {
        std::iter_swap(iter, objManager->Object[tag].end() - 1);
        delete objManager->Object[tag].back();
    }
}

// �S�폜 //

void ObjManager::ReleaseAllObj()
{
    //�ꎞ�ۑ��ꏊ�̒�����ɂȂ�܂Ŗ�������I�u�W�F�N�g�폜
    while (!objManager->holdObj.empty())
    {
        delete objManager->holdObj.back();
        objManager->holdObj.pop_back();
    }

    //�A�N�e�B�u�̒�����ɂȂ�܂Ŗ�������I�u�W�F�N�g�폜
    for (auto& tag : ObjTagAll)
    {
        while (!objManager->Object[tag].empty())
        {
            delete objManager->Object[tag].back();
            objManager->Object[tag].pop_back();
        }
    }
}

// �S�X�V���� //

void ObjManager::Update(float deltaTime)
{

    // �Y���^�O�ɂ��邷�ׂẴI�u�W�F�N�g���X�V
    for (auto& tag : ObjTagAll)
    {
        for (int i = 0; i < objManager->Object[tag].size(); ++i)
        {
            objManager->Object[tag][i]->Update(deltaTime);
        }
    }

    //�u���[���p���
    if (PauseMenu::HasStatus("Bloom"))
    {
        objManager->bloom->SetColoerScreen();
    }
    else
    {
        SetCameraNearFar(0.1f, 400.0f);
    }

    //�ꎞ�ۑ����̃I�u�W�F�N�g���A�N�e�B�u���X�g�ɒǉ�
    for (auto holding : objManager->holdObj)
    {
        ObjectTag tag = holding->GetTag();
        objManager->Object[tag].emplace_back(holding);
    }

    //�S�Ĉڂ��I�������ۑ��ꏊ�̒��g����ɂ���
    objManager->holdObj.clear();

    Dead();
}

// ���S���� //

void ObjManager::Dead()
{

    //���S�����I�u�W�F�N�g���������Ď��S�I�u�W�F�N�g�Ɉړ�
    std::vector<ObjBase*>deadObj;
    for (auto& tag : ObjTagAll)
    {
        for (auto obj : objManager->Object[tag])
        {
            if (!obj->IsAlive())
            {
                deadObj.emplace_back(obj);
            }
        }
        objManager->Object[tag].erase(remove_if(begin(objManager->Object[tag]), end(objManager->Object[tag]),
            [](ObjBase* dead) {return !dead->IsAlive(); }), cend(objManager->Object[tag]));
    }

    //���S�I�u�W�F�N�g�̒��g����ɂȂ�܂ō폜
	while (!deadObj.empty())
    {
        delete deadObj.back();
        deadObj.pop_back();
    }
}

// �S�`�揈�� //

void ObjManager::Draw()
{
    //�Y���^�O�ɂ��邷�ׂẴI�u�W�F�N�g��`��
    for (auto& tag : ObjTagAll)
    {

        for (int i = 0; i < objManager->Object[tag].size(); ++i)
        {
            if (objManager->Object[tag][i]->IsVisible())
            {
                objManager->Object[tag][i]->Draw();
            }
        }
    }

    //�u���[���`��
    if (PauseMenu::HasStatus("Bloom"))
    {
        objManager->bloom->SetBloomGraph();
        objManager->bloom->Draw();
    }
}

// �����蔻�菈�� //

void ObjManager::Collision()
{
    //�����蔻��̑g�ݍ��킹
    //Ghost
    for (int gstNum = 0; gstNum < objManager->Object[ObjectTag::Ghost].size(); ++gstNum)
    {
        for (int mapNum = 0; mapNum < objManager->Object[ObjectTag::Map].size(); ++mapNum)
        {
            objManager->Object[ObjectTag::Ghost][gstNum]->
                OnCollisionEnter(objManager->Object[ObjectTag::Map][mapNum]);
        }
        for (int plyNum = 0; plyNum < objManager->Object[ObjectTag::Player].size(); ++plyNum)
        {
            objManager->Object[ObjectTag::Ghost][gstNum]->
                OnCollisionEnter(objManager->Object[ObjectTag::Player][plyNum]);
        }
    }

    //Player
    for (int plyNum = 0; plyNum < objManager->Object[ObjectTag::Player].size(); ++plyNum)
    {
        for (int mapNum = 0; mapNum < objManager->Object[ObjectTag::Map].size(); ++mapNum)
        {
            objManager->Object[ObjectTag::Player][plyNum]->
                OnCollisionEnter(objManager->Object[ObjectTag::Map][mapNum]);
        }
        for (int furNum = 0; furNum < objManager->Object[ObjectTag::Furniture].size(); ++furNum)
        {
            objManager->Object[ObjectTag::Player][plyNum]->
                OnCollisionEnter(objManager->Object[ObjectTag::Furniture][furNum]);
        }
        for (int gstNum = 0; gstNum < objManager->Object[ObjectTag::Ghost].size(); ++gstNum)
        {
            objManager->Object[ObjectTag::Player][plyNum]->
                OnCollisionEnter(objManager->Object[ObjectTag::Ghost][gstNum]);
        }
    }
}

// �^�O�̐擪�I�u�W�F�N�g�擾 //

ObjBase* ObjManager::GetFirstObj(ObjectTag tag)
{
    //�I�u�W�F�N�g�̐���0��������nullptr��Ԃ�
    if (objManager->Object[tag].size() == 0)		
    {
        return nullptr;
    }

    //�^�O��̍ŏ��̃I�u�W�F�N�g��Ԃ�
    return objManager->Object[tag][0];
}

// �^�O�̎w��I�u�W�F�N�g�擾 //

ObjBase* ObjManager::GetObj(ObjectTag tag, int tagNum)
{
    //�I�u�W�F�N�g�̐����w�萔��菭�Ȃ�������nullptr��Ԃ�
    if (objManager->Object[tag].size() < static_cast<unsigned long long>(tagNum) + 1)
    {
        return nullptr;
    }

    //�^�O���tagNum�Ԗڂ̃I�u�W�F�N�g��Ԃ�
    return objManager->Object[tag][tagNum];
}

// �㏈�� //

void ObjManager::Finalize()
{
    //�S�I�u�W�F�N�g���
    ReleaseAllObj();

    //�C���X�^���X�폜
    if (objManager)
    {
        delete objManager;
    }
}