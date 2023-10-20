#pragma once
#include<memory>

#include"../../ObjectBase/ObjBase.h"

/// <summary>
/// Chair�N���X
/// </summary>
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
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;

    //�A�j���[�V�����^�C�v
    enum Anim
    {
        IDLE = 0,           //�ҋ@
        MOVE,               //����
    };

private:
    std::unique_ptr<class Animation> chairAnim;         //�A�j���[�V����
    int animType;                       //�A�j���[�V�������

    std::unique_ptr<class Sound> chairSound;            //�T�E���h
};

