#pragma once
#include<string>

#include"../../Status/Base/StatusBase.h"

/// <summary>
/// Button�N���X
/// </summary>
class Button:public StatusBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name">:�{�^����</param>
    /// <param name="num">:�{�^���ԍ�</param>
    Button(std::string name,int num);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Button();

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
    const int BUTTON_SIZE = 45;                         //�{�^���T�C�Y
};

