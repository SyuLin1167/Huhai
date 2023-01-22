#pragma once
#include<DxLib.h>


#include"../ObjectManager/ObjManager.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../ObjectBase/ObjectBase.h"
#include"../../Asset/Animation/Animation.h"
#include"../../Collision/Collision.h"

class Animation;

/* Enemy�̃N���X */
class Enemy :public ObjectBase
{
public:
    /// <summary>
    /// Enemy�̃R���X�g���N�^�[
    /// </summary>
    Enemy();

    /// <summary>
    /// Enemy�̃f�X�g���N�^�[
    /// </summary>
    ~Enemy();

    /// <summary>
    /// Enemy�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Enemy�`�揈��
    /// </summary>
    void Draw()override;


    /// <summary>
    /// Enemy�Փˎ�����
    /// </summary>
    /// <param name="other">:�I�u�W�F�N�g</param>
    void OnCollisionEnter(const ObjectBase* other)override;


    /// <summary>
    /// �����蔻�苅�擾
    /// </summary>
    /// <returns>�����蔻�苅</returns>
    Sphere GetColSphere() { return colSphere; }

    /// <summary>
    /// �A�j���[�V�����X�e�[�^�X
    /// </summary>
    enum Anim
    {
        IDLE = 0,							//�ҋ@
        RUN,								//����
        ATACK								//�U��
    };
private:
    /// <summary>
    /// Enemy�ړ�����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Move(float deltaTime);

    //---�A�j���[�V�����֘A---//
    Animation* emyAnim;						//�A�j���[�V����
    int animType;							//�A�j���[�V�������

    //---�����蔻��֘A---//
    class Collision* emyCol;				//�R���W����
    Sphere colSphere;			//�����蔻�苅
};

