#pragma once
#include<memory>

#include"../../ObjectBase/ObjBase.h"

/// <summary>
/// Man�N���X
/// </summary>
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

    /// <summary>
    /// �A�j���[�V�����^�C�v
    /// </summary>
    enum Anim
    {
        CRYING = 0,         //����
        DEAD,               //���S
    };

private:
    const float ROTATE_VELOCITY = 5.0f;             //��]���x
    bool isSpeak;                                   //��b���

    std::unique_ptr<class Animation> manAnim;       //�A�j���[�V����
    int animType;                                   //�A�j���[�V�����^�C�v

    std::unique_ptr<class Sound> manSound;          //�T�E���h
};
