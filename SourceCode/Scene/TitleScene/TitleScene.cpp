#include "TitleScene.h"

#include "../../Object/ObjectManager/ObjManager.h"
#include "../../Asset/AssetManager/AssetManager.h"
#include "../../Object/MapObject/Map/Map.h"
#include "../../Object/MapObject/Door/Door.h"
#include "../../Object/MapObject/Light/BlinkingLight/BlinkingLight.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/CharaObject/Camera/FixedCamera/FixedCamera.h"
#include "../../UI/Select/Select.h"
#include "../RoomScene/RoomScene.h"
#include "../SaveScene/SaveScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
    :SceneBase()
{
    //�^�C�g�����S����
    bgHandle = AssetManager::GetGraph("../Assets/BackGround/Title.png");
    bgX = TITLE_POS_X;
    bgY = TITLE_POS_Y;

    //�T�E���h����
    sound->AddSound("../Assets/Sound/TitleBgm.mp3", SoundTag::Title);
    sound->AddSound("../Assets/Sound/StartSE.mp3", SoundTag::Start);
    sound->StartSound(SoundTag::Title, DX_PLAYTYPE_LOOP);

    //�J��������
    ObjManager::AddObj(new FixedCamera);

    //�}�b�v����
    ObjManager::AddObj(new Map(Map::MapTag::TITLE));

    //�h�A����
    door = new Door("title");
    ObjManager::AddObj(door);

    //���C�g����
    ObjManager::AddObj(new BlinkingLight("title"));
    ObjManager::AddObj(new NomalLight("title", "1"));

    //�I���{�^������
    for (auto type : selectTypeAll)
    {
        select[type] = new Select(type);
    }

    //�O���t�쐬
    screenGraph = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
    //�摜�n���h���폜
    if (bgHandle)
    {
        DeleteGraph(bgHandle);
    }
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�f���^�^�C��</param>
/// <returns>���̃t���[���̃V�[��</returns>
SceneBase* TitleScene::UpdateScene(const float deltaTime)
{
    //�}�E�X�|�C���^�[�\��
    SetMouseDispFlag(TRUE);

    //�I�u�W�F�N�g�X�V
    ObjManager::UpdateAllObj(deltaTime);
    door->MoveAnim(Door::AnimType::OPEN);

    for (auto type : selectTypeAll)
    {
        select[type]->Update(deltaTime);

        //�{�^���I��������
        if (select[type]->GetButtonInput())
        {
            //�}�E�X���W����ʂ̒��S�ɂ��Ĕ�\���ɂ���
            SetMousePoint(SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT);
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
                    ObjManager::DeleteAllObj();

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

/// <summary>
/// �`�揈��
/// </summary>
void TitleScene::DrawScene()
{
    //�I�u�W�F�N�g�`��
    ObjManager::DrawAllObj();

    //�I���{�^���`��
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screenGraph);
    DrawExtendGraph(bgX, bgY, bgX + TITLE_SIZE_X, bgY + TITLE_SIZE_Y, bgHandle, true);
    for (auto type : selectTypeAll)
    {
        if (select[type])
        {
            select[type]->Draw();
        }
    }

    //�t�F�[�h����
    blendMode->Fade();
    DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK_SCREEN_COLOR, true);
    blendMode->NoBlend();
}
