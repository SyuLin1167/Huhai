#pragma once
#include<unordered_map>

#include"SelectType.h"
#include"../../Object/ObjectBase/ObjectBase.h"

/*SelectButton�N���X*/
class Select :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Select(SelectType type);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Select();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// �����蔻�菈��
    /// </summary>
    void Collision();

    /// <summary>
    /// ���͏���
    /// </summary>
    void Input();

    /// <summary>
    /// �I���t���O�擾
    /// </summary>
    /// <returns>�I�����ꂽ:true|����Ă��Ȃ�:false</returns>
    bool GetSelect() const { return isSelect; }

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

private:
    int mouseX;                      //�}�E�X���WX
    int mouseY;                      //�}�E�X���WY
    bool canSelect;                  //�I���\���
    bool isSelect;                   //�I�����
    bool hasInput;                   //���̓t���O

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

    class Wipe* selectBlend;    //�u�����h���[�h
};


