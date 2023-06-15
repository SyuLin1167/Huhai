#pragma once
#include"../../ObjectBase/ObjectBase.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Model/Model.h"

        /*Furniture�N���X*/
class Furniture :public ObjectBase
{
public:
    /// <summary>
    /// Furniture�R���X�g���N�^�[
    /// </summary>
    /// <param name="furtag">:�Ƌ�^�O</param>
    Furniture(int furtag);

    /// <summary>
    /// Furniture�f�X�g���N�^�[
    /// </summary>
    ~Furniture();

    /// <summary>
    /// Furniture���f���ǂݍ��ݏ���
    /// </summary>
    /// <param name="furtag">:�Ƌ�^�O</param>
    void LoadModel(int furtag);

    /// <summary>
    /// Furniture�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// Furniture�`�揈��
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