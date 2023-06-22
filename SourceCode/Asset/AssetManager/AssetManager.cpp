#include "AssetManager.h"

//���Ԃւ̃|�C���^��`
AssetManager* AssetManager::assetMgr = nullptr;

// �R���X�g���N�^ //

AssetManager::AssetManager()
{
    SetEnableXAudioFlag(FALSE);
    Set3DSoundOneMetre(20.0f);
}

// �f�X�g���N�^ //

AssetManager::~AssetManager()
{
}

// ���������� //

void AssetManager::Init()
{
    //�C���X�^���X����
    if (!assetMgr)
    {
        assetMgr = new AssetManager;
    }
}

// ���b�V���擾 //

int AssetManager::GetMesh(std::string fileName)
{
    int meshID = 0;
    //�t�@�C�����������ēo�^����Ă��Ȃ�������o�^
    auto iter = assetMgr->meshMap.find(fileName);
    if (iter == assetMgr->meshMap.end())
    {
        meshID = MV1LoadModel(fileName.c_str());
        
        //ID����Ȃ炻�̂܂ܕԂ�
        if (meshID == -1)
        {
            return meshID;
        }

        assetMgr->meshMap.emplace(fileName, meshID);
    }

    //�����������b�V��ID��Ԃ�
    meshID = MV1DuplicateModel(assetMgr->meshMap[fileName]);
    assetMgr->dupMesh.push_back(meshID);
    return meshID;
}

// �A�j���[�V�����擾 //

int AssetManager::GetAnim(std::string fileName)
{
    int animID = 0;
    //�t�@�C�����������ēo�^����Ă��Ȃ�������o�^
    auto iter = assetMgr->animMap.find(fileName);
    if (iter == assetMgr->animMap.end())
    {
        animID = MV1LoadModel(fileName.c_str());

        //ID����Ȃ炻�̂܂ܕԂ�
        if (animID == -1)
        {
            return animID;
        }

        assetMgr->animMap.emplace(fileName, animID);
    }

    //�A�j���[�V����ID��Ԃ�
    return assetMgr->animMap[fileName];
}

// �T�E���h�擾 //

int AssetManager::GetSound(std::string fileName)
{
    int meshID = 0;
    //�t�@�C�����������ēo�^����Ă��Ȃ�������o�^
    auto iter = assetMgr->soundMap.find(fileName);

    if (iter == assetMgr->soundMap.end())
    {
        meshID = LoadSoundMem(fileName.c_str());

        //ID����Ȃ炻�̂܂ܕԂ�
        if (meshID == -1)
        {
            return meshID;
        }

        assetMgr->meshMap.emplace(fileName, meshID);
    }

    //���������T�E���hID��Ԃ�
    meshID = DuplicateSoundMem(assetMgr->meshMap[fileName]);
    assetMgr->dupMesh.push_back(meshID);
    return meshID;
}

    // @brief ���b�V���̍폜 //

void AssetManager::ReleaseMesh(int meshID)
{
    //�����������b�V��������
    auto iter =find(assetMgr->dupMesh.begin(),
        assetMgr->dupMesh.end(), meshID);

    //������Ȃ������猋�ʂ�Ԃ�
    if (iter == assetMgr->dupMesh.end())
    {
        return;
    }

    //���������疖���ړ����č폜
    MV1DeleteModel(meshID);
    iter_swap(iter, assetMgr->dupMesh.end() - 1);
    assetMgr->dupMesh.pop_back();
}

// �S�A�Z�b�g�폜 //

void AssetManager::ReleaseAllAsset()
{
    //�A�j���[�V�������
    for (auto& anim : assetMgr->animMap)
    {
        MV1DeleteModel(anim.second);
    }

    //���b�V�����
    for (auto& mesh : assetMgr->meshMap)
    {
        MV1DeleteModel(mesh.second);
    }

    //�T�E���h���
    for (auto& sound : assetMgr->soundMap)
    {
        DeleteSoundMem(sound.second);
    }

    //---�������---//
    for (auto dup : assetMgr->dupMesh)
    {
        MV1DeleteModel(dup);
    }
    for (auto dup : assetMgr->dupSound)
    {
        DeleteSoundMem(dup);
    }

    //�A�Z�b�g�̗v�f�폜
    assetMgr->animMap.clear();
    assetMgr->meshMap.clear();
    assetMgr->soundMap.clear();

    //�����̗v�f�폜
    assetMgr->dupMesh.clear();
    assetMgr->dupSound.clear();
}

// �㏈�� //

void AssetManager::Finalize()
{
    //�S�A�Z�b�g�폜
    ReleaseAllAsset();

    //�C���X�^���X�폜
    if (assetMgr)
    {
        delete assetMgr;
    }
}