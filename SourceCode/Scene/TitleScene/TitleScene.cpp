#include "TitleScene.h"

#include "../../Object/ObjectManager/ObjManager.h"
#include "../../Asset/AssetManager/AssetManager.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Light/BlinkingLight/BlinkingLight.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/CharaObject/Camera/FixedCamera/FixedCamera.h"
#include "../RoomScene/RoomScene.h"
#include "../SaveScene/SaveScene.h"

// �R���X�g���N�^ //

TitleScene::TitleScene()
    :SceneBase()
{
    //�^�C�g�����S����
    BgHandle = AssetManager::GetGraph("../Assets/BackGround/Title.png");
    BgX = TITLE_POS_X;
    BgY = TITLE_POS_Y;

    //�T�E���h����
    sound->AddSound("../Assets/Sound/TitleBgm.mp3", SoundTag::Title);
    sound->AddSound("../Assets/Sound/StartSE.mp3", SoundTag::Start);
    sound->StartSound(SoundTag::Title, DX_PLAYTYPE_LOOP);

    //�J��������
    ObjManager::Entry(new FixedCamera);

    //�}�b�v����
    ObjManager::Entry(new Map(Map::MapTag::TITLE));

    //�h�A����
    door = new Door(VGet(0, 0, 66), VGet(-1, 0, 0));
    ObjManager::Entry(door);
    door->MoveAnim(Door::AnimType::OPEN);

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

SceneBase* TitleScene::UpdateScene(const float deltaTime)
{
    //�}�E�X�|�C���^�[�\��
    SetMouseDispFlag(TRUE);

    //�I�u�W�F�N�g�X�V
    ObjManager::Update(deltaTime);
    for (auto type : selectTypeAll)
    {
        select[type]->Update(deltaTime);

        //�{�^���I��������
        if (select[type]->GetButtonInput())
        {
            //�}�E�X���W����ʂ̒��S�ɂ��Ĕ�\���ɂ���
            SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            SetMouseDispFlag(false);

            //�t�F�[�h�A�E�g
            blendMode->AddFade(deltaTime);

            //EXIT�I�����A�V�[����nullptr�ɂ���
            if (type == EXIT)
            {
                return nullptr;
            }
            else
            {
                //EXIT�ȊO�I�����ASE���Đ�
                sound->StartSoundOnce(SoundTag::Start, DX_PLAYTYPE_BACK);
            }

            //�V�[���ڍs���̉��o���I�������
            if (!sound->IsPlaying(SoundTag::Start))
            {
                if (!blendMode->NowFade())
                {
                    //���ׂẴT�E���h���~�߂�
                    sound->StopAllSound();

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

void TitleScene::DrawScene()
{
    //�I�u�W�F�N�g�`��
    ObjManager::Draw();

    //�I���{�^���`��
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screenGraph);
    DrawExtendGraph(BgX, BgY, BgX + TITLE_SIZE_X, BgY + TITLE_SIZE_Y, BgHandle, true);
    for (auto type : selectTypeAll)
    {
        if (select[type])
        {
            select[type]->Draw();
        }
    }

    //�t�F�[�h����
    blendMode->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    blendMode->NoBlend();
}
