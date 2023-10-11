#include "Sound.h"

#include"../AssetManager/AssetManager.h"
#include"../../Object/ObjectManager/ObjManager.h"
#include"../../Scene/PauseMenu/PauseMenu.h"

// �R���X�g���N�^ //

Sound::Sound()
    :soundType(-1)
    , nowSoundTime(0.0f)
    , attachedIndex(0)
    , prevSoundPos(VGet(0,0,0))
    , prevListnerPos(VGet(0,0,0))
{
}

// �f�X�g���N�^ //

Sound::~Sound()
{
    //�T�E���h�폜
    for (auto tag : soundTagAll)
    {
        DeleteSoundMem(soundData[tag].handle);
    }
}

// �ǉ����� //

void Sound::AddSound(std::string fileName, SoundTag tag, bool isDim,bool volumeType)
{
    //�T�E���h�f�[�^�ݒ�
    SoundData sound = {};
    sound.volumeType = volumeType;
    sound.isDim = isDim;

    //�T�E���h�o�^&�擾
    SetCreate3DSoundFlag(sound.isDim);
    sound.handle = AssetManager::GetSound(fileName.c_str());

    //���g���󂾂����炻�̂܂ܕԂ�
    if (sound.handle == -1)
    {
        return ;
    }

    //�f�[�^�ǉ�
    soundData.emplace(tag, sound);
}

// �h�b�v���[���� //

void Sound::Doppler(SoundTag tag, VECTOR pos)
{
    //3�����T�E���h�̓J�����̋����ɍ��킹�ĉ��ʂ�ς���
    ObjBase* camera = ObjManager::GetFirstObj(ObjTag::Camera);
    auto& sound = soundData[tag];
    if (sound.isDim && IsPlaying(tag))
    {
        //�T�E���h�Ɋւ����W�ݒ�
        if (camera)
        {
            Set3DPositionSoundMem(pos, sound.handle);
            Set3DSoundListenerPosAndFrontPos_UpVecY(camera->GetPos(), camera->GetPos() + camera->GetDir());

            //�ړ����x�Z�o
            VECTOR soundVel = VScale(VSub(pos, prevSoundPos), 60.0f);
            Set3DVelocitySoundMem(soundVel, sound.handle);
            VECTOR listnerVel = VScale(VSub(camera->GetPos(), prevListnerPos), 60.0f);
            Set3DSoundListenerVelocity(listnerVel);

            //�ߋ��̍��W�ɑ��
            prevSoundPos = pos;
            prevListnerPos = camera->GetPos();
        };

    }
}

// �Đ����� //

void Sound::StartSound(SoundTag tag, int playType)
{
    //�Đ�����Ă��Ȃ�������T�E���h�Đ�
    auto& sound = soundData[tag];
    if (!CheckSoundMem(sound.handle))
    {
        //�T�E���h�̗L���͈͐ݒ�
        if (sound.isDim)
        {
            Set3DRadiusSoundMem(500.0f, sound.handle);
        }

        if (sound.volumeType)
        {
            sound.volume = PauseMenu::Parameter("SE");
        }
        else
        {
            sound.volume = PauseMenu::Parameter("Bgm");
        }

        ChangeVolumeSoundMem(sound.volume, sound.handle);

        PlaySoundMem(sound.handle, playType);
    }
}

// ��x�����Đ����� //

void Sound::StartSoundOnce(SoundTag tag, int playType)
{
    //�Đ�����Ă��Ȃ�������T�E���h�Đ�
    auto& sound = soundData[tag];
    if (sound.playOnce)
    {
        StartSound(tag, playType);
        sound.playOnce = false;
    }
}

// ��~���� //

void Sound::StopSound(SoundTag tag)
{
    //�T�E���h���Đ�����Ă������~
    auto& sound = soundData[tag];
    if (CheckSoundMem(sound.handle))
    {
        StopSoundMem(sound.handle);
    }
}

// �S�T�E���h��~���� //

void Sound::StopAllSound()
{
    //���ׂẴT�E���h�ɒ�~����������
    for (auto& tag : soundTagAll)
    {
        StopSound(tag);
    }
}

// �Đ���� //

bool Sound::IsPlaying(SoundTag tag)
{
    //�Đ�����Ă�����Đ����ɂ���
    auto& sound = soundData[tag];
    if (CheckSoundMem(sound.handle))
    {
        return true;
    }
    else
    {
        //����Ă��Ȃ��������~���ɂ���
        return false;
    }
}

// �R���X�g���N�^ //

Sound::SoundData::SoundData()
    :handle(-1)
    , volume(150)
    , volumeType(false)
    , isDim(false)
    , playOnce(true)
{
}