#pragma once
#include<vector>

/*��ޕʃ^�O�N���X*/
enum class ObjectTag :unsigned char
{
    Camera,     //�J����
    Block,      //�u���b�N
    Map,        //�}�b�v
    Player,     //�v���C���[
    Enemy,      //�G�l�~�[
};

/*���[�v����p*/
constexpr static ObjectTag ObjTagAll[] =
{
    ObjectTag::Camera,
    ObjectTag::Map,
    ObjectTag::Block,
    ObjectTag::Player,
    ObjectTag::Enemy,
};

