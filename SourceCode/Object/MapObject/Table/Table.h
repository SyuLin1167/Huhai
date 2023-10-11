#pragma once
#include<map>

#include"../../ObjectBase/ObjBase.h"

constexpr int TableNum = 19;

/*Table�N���X*/
class Table :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="objNum">:�I�u�W�F�N�g�ԍ�</param>
    Table(const int objNum);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Table();

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

