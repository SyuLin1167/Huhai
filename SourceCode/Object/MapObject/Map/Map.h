#pragma once
#include"../../ObjectBase/ObjectBase.h"

/*Map�N���X*/
class Map :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="maptag">:�}�b�v�^�O</param>
    Map(int tag);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Map();

    /// <summary>
    /// �ǂݍ��ݏ���
    /// </summary>
    void LoadModel();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

    //�}�b�v�^�O
    enum MapTag
    {
        TITLE = 0,
        ROOM,
        STAGE,
        ESCAPE,
        ESCAPEMAIN,
        GOAL,
    };

private:
    class Model* mapModel;      //���f��
    class Sound* mapSound;      //�T�E���h
    int mapTag;                 //�^�O
};
