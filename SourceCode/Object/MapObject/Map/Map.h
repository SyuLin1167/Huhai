#pragma once
#include<unordered_map>
#include<string>
#include<memory>

#include"../../ObjectBase/ObjBase.h"

/// <summary>
/// �}�b�v�I�u�W�F�N�g
/// </summary>
class Map :public ObjBase
{
public:
    /// <summary>
    /// �}�b�v�^�O
    /// </summary>
    enum MapTag
    {
        TITLE = 0,
        ROOM,
        STAGE,
        ESCAPE,
        ESCAPEMAIN,
        GOAL,
    };

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="maptag">:�}�b�v�^�O</param>
    Map(MapTag tag);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Map();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;


private:
    std::unique_ptr<class Sound> mapSound;      //�T�E���h
    MapTag mapTag;                 //�^�O

    //�}�b�v�t�@�C���f�[�^
    std::unordered_map<MapTag, std::string> mapFile
    {
        {MapTag::TITLE,"../Assets/Map/Stage/Title.mv1"},
        {MapTag::ROOM,"../Assets/Map/Room/Room.mv1"},
        {MapTag::STAGE,"../Assets/Map/Stage/Stage.mv1"},
        {MapTag::ESCAPE,"../Assets/Map/Stage/Escape.mv1"},
        {MapTag::ESCAPEMAIN,"../Assets/Map/Stage/EscapeMain.mv1"},
        {MapTag::GOAL,"../Assets/Map/Stage/GoalRoom.mv1"},
    };

    //�����蔻��t�@�C���f�[�^
    std::unordered_map<MapTag, std::string> mapColFile
    {
        {MapTag::ROOM,"../Assets/Map/Room/Room.mv1"},
        {MapTag::STAGE,"../Assets/Map/Stage/StageCol.mv1"},
        {MapTag::ESCAPE,"../Assets/Map/Stage/EscapeCol.mv1"},
        {MapTag::GOAL,"../Assets/Map/Stage/GoalRoom.mv1"},
    };
};
