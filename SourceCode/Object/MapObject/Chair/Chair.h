#pragma once

#include"../../ObjectBase/ObjBase.h"

/*Chair�N���X*/
class Chair :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Chair();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Chair();

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
    /// �`�揈��
    /// </summary>
    void Draw()override;

    //�A�j���[�V�����^�C�v
    enum Anim
    {
        IDLE = 0,			//�ҋ@
        MOVE,               //����
    };

private:
    class Animation* ChairAnim;			//�A�j���[�V����
    int animType;						//�A�j���[�V�������

    class Sound* chairSound;            //�T�E���h
};

