#include "Title.h"

#include "../../Object/ObjectManager/ObjManager.h"
#include "../../Asset/AssetManager/AssetManager.h"
#include "../../BlendMode/BlendMode.h"
#include "../../Asset/Sound/Sound.h"
#include "../../Object/CharaObject/Camera/CameraFps.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Light/BlinkingLight/BlinkingLight.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../RoomScene/Room.h"
#include "../EscapeScene/Escape.h"
#include "../Save/Save.h"

// �R���X�g���N�^ //

Title::Title()
    :SceneBase()
    ,screenGraph(-1)
{
    //�^�C�g�����S����
    BgHandle = LoadGraph("../Assets/BackGround/Title.png");
    BgX = 180;
    BgY = 150;

    //�u�����h���[�h����
    titleBlend = new BlendMode;

    //�T�E���h����
    titleSound = new Sound;
    titleSound->AddSound("../Assets/Sound/TitleBgm.mp3", SoundTag::Title, 150);
    titleSound->AddSound("../Assets/Sound/StartSE.mp3", SoundTag::Start, 150);
    titleSound->StartSound(SoundTag::Title, DX_PLAYTYPE_LOOP);

    //�J��������
    ObjManager::Entry(new CameraFps);

    //�}�b�v����
    ObjManager::Entry(new Map(Map::MapTag::TITLE));

    //�h�A����
    door = new Door(VGet(0, 0, 66), VGet(0, 0, 0));
    ObjManager::Entry(door);

    //���C�g����
    ObjManager::Entry(new BlinkingLight(VGet(-35, 32, 70)));
    ObjManager::Entry(new NomalLight(VGet(80, 32, 65)));

    //�I���{�^������
    for (auto type : selectTypeAll)
    {
        select[type] = new Select(type);
    }

    //�O���t�쐬
    screenGraph = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);

    //�}�E�X�|�C���^�[�\��
    SetMouseDispFlag(TRUE);
}

// �f�X�g���N�^ //

Title::~Title()
{
    //�摜�n���h���폜
    if (BgHandle)
    {
        DeleteGraph(BgHandle);
    }
}

// �X�V���� //

SceneBase* Title::Update(float deltaTime)
{
    //�h�A�͊J����Ԃɂ���
    door->MoveAnim(Door::Anim::OPEN);

    //�I�u�W�F�N�g�X�V
    ObjManager::Update(deltaTime);
    for (auto type : selectTypeAll)
    {
        select[type]->Update(deltaTime);

        //�{�^���I��������
        if (select[type]->GetSelect())
        {
            //�}�E�X���W����ʂ̒��S�ɂ��Ĕ�\���ɂ���
            SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            SetMouseDispFlag(FALSE);

            //�t�F�[�h�A�E�g
            titleBlend->AddFade(deltaTime);

            if (type == EXIT)
            {
                //EXIT�I�����A�V�[����nullptr�ɂ���
                return nullptr;
            }
            else
            {
                //EXIT�ȊO�I�����ASE���Đ�
                titleSound->StartSoundOnce(SoundTag::Start, DX_PLAYTYPE_BACK);
            }

            //�V�[���ڍs���̉��o���I�������
            if (!titleSound->IsPlaying(SoundTag::Start))
            {
                if (!titleBlend->NowFade())
                {
                    //���ׂẴT�E���h���~�߂�
                    titleSound->StopAllSound();

                    //�Ǘ��N���X���̊m�ۂ����f�[�^���
                    AssetManager::ReleaseAllAsset();
                    ObjManager::ReleaseAllObj();

                    if (type == PLAY)
                    {
                        //PLAY�I�����A�V�[�������̏�ʂɂ���
                        return new Room;
                    }
                    if (type == LOAD)
                    {
                        //LOAD�I�����A�V�[����ۑ��V�[���ɂ���
                        if (!SaveScene::Load())
                        {
                            SaveScene::Save(new Room);
                        }
                        return SaveScene::Load();
                    }
                }
            }
        }
    }

    //�J�����ݒ�(���FixedCamera�N���X���쐬���āA�����ōs��)
    ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
    if (camera)
    {
        camera->SetPos(VGet(70, 6, 75));
        camera->SetDir(VGet(-1.0f, 0.1f, -0.7f));
    }


    //SetCameraPositionAndTarget_UpVecY(VGet(70, 6, 75), VGet(-10, 10, 25));         //�����_�Ɍ����ăJ�������Z�b�g

    return this;
}

// �`�揈�� //

void Title::Draw()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();

    //�I���{�^���`��
    GetDrawScreenGraph(0, 0, 1920, 1080, screenGraph);
    DrawExtendGraph(BgX, BgY, BgX + 450, BgY + 200, BgHandle, TRUE);
    for (auto type : selectTypeAll)
    {
        select[type]->Draw();
    }

    //�t�F�[�h����
    titleBlend->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    titleBlend->NoBlend();
}
