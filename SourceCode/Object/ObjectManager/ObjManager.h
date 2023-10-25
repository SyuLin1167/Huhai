#pragma once
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<memory>

#include"../ObjectBase/ObjBase.h"
#include"../ObjectBase/ObjTag.h"

/// <summary>
/// �I�u�W�F�N�g�̊Ǘ�
/// </summary>
class ObjManager final
{
public:
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ObjManager();

    /// <summary>
    /// ����������
    /// </summary>
    static void Init();

    /// <summary>
    /// �I�u�W�F�N�g�ǉ�����
    /// </summary>
    /// <param name="newObj">:�ǉ��I�u�W�F�N�g</param>
    static void AddObj(ObjBase* newObj);

    /// <summary>
    /// �S�I�u�W�F�N�g�X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    static void UpdateAllObj(const float deltaTime);

    /// <summary>
    /// �S�I�u�W�F�N�g�����蔻�菈��
    /// </summary>
    static void OnCollision();

    /// <summary>
    /// �S�I�u�W�F�N�g�`�揈��
    /// </summary>
    static void DrawAllObj();

    /// <summary>
    /// �I�u�W�F�N�g�폜����
    /// </summary>
    /// <param name="releaseObj">:�폜�I�u�W�F�N�g</param>
    static void DeleteObj(std::shared_ptr<ObjBase>& releaseObj);

    /// <summary>
    /// �S�I�u�W�F�N�g�폜����
    /// </summary>
    static void DeleteAllObj();

    /// <summary>
    /// �^�O�̐擪�I�u�W�F�N�g�擾
    /// </summary>
    /// <param name="tag">:�^�O</param>
    /// <returns>�I�u�W�F�N�g</returns>
    static ObjBase* GetFirstObj(ObjTag tag);

    /// <summary>
    /// �^�O�̎w��I�u�W�F�N�g�擾
    /// </summary>
    /// <param name="tag">:�^�O</param>
    /// <param name="tagNum">:�I�u�W�F�N�g�ԍ�</param>
    /// <returns>:�I�u�W�F�N�g</returns>
    static ObjBase* GetObj(ObjTag tag, int tagNum);

private:
    /// <summary>
    /// �R���X�g���N�^(�V���O���g��)
    /// </summary>
    ObjManager();

    /// <summary>
    /// �I�u�W�F�N�g���S����
    /// </summary>
    static void OnDeadObj();

    static std::unique_ptr<ObjManager> singleton;       //���g�̎���
    //std::vector<ObjBase*>holdObj;                     //�ꎞ�ۑ��I�u�W�F�N�g
    std::unordered_map<ObjTag, std::vector<
        std::shared_ptr<ObjBase>>> object;              //�I�u�W�F�N�g

    std::unique_ptr<class Bloom> bloom;                 //�u���[��
};