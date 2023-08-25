#pragma once
#include<string>

#include"../Base/SetUpBase.h"

/*TitleButton�N���X*/
class TitleButton :public SetUpBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="num">:�{�^���ԍ�</param>
    TitleButton(int num);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~TitleButton();

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
    /// ���̓��Z�b�g
    /// </summary>
    void ChangeToFalse() { isInput = false; }
private:
    const int TITLE_BUTTON_WIDTH = 270;         //�^�C�g���{�^����
    const int TITLE_BUTTON_HEIGHT = 45;         //�^�C�g���{�^������

    class Blend* titleButtonBlend;                    //�u�����h���[�h
};
