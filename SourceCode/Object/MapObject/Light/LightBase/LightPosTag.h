#pragma once

/*種類別タグクラス*/
enum class LightPosTag :unsigned char
{
    StartRoom = 0,
    Room1, 
    Room2,
    Corridor,
};

/*ループ制御用*/
constexpr static LightPosTag LightPosTagAll[] =
{
    LightPosTag::StartRoom,
    LightPosTag::Room1,
    LightPosTag::Room2,
    LightPosTag::Corridor,
};