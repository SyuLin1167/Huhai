#include "AssetManager.h"


//���Ԃւ̃|�C���^��`
std::unique_ptr<AssetManager> AssetManager::singleton = nullptr;

/// <summary>
/// �R���X�g���N�^
/// </summary>
AssetManager::AssetManager()
{
    SetEnableXAudioFlag(TRUE);
    Set3DSoundOneMetre(10.0f);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
AssetManager::~AssetManager()
{
    //�S�A�Z�b�g�폜
    ReleaseAllAsset();
}

/// <summary>
/// ����������
/// </summary>
void AssetManager::Init()
{
    //�C���X�^���X����
    if (!singleton)
    {
        singleton.reset(new AssetManager);
    }
}

/// <summary>
/// �O���t�擾
/// </summary>
/// <param name="fileName">:�t�@�C����</param>
/// <returns>:���������O���tID</returns>
int AssetManager::GetGraph(std::string fileName)
{
    int meshID = 0;

    //�t�@�C�����������ēo�^����Ă��Ȃ�������o�^
    auto findFile = singleton->graphMap.find(fileName);
    if (findFile == singleton->graphMap.end())
    {
        meshID = LoadGraph(fileName.c_str());

        //ID����Ȃ炻�̂܂ܕԂ�
        if (meshID == -1)
        {
            return meshID;
        }

        singleton->graphMap.emplace(fileName, meshID);
    }

    //�O���tID��Ԃ�
    return singleton->graphMap[fileName];
}


/// <summary>
/// ���b�V���擾
/// </summary>
/// <param name="fileName">:�t�@�C����</param>
/// <returns>�����������b�V��ID</returns>
int AssetManager::GetMesh(std::string fileName)
{
    int meshID = 0;

    //�t�@�C�����������ēo�^����Ă��Ȃ�������o�^
    auto iter = singleton->meshMap.find(fileName);
    if (iter == singleton->meshMap.end())
    {
        meshID = MV1LoadModel(fileName.c_str());

        //ID����Ȃ炻�̂܂ܕԂ�
        if (meshID == -1)
        {
            return meshID;
        }

        singleton->meshMap.emplace(fileName, meshID);
    }

    //�����������b�V��ID��Ԃ�
    meshID = MV1DuplicateModel(singleton->meshMap[fileName]);
    singleton->dupMesh.push_back(meshID);
    return meshID;
}

/// <summary>
/// �A�j���[�V�����擾
/// </summary>
/// <param name="fileName">:�t�@�C����</param>
/// <returns>�A�j���[�V����ID</returns>
int AssetManager::GetAnim(std::string fileName)
{
    int animID = 0;

    //�t�@�C�����������ēo�^����Ă��Ȃ�������o�^
    auto iter = singleton->animMap.find(fileName);
    if (iter == singleton->animMap.end())
    {
        animID = MV1LoadModel(fileName.c_str());

        //ID����Ȃ炻�̂܂ܕԂ�
        if (animID == -1)
        {
            return animID;
        }

        singleton->animMap.emplace(fileName, animID);
    }

    //�A�j���[�V����ID��Ԃ�
    return singleton->animMap[fileName];
}

/// <summary>
/// �T�E���h�擾
/// </summary>
/// <param name="fileName">:�t�@�C����</param>
/// <returns>���������T�E���hID</returns>
int AssetManager::GetSound(std::string fileName)
{
    int meshID = 0;

    //�t�@�C�����������ēo�^����Ă��Ȃ�������o�^
    auto iter = singleton->soundMap.find(fileName);

    if (iter == singleton->soundMap.end())
    {
        meshID = LoadSoundMem(fileName.c_str());

        //ID����Ȃ炻�̂܂ܕԂ�
        if (meshID == -1)
        {
            return meshID;
        }

        singleton->meshMap.emplace(fileName, meshID);
    }

    //���������T�E���hID��Ԃ�
    meshID = DuplicateSoundMem(singleton->meshMap[fileName]);
    singleton->dupMesh.push_back(meshID);
    return meshID;
}

/// <summary>
/// ���b�V���폜
/// </summary>
/// <param name="meshID">:���b�V��ID</param>
void AssetManager::ReleaseMesh(int meshID)
{
    //�����������b�V��������
    auto iter = find(singleton->dupMesh.begin(),
        singleton->dupMesh.end(), meshID);

    //������Ȃ������猋�ʂ�Ԃ�
    if (iter == singleton->dupMesh.end())
    {
        return;
    }

    //���������疖���ړ����č폜
    MV1DeleteModel(meshID);
    std::iter_swap(iter, singleton->dupMesh.end() - 1);
    singleton->dupMesh.pop_back();
}

// �S�A�Z�b�g�폜 //

void AssetManager::ReleaseAllAsset()
{
    //�O���t���
    for (auto& graph : singleton->graphMap)
    {
        DeleteGraph(graph.second);
    }
    //�A�j���[�V�������
    for (auto& anim : singleton->animMap)
    {
        MV1DeleteModel(anim.second);
    }

    //���b�V�����
    for (auto& mesh : singleton->meshMap)
    {
        MV1DeleteModel(mesh.second);
    }

    //�T�E���h���
    for (auto& sound : singleton->soundMap)
    {
        DeleteSoundMem(sound.second);
    }

    //�������-
    for (auto dup : singleton->dupMesh)
    {
        MV1DeleteModel(dup);
    }
    for (auto dup : singleton->dupSound)
    {
        DeleteSoundMem(dup);
    }

    //�A�Z�b�g�̗v�f�폜
    singleton->graphMap.clear();
    singleton->animMap.clear();
    singleton->meshMap.clear();
    singleton->soundMap.clear();

    //�����̗v�f�폜
    singleton->dupMesh.clear();
    singleton->dupSound.clear();
}