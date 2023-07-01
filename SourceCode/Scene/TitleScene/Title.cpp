#include "Title.h"

#include "../../Object/ObjectManager/ObjManager.h"
#include "../../Asset/AssetManager/AssetManager.h"
#include "../../BlendMode/Wipe.h"
#include "../../Asset/Sound/Sound.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Light/BlinkingLight/BlinkingLight.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/CharaObject/Camera/FixedCamera/FixedCamera.h"
#include "../RoomScene/Room.h"
#include "../EscapeScene/Escape.h"
#include "../Save/Save.h"

// �R���X�g���N�^ //

TitleScene::TitleScene()
    :SceneBase()
    ,screenGraph(-1)
{
    //�^�C�g�����S����
    BgHandle = LoadGraph("../Assets/BackGround/Title.png");
    BgX = 180;
    BgY = 150;

    //�u�����h���[�h����
    titleBlend = new Wipe;

    //�T�E���h����
    titleSound = new Sound;
    titleSound->AddSound("../Assets/Sound/TitleBgm.mp3", SoundTag::Title);
    titleSound->AddSound("../Assets/Sound/StartSE.mp3", SoundTag::Start);
    titleSound->StartSound(SoundTag::Title, DX_PLAYTYPE_LOOP);

    //�J��������
    ObjManager::Entry(new FixedCamera);

    //�}�b�v����
    ObjManager::Entry(new Map(Map::MapTag::TITLE));

    //�h�A����
    door = new Door(VGet(0, 0, 66), VGet(0, 0, 0));
    ObjManager::Entry(door);

    //���C�g����
    ObjManager::Entry(new BlinkingLight(VGet(-35, 33, 70)));
    ObjManager::Entry(new NomalLight(VGet(65, 33, 65)));

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

TitleScene::~TitleScene()
{
    //�摜�n���h���폜
    if (BgHandle)
    {
        DeleteGraph(BgHandle);
    }
}

// �X�V���� //

SceneBase* TitleScene::Update(float deltaTime)
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
                        return new RoomScene;
                    }
                    if (type == LOAD)
                    {
                        //LOAD�I�����A�V�[����ۑ��V�[���ɂ���
                        return SaveScene::Load();
                    }
                }
            }
        }
    }

    return this;
}

// �`�揈�� //

void TitleScene::Draw()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();

    //�I���{�^���`��
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screenGraph);
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
