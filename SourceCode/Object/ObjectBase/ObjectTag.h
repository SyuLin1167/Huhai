#pragma once
#include<vector>

/*��ޕʃ^�O�N���X*/
enum class ObjectTag :unsigned char
{
    Camera,     //�J����
    Player,     //�v���C���[
    Enemy,      //�G�l�~�[
};

/*���[�v����p*/
constexpr static ObjectTag ObjTagAll[] =
{
    ObjectTag::Camera,
    ObjectTag::Player,
    ObjectTag::Enemy,
};

