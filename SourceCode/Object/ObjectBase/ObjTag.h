#pragma once

/*�I�u�W�F�N�g�^�O*/
enum class ObjTag :unsigned char
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
constexpr static ObjTag ObjTagAll[] =
{
    ObjTag::Camera,
    ObjTag::Map,
    ObjTag::Furniture,
    ObjTag::Light,
    ObjTag::Player,
    ObjTag::Ghost,
    ObjTag::Man,
    ObjTag::UI,
    ObjTag::Remarks,
};

