#pragma once

/*��ޕʃ^�O�N���X*/
enum class LightPosTag :unsigned char
{
    StartRoom = 0,
    Room1, 
    Room2,
    Corridor,
};

/*���[�v����p*/
constexpr static LightPosTag LightPosTagAll[] =
{
    LightPosTag::StartRoom,
    LightPosTag::Room1,
    LightPosTag::Room2,
    LightPosTag::Corridor,
};