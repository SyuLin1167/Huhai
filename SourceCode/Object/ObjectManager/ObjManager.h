#pragma once
#include<vector>
#include<unordered_map>
#include<DxLib.h>

#include"../ObjectBase/ObjectBase.h"
#include"../ObjectBase/ObjectTag.h"

using namespace std;

/* �I�u�W�F�N�g�Ǘ��N���X */
class ObjManager final
{
public:
    /// <summary>
    /// ObjManager����������
    /// </summary>
    static void Init();

    /// <summary>
    /// �I�u�W�F�N�g�o�^
    /// </summary>
    /// <param name="newObj">:�ǉ�����I�u�W�F�N�g</param>
    static void Entry(ObjectBase* newObj);

    /// <summary>
    /// �I�u�W�F�N�g�폜
    /// </summary>
    /// <param name="releaseObj">:�폜����I�u�W�F�N�g</param>
    static void Release(ObjectBase* releaseObj);

    /// <summary>
    /// �S�I�u�W�F�N�g�폜
    /// </summary>
    static void ReleaceAllObj();

    /// <summary>
    /// �S�I�u�W�F�N�g�̍X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    static void Update(float deltaTime);

    /// <summary>
    /// �I�u�W�F�N�g�̐�����
    /// </summary>
    static void Dead();

    /// <summary>
    /// �S�I�u�W�F�N�g�̕`�揈��
    /// </summary>
    static void Draw();

    /// <summary>
    /// �����蔻�菈��
    /// </summary>
    static void Collision();

    /// <summary>
    /// �^�O��̍ŏ��̃I�u�W�F�N�g�擾
    /// </summary>
    /// <param name="tag">:�^�O</param>
    /// <returns>�^�O��̍ŏ��̃I�u�W�F�N�g</returns>
    static ObjectBase* GetFirstObj(ObjectTag tag);

    /// <summary>
    /// ObjManager�̉��
    /// </summary>
    static void Finalize();

private:
    /// <summary>
    /// ObjManager�R���X�g���N�^�[(�V���O���g��)
    /// </summary>
    ObjManager();

    /// <summary>
    /// ObjManager�f�X�g���N�^�[
    /// </summary>
    ~ObjManager();

    static ObjManager* objInstance;     //ObjManager�̎���
    vector<ObjectBase*>holdObj;         //�ꎞ�ҋ@�I�u�W�F�N�g
    unordered_map<ObjectTag, vector<ObjectBase*>>Object;          //Object[�^�O���][�I�u�W�F�N�g��]
};

