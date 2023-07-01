#pragma once

#include<vector>
#include<unordered_map>

#include"../ObjectBase/ObjectBase.h"
#include"../ObjectBase/ObjectTag.h"

/* ObjManager�N���X */
class ObjManager final
{
public:
    /// <summary>
    /// ����������
    /// </summary>
    static void Init();

    /// <summary>
    /// �o�^
    /// </summary>
    /// <param name="newObj">:�ǉ��I�u�W�F�N�g</param>
    static void Entry(ObjBase* newObj);

    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="releaseObj">:�폜�I�u�W�F�N�g</param>
    static void Release(ObjBase* releaseObj);

    /// <summary>
    /// �S�폜
    /// </summary>
    static void ReleaseAllObj();

    /// <summary>
    /// �S�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    static void Update(float deltaTime);

    /// <summary>
    /// �S�`�揈��
    /// </summary>
    static void Draw();

    /// <summary>
    /// �����蔻�菈��
    /// </summary>
    static void Collision();

    /// <summary>
    /// �^�O�̐擪�I�u�W�F�N�g�擾
    /// </summary>
    /// <param name="tag">:�^�O</param>
    /// <returns>�I�u�W�F�N�g</returns>
    static ObjBase* GetFirstObj(ObjectTag tag);

    /// <summary>
    /// �^�O�̎w��I�u�W�F�N�g�擾
    /// </summary>
    /// <param name="tag">:�^�O</param>
    /// <param name="tagNum">:�I�u�W�F�N�g�ԍ�</param>
    /// <returns>:�I�u�W�F�N�g</returns>
    static ObjBase* GetObj(ObjectTag tag, int tagNum);

    /// <summary>
    /// �㏈��
    /// </summary>
    static void Finalize();

private:
    /// <summary>
    /// �R���X�g���N�^(�V���O���g��)
    /// </summary>
    ObjManager();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ObjManager();

    /// <summary>
    /// ���S����
    /// </summary>
    static void Dead();

    static ObjManager* objManager;                                  //���g�̎���
    std::vector<ObjBase*>holdObj;                                   //�ꎞ�ۑ��I�u�W�F�N�g
    std::unordered_map<ObjectTag, std::vector<ObjBase*>>Object;     //Object[�^�O���][�I�u�W�F�N�g��]

    class Bloom* bloom;                                             //�u���[��
};