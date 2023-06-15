#include "AssetManager.h"


AssetManager* AssetManager::assetInstance = nullptr;    //AssetManager���Ԃւ̃|�C���^��`

    // @brief AssetManager�R���X�g���N�^�[ //

AssetManager::AssetManager()
{
    SetEnableXAudioFlag(FALSE);
    Set3DSoundOneMetre(20.0f);

}

    // @brief AssetManager�f�X�g���N�^�[ //

AssetManager::~AssetManager()
{
    assetInstance->ReleaseAllAsset();       //���ׂẴA�Z�b�g���폜
    assetInstance = nullptr;                //�|�C���^���폜
}

    // @brief AssetManager������ //

void AssetManager::Init()
{
    if (!assetInstance)                     //�|�C���^���󂾂�����
    {
        assetInstance = new AssetManager;   //�|�C���^������
    }
}

    // @brief ���b�V���̎擾 //

int AssetManager::GetMesh(std::string meshFileName)
{
    int meshID = 0;
    //---���b�V���o�^---//
    auto iter = assetInstance->meshMap.find(meshFileName);   //�t�@�C�����o�^����Ă��邩�ǂ�������

    if (iter == assetInstance->meshMap.end())                                               //�o�^����Ă��Ȃ�������
    {
        meshID = MV1LoadModel(meshFileName.c_str());                                        //�V�K�t�@�C���ǂݍ���
        if (meshID == -1)                                                                   //ID���󂾂�����
        {
            return meshID;                                                                  //ID��Ԃ�
        }
        assetInstance->meshMap.emplace(meshFileName, meshID);                //�t�@�C����ID�Ƌ��ɓo�^
    }

    //---�����������b�V����ԋp---//
    meshID = MV1DuplicateModel(assetInstance->meshMap[meshFileName]);             //���b�V�������AID�ɑ��
    assetInstance->duplicateMesh.push_back(meshID);                                   //�����𖖔��ɒǉ�
    return meshID;                                                                         //��������ID��Ԃ�
}

    // @brief �A�j���[�V�����̎擾 //

int AssetManager::GetAnim(std::string animFileName)
{
    int animID = 0;
    //---�A�j���[�V�����o�^---//
    auto iter = assetInstance->animMap.find(animFileName);  //�t�@�C�����o�^����Ă��邩�ǂ�������

    if (iter == assetInstance->animMap.end())                                             //�o�^����Ă��Ȃ�������
    {
        animID = MV1LoadModel(animFileName.c_str());                                      //�V�K�t�@�C���ǂݍ���
        if (animID == -1)                                                                 //ID���󂾂�����
        {
            return animID;                                                                //ID��Ԃ�
        }
        assetInstance->animMap.emplace(animFileName, animID);               //�t�@�C����ID�Ƌ��ɓo�^
    }

    return assetInstance->animMap[animFileName];                                         //�A�j���[�V����ID��Ԃ�
}

int AssetManager::GetSound(std::string soundFileName)
{
    int meshID = 0;
    //---���b�V���o�^---//
    auto iter = assetInstance->soundMap.find(soundFileName);   //�t�@�C�����o�^����Ă��邩�ǂ�������

    if (iter == assetInstance->soundMap.end())                                               //�o�^����Ă��Ȃ�������
    {
        meshID = LoadSoundMem(soundFileName.c_str());                                        //�V�K�t�@�C���ǂݍ���
        if (meshID == -1)                                                                   //ID���󂾂�����
        {
            return meshID;                                                                  //ID��Ԃ�
        }
        assetInstance->meshMap.emplace(soundFileName, meshID);                //�t�@�C����ID�Ƌ��ɓo�^
    }

    //---�����������b�V����ԋp---//
    meshID = DuplicateSoundMem(assetInstance->meshMap[soundFileName]);             //���b�V�������AID�ɑ��
    assetInstance->duplicateMesh.push_back(meshID);                                   //�����𖖔��ɒǉ�
    return meshID;                                                                         //��������ID��Ԃ�
}

    // @brief ���b�V���̍폜 //

void AssetManager::ReleaseMesh(int meshID)
{
    auto iter = find(assetInstance->duplicateMesh.begin(),
        assetInstance->duplicateMesh.end(), meshID);                            //�������ꂽ���b�V����������
    if (iter == assetInstance->duplicateMesh.end())                                        //������Ȃ�������
    {
        return;                                                                            //���ʂ�Ԃ�
    }
    MV1DeleteModel(meshID);                                                         //���b�V���폜

    iter_swap(iter, assetInstance->duplicateMesh.end() - 1);                   //�����̃f�[�^�Ɠ���ւ���
    assetInstance->duplicateMesh.pop_back();                                                //�����̃f�[�^���폜
}

    // @brief �S�A�Z�b�g�̍폜 //

void AssetManager::ReleaseAllAsset()
{
    //---�A�j���[�V�������---//
    for (auto& anim : assetInstance->animMap)
    {
        MV1DeleteModel(anim.second);
    }

    //---���b�V�����---//
    for (auto& mesh : assetInstance->meshMap)
    {
        MV1DeleteModel(mesh.second);
    }

    //�T�E���h�J��
    for (auto& sound : assetInstance->soundMap)
    {
        DeleteSoundMem(sound.second);
    }

    //---�������---//
    for (auto dup : assetInstance->duplicateMesh)
    {
        MV1DeleteModel(dup);
    }
    for (auto dup : assetInstance->duplicateSound)
    {
        DeleteSoundMem(dup);
    }


    assetInstance->animMap.clear();             //�A�j���[�V�����̂��ׂĂ̗v�f���폜
    assetInstance->meshMap.clear();             //���b�V���̂��ׂĂ̗v�f���폜
    assetInstance->soundMap.clear();
    assetInstance->duplicateMesh.clear();       //�������b�V���̂��ׂĂ̗v�f���폜
    assetInstance->duplicateSound.clear();
}

    // @brief AssetManager�̉�� //

void AssetManager::Finalize()
{
    ReleaseAllAsset();
    if (assetInstance)                          //�|�C���^���󂶂�Ȃ�������
    {
        delete assetInstance;                   //���g���폜
    }
}