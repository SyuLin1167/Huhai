#pragma once
#include<DxLib.h>

#include"../../ObjectBase/ObjectBase.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/Model/Model.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Collision/Collision.h"

        /*Door�N���X*/
class Door :public ObjectBase
{
    ObjectBase* player;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Door();

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="doorPos">:�h�A�̃��[���h���W</param>
    /// <param name="doorAngle">:�h�A�̕���</param>
    Door(VECTOR doorPos, VECTOR doorAngle);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Door();

    /// <summary>
    /// �ǂݍ��ݏ���
    /// </summary>
    void Load();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// �A�j���[�V��������
    /// </summary>
    /// <param name="animtype">:�A�j���[�V�����^�C�v</param>
    void MoveAnim(int animtype);

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

    enum Anim
    {
        IDLE = 0,			//�ҋ@
        OPEN,			//�J
        CLOSE			//��
    };
private:
    //---�A�j���[�V�����֘A---//
    class Animation* doorAnim;			//�A�j���[�V����
    int animType;						//�A�j���[�V�������

    class Model* doorModel;

    class Sound* doorSound;
};
