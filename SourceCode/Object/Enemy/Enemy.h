#pragma once
#include<DxLib.h>


#include"../ObjectBase/ObjectBase.h"
#include"../../Asset/AssetManager/AssetManager.h"
#include"../../Collision/Collision.h"

/* Enemy�̃N���X */
class Enemy :public ObjectBase
{
public:
    /// <summary>
    /// Enemy�̃R���X�g���N�^�[
    /// </summary>
    Enemy();

    /// <summary>
    /// Enemy�̃f�X�g���N�^�[
    /// </summary>
    ~Enemy();

    /// <summary>
    /// Enemy�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime);

    /// <summary>
    /// Enemy�`�揈��
    /// </summary>
    void Draw();

    /// <summary>
    /// �����蔻�苅�擾
    /// </summary>
    /// <returns>�����蔻�苅</returns>
    Sphere GetColSphere() { return colSphere; }

private:

    Sphere colSphere;			//�����蔻�苅
};

