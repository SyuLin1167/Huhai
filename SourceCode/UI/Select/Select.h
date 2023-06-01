#pragma once
#include<unordered_map>

#include"SelectType.h"
#include"../../Object/ObjectBase/ObjectBase.h"
#include"../../BlendMode/BlendMode.h"

using namespace std;

/*�Z���N�g�{�^���N���X*/
class Select:public ObjectBase
{
    class BlendMode* selectBlend;

public:
    /// <summary>
    /// Select�R���X�g���N�^
    /// </summary>
    Select(SelectType type);

    /// <summary>
    /// Select�f�X�g���N�^
    /// </summary>
    ~Select();

    /// <summary>
    /// Select�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Select�����蔻�菈��
    /// </summary>
    void OnCollisionEnter();

    /// <summary>
    /// �I���t���O�擾
    /// </summary>
    /// <returns>�I�����ꂽ���ǂ���</returns>
    bool GetSelect() { return isSelect; }

    /// <summary>
    /// Select�`�揈��
    /// </summary>
    void Draw()override;

private:
    int mouseX;                     //�}�E�X���WX
    int mouseY;                     //�}�E�X���WY
    bool isSelect;                  //�I�����ꂽ���ǂ���
    bool nowInput;                  //���͒����ǂ���

    //�`����W���i�[�����z��
    unordered_map<SelectType, VECTOR> drawPos{
        {SelectType::PLAY,{125,680,0}},
        {SelectType::LOAD,{125,760,0}},
        {SelectType::EXIT,{125,840,0}},
    };

    //�摜�n���h�����i�[�����z��
    unordered_map<SelectType, const char*> drawHandle{
        {SelectType::PLAY,"../Assets/BackGround/Play.png"},
        {SelectType::LOAD,"../Assets/BackGround/Load.png"},
        {SelectType::EXIT,"../Assets/BackGround/Exit.png"},
    };
};


