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
    /// �R���X�g���N�^
    /// </summary>
    Bed();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Bed();

    /// <summary>
    /// �ǂݍ��ݏ���
    /// </summary>
    void Load();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;
};
