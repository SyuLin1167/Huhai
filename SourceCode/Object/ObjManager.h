#pragma once
#include<vector>
#include<map>
#include<DxLib.h>

#include"ObjectBase.h"
#include"ObjectTag.h"

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
    vector<ObjectBase*>Object;          //Object[�^�O���][�I�u�W�F�N�g��]
};

