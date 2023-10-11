#pragma once

#include"../../ObjectBase/ObjBase.h"

/*Man�N���X*/
class Man :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Man();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Man();

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
        CRYING = 0,         //����
        DEAD,               //���S
    };

private:

    class Animation* manAnim;               //�A�j���[�V����
    int animType;                           //�A�j���[�V�����^�C�v


    const float ROTATE_VELOCITY = 5.0f;     //��]���x

    bool isSpeak;                           //��b���

    class Sound* manSound;                  //�T�E���h
};
