#pragma once
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectBase/ObjectBase.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Scene/TitleScene/Title.h"

/*Bed�N���X*/
class Bed :public ObjectBase
{
public:
    /// <summary>
    /// Bed�R���X�g���N�^
    /// </summary>
    Bed();

    /// <summary>
    /// Bed�f�X�g���N�^
    /// </summary>
    ~Bed();

    /// <summary>
    /// Bed�ǂݍ��ݏ���
    /// </summary>
    void Load();

    /// <summary>
    /// Bed�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Bed�`�揈��
    /// </summary>
    void Draw()override;
};

