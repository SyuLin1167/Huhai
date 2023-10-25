#pragma once
#include<unordered_map>

#include"SelectType.h"
#include"../../UI/UIBase/UIBase.h"

/// <summary>
/// �{�^���̑I��
/// </summary>
class Select :public UIBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="type">:�{�^���^�C�v</param>
    Select(SelectType type);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Select();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;

private:
    const int BUTTON_WIDTH = 160;
    const int BUTTON_HEIGHT = 50;

    //�`����W���i�[�����z��
    std::unordered_map<SelectType, VECTOR> drawPos{
        {SelectType::PLAY,{125,680,0}},
        {SelectType::LOAD,{125,760,0}},
        {SelectType::EXIT,{125,840,0}},
    };

    //�摜�n���h�����i�[�����z��
    std::unordered_map<SelectType, const char*> drawHandle{
        {SelectType::PLAY,"../Assets/BackGround/Play.png"},
        {SelectType::LOAD,"../Assets/BackGround/Load.png"},
        {SelectType::EXIT,"../Assets/BackGround/Exit.png"},
    };

    class BlendMode* selectBlend;    //�u�����h���[�h
};


