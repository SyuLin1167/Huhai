#pragma once
#include"../../ObjectBase/ObjectBase.h"

/*Furniture�N���X*/
class Furniture :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="furtag">:�Ƌ�^�O</param>
    Furniture(int furtag);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Furniture();

    /// <summary>
    /// �ǂݍ��ݏ���
    /// </summary>
    /// <param name="tag">:�^�O</param>
    void Load(int tag);

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

    enum FurName
    {
        Room = 0,
        Stage,
    };

private:
    class Model* furModel;
    class Model* furColModel;
};