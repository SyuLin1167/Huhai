#pragma once
#include<DxLib.h>

#include"../../ObjectBase/ObjectBase.h"

/*Door�N���X*/
class Door :public ObjBase
{
    ObjBase* player;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Door();

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pos">:���[���h���W</param>
    /// <param name="dir">:����</param>
    Door(VECTOR pos, VECTOR dir);

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

    //�A�j���[�V�����^�C�v
    enum Anim
    {
        IDLE = 0,       //�ҋ@
        OPEN,           //�J
        CLOSE           //��
    };

private:
    class Animation* doorAnim;			//�A�j���[�V����
    int animType;						//�A�j���[�V�����^�C�v

    bool rotateNow;                     //��]���
    VECTOR aimDir;                      //�ڕW����

    class Sound* doorSound;             //�T�E���h
};
