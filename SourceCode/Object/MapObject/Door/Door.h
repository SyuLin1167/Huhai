#pragma once
#include<DxLib.h>

#include"../../ObjectBase/ObjectBase.h"

/*Door�N���X*/
class Door :public ObjBase
{
public:
    //�A�j���[�V�����^�C�v
    enum AnimType
    {
        IDLE = 0,       //�ҋ@
        OPEN,           //�J
        CLOSE           //��
    };

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="scene">:�V�[����</param>
    /// <param name="num">:�I�u�W�F�N�g�ԍ�</param>
    Door(std::string scene, std::string num = "0");

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Door();

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

private:
    class Animation* doorAnim;			//�A�j���[�V����
    int animType;						//�A�j���[�V�����^�C�v

    bool rotateNow;                     //��]���
    VECTOR aimDir;                      //�ڕW����

    class Sound* doorSound;             //�T�E���h

    class ObjBase* player;              //�v���C���[�I�u�W�F�N�g
    class Action* action;               //�A�N�V�����{�^��
};
