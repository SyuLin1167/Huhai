#pragma once
#include"../../ObjectBase/ObjectBase.h"
#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Model/Model.h"

/*Map�N���X*/
class Map:public ObjectBase
{
public:
    /// <summary>
    /// Map�R���X�g���N�^
    /// </summary>
    /// <param name="maptag">:�}�b�v�^�O</param>
    Map(int maptag);

    /// <summary>
    /// Map�f�X�g���N�^�[
    /// </summary>
    ~Map();

    /// <summary>
    /// Map�ǂݍ��ݏ���
    /// </summary>
    void LoadModel();

    /// <summary>
    /// Map�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// Map�`�揈��
    /// </summary>
    void Draw()override;


    enum MapName
    {
        TITLE=0,
        ROOM,
        STAGE,
        ESCAPE,
        ESCAPEMAIN,
        GOAL,
    };

private:
    class Model* mapModel;
    int mapTag;
};

