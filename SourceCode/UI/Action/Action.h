#pragma once
#include"../../Object/ObjectBase/ObjectBase.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../BlendMode/BlendMode.h"

constexpr float actionRange = 30.0f;

        /*�A�N�V�����{�^���N���X*/
class Action :public ObjectBase
{
    class BlendMode* actionBlend;
public:
    /// <summary>
    /// Action�R���X�g���N�^
    /// </summary>
    /// <param name="objpos">:�`����W</param>
    Action(VECTOR objpos);

    /// <summary>
    /// Action�f�X�g���N�^
    /// </summary>
    ~Action();

    /// <summary>
    /// Action�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Action�`�揈��
    /// </summary>
    void Draw()override;

    /// <summary>
    /// �A�N�V���������ǂ���
    /// </summary>
    /// <returns>�A�N�V���������ǂ���</returns>
    bool IsAction() { return isAction; }

private:
    float objDistance;      //�I�u�W�F�N�g�Ƃ̋���
    bool canAction;         //�A�N�V�����\���ǂ���
    bool isAction;          //�A�N�V���������ǂ���
};
