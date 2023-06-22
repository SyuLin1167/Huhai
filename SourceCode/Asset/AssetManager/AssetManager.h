#pragma once
#include<DxLib.h>
#include<string>
#include<unordered_map>

/* AssetManager�N���X */
class AssetManager final
{
public:
    /// <summary>
    /// ����������
    /// </summary>
    static void Init();

    /// <summary>
    /// ���b�V���擾
    /// </summary>
    /// <param name="fileName">:�t�@�C����</param>
    /// <returns>�����������b�V��ID</returns>
    static int GetMesh(std::string fileName);

    /// <summary>
    /// �A�j���[�V�����擾
    /// </summary>
    /// <param name="fileName">:�t�@�C����</param>
    /// <returns>�A�j���[�V����ID</returns>
    static int GetAnim(std::string fileName);

    /// <summary>
    /// �T�E���h�擾
    /// </summary>
    /// <param name="fileName">:�t�@�C����</param>
    /// <returns>���������T�E���hID</returns>
    static int GetSound(std::string fileName);

    /// <summary>
    /// ���b�V���폜
    /// </summary>
    /// <param name="meshID">:���b�V��ID</param>
    static void ReleaseMesh(int meshID);

    /// <summary>
    /// �S�A�Z�b�g�폜
    /// </summary>
    static void ReleaseAllAsset();

    /// <summary>
    /// �㏈��
    /// </summary>
    static void Finalize();

private:
    /// <summary>
    /// �R���X�g���N�^(�V���O���g��)
    /// </summary>
    AssetManager();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~AssetManager();

    static AssetManager* assetMgr;                      //���g�̎���
    std::unordered_map<std::string, int>meshMap;        //���b�V��(�I���W�i��)
    std::unordered_map<std::string, int>animMap;        //�A�j���[�V����(�I���W�i��)
    std::unordered_map<std::string, int>soundMap;       //�T�E���h(�I���W�i��)
    std::vector<int> dupMesh;                     //���b�V��(����)
    std::vector<int> dupSound;                    //�T�E���h(����)
};
