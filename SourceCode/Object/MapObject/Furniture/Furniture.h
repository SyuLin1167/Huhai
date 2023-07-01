#pragma once

#include<unordered_map>
#include<string>

#include"../../ObjectBase/ObjectBase.h"

/*Furniture�N���X*/
class Furniture :public ObjBase
{
public:
    //�Ƌ�^�O
    enum FurName
    {
        Room = 0,
        Stage,
    };

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="tag">:�^�O</param>
    Furniture(FurName tag);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Furniture();

    /// <summary>
    /// �ǂݍ��ݏ���
    /// </summary>
    /// <param name="tag">:�^�O</param>
    void Load(FurName tag);

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

private:
    //�Ƌ�f���t�@�C���f�[�^
    std::unordered_map<FurName, std::string> furModel
    {
        {FurName::Room,"../Assets/Map/Furniture/RoomFur.mv1"},
        {FurName::Stage,"../Assets/Map/Furniture/StageFur.mv1"},
    };

    //�Ƌ���蔻��t�@�C���f�[�^
    std::unordered_map<FurName, std::string> furColModel
    {
        {FurName::Room,"../Assets/Map/Furniture/RoomFurCol.mv1"},
        {FurName::Stage,"../Assets/Map/Furniture/StageFurCol.mv1"},
    };
};