#pragma once
#include<map>

#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../ObjectBase/ObjectBase.h"
#include"../../../Collision/Collision.h"

constexpr int TableNum = 19;

        /*Table�N���X*/
class Table :public ObjectBase
{
public:
    /// <summary>
    /// Table�R���X�g���N�^
    /// </summary>
    /// <param name="objNum">:�I�u�W�F�N�g�ԍ�</param>
    Table(int objNum);

    /// <summary>
    /// Table�f�X�g���N�^
    /// </summary>
    ~Table();

    /// <summary>
    /// Table�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// Table�`�揈��
    /// </summary>
    void Draw()override;

private:
    //���W�f�[�^
    std::map<int, VECTOR> posData
    {
        {0,{215,0,7}},{1,{220,0,-22}},{2,{250,0,-10}},
        {3,{240,0,18}},{4,{285,0,-15}},{5,{320,0,22}},
        {6,{340,0,-8}},{7,{400,0,10}},{8,{440,0,-10}},
        {9,{480,0,10}},{10,{520,0,0}},{11,{520,0,-22}},
        {12,{520,0,22}},{13,{550,0,-11}},{14,{560,0,13}},
        {15,{600,0,17}},{16,{610,0,-11}},{17,{640,0,-17}},
        {18,{635,0,11}},
    };

    //�����f�[�^
    std::map<int, float> dirData
    {
        {0,0.0f},{1,90.0f},{2,0.0f},
        {3,-75.0f},{4,0.0f},{5,90.0f},
        {6,90.0f},{7,0.0f},{8,0.0f},
        {9,0.0f},{10,90.0f},{11,90.0f},
        {12,90.0f},{13,35.0f},{14,90.0f},
        {15,0.0f},{16,-65.0f},{17,0.0f},
        {18,-65.0f},
    };
};

