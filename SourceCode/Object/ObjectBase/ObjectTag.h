#pragma once
#include<vector>

/*��ޕʃ^�O�N���X*/
enum class ObjectTag :unsigned char
{
    Camera,     //�J����
    Map,        //�}�b�v
    Furniture,  //�Ƌ�
    Light,      //�Ɩ�
    Player,     //�v���C���[
    Ghost,      //�G�l�~�[
    Man,        //�j��
    UI,         //UI
};

/*���[�v����p*/
constexpr static ObjectTag ObjTagAll[] =
{
    ObjectTag::Camera,
    ObjectTag::Map,
    ObjectTag::Furniture,
    ObjectTag::Light,
    ObjectTag::Player,
    ObjectTag::Ghost,
    ObjectTag::Man,
    ObjectTag::UI,
};

