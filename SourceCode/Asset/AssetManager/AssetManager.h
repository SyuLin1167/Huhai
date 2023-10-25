#pragma once
#include<DxLib.h>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<memory>

/// <summary>
/// �A�Z�b�g�S�ʂ̊Ǘ�
/// </summary>
class AssetManager final
{
public:
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~AssetManager();

    /// <summary>
    /// ����������
    /// </summary>
    static void Init();

    /// <summary>
    /// �O���t�擾
    /// </summary>
    /// <param name="fileName">:�t�@�C����</param>
    /// <returns>:���������O���tID</returns>
    static int GetGraph(std::string fileName);

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

private:
    /// <summary>
    /// �R���X�g���N�^(�V���O���g��)
    /// </summary>
    AssetManager();

    static std::unique_ptr<AssetManager> singleton;     //���g�̎���
    std::unordered_map<std::string, int>graphMap;       //�O���t(�I���W�i��)
    std::unordered_map<std::string, int>meshMap;        //���b�V��(�I���W�i��)
    std::unordered_map<std::string, int>animMap;        //�A�j���[�V����(�I���W�i��)
    std::unordered_map<std::string, int>soundMap;       //�T�E���h(�I���W�i��)
    std::vector<int> dupMesh;                           //���b�V��(����)
    std::vector<int> dupSound;                          //�T�E���h(����)
};
