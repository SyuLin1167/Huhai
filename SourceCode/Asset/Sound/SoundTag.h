#pragma once

/*SoundTagクラス*/
enum class SoundTag :unsigned char
{
    Title,
    Start,
    Escape,
    GameOver,
    PlayerWalk,
    GhostScream,
    GhostWalk,
    DoorOpen,
    DoorClose,
    InDoor,
    ManHurt,
    BodyFall,
    MoveChair,
    FallingChair,
};

/*全サウンド*/
constexpr static SoundTag soundTagAll[] =
{
    SoundTag::Title,
    SoundTag::Start,
    SoundTag::Escape,
    SoundTag::GameOver,
    SoundTag::PlayerWalk,
    SoundTag::GhostScream,
    SoundTag::GhostWalk,
    SoundTag::DoorOpen,
    SoundTag::DoorClose,
    SoundTag::InDoor,
    SoundTag::ManHurt,
    SoundTag::BodyFall,
    SoundTag::MoveChair,
    SoundTag::FallingChair,
};