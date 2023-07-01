#pragma once

/*�I�u�W�F�N�g�^�O*/
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
    Remarks,    //�Z���t
};

/*�S�^�O*/
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
    ObjectTag::Remarks,
};

