#include "Title.h"

#include "../RoomScene/Room.h"
#include"../../Object/CharaObject/Camera/CameraFps.h"
#include"../../Object/MapObject/Door/Door.h"
#include"../../Object/MapObject/Light/BlinkingLight/BlinkingLight.h"
#include"../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Map/Map.h"
#include"../../UI/Select/Select.h"
#include"../ResultScene/Result.h"

// @brief TitleScene�R���X�g���N�^�[ //

Title::Title()
    :SceneBase()
    ,fadeLock(true)
    ,titleBlend(nullptr)
{
    ObjManager::Init();
    AssetManager::Init();

    BgX = 180;
    BgY = 150;
    BgHandle = LoadGraph("../Assets/BackGround/Title.png");

    ////---�}�b�v�𐶐�---//
    ObjManager::Entry(new Map(Map::MapName::TITLE));

    door = new Door(VGet(0, 0, 66), VGet(0, 0, 0));
    ObjManager::Entry(door);

    ObjManager::Entry(new BlinkingLight(VGet(-35, 32, 70)));
    ObjManager::Entry(new NomalLight(VGet(80, 32, 65)));

    for (auto type : selectTypeAll)
    {
        select[type] = new Select(type);
    }

    titleBlend = new BlendMode;
    SetCameraNearFar(CameraNear, CameraFar);                                    //�J�����̕`��͈͐ݒ�

    graph = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetMouseDispFlag(TRUE);
}

// @brief TitleScene�f�X�g���N�^�[ //

Title::~Title()
{
    if (BgHandle != -1)
    {
        DeleteGraph(BgHandle);
    }
}

// @brief TitleScene�X�V���� //

SceneBase* Title::Update(float deltaTime)
{
    door->MoveAnim(Door::Anim::OPEN);
    ObjManager::Update(deltaTime);
    for (auto type : selectTypeAll)
    {
        select[type]->Update(deltaTime);
    if (select[type]->GetSelect())
    {
        SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        SetMouseDispFlag(FALSE);                                                    //�}�E�X�͔�\��
        titleBlend->AddFade();
        if (!titleBlend->NowFade())
        {
            AssetManager::ReleaseAllAsset();            //�S�ẴA�Z�b�g�̊J��
            ObjManager::ReleaseAllObj();                //�S�ẴI�u�W�F�N�g�̊J��
            if (type == PLAY)
            {
                return new Room;
            }
            if (type == LOAD)
            {
                return new Result;
            }
            if (type == EXIT)
            {
                return nullptr;
            }
        }
    }
    }
    
    SetCameraPositionAndTarget_UpVecY(VGet(70, 6, 75), VGet(-10, 10, 25));         //�����_�Ɍ����ăJ�������Z�b�g

    return this;
}

// @brief TitleScene�`�揈�� //

void Title::Draw()
{
    ObjManager::Draw();
    GetDrawScreenGraph(0, 0, 1920, 1080, graph);
    DrawExtendGraph(BgX, BgY, BgX + 450, BgY+200, BgHandle, TRUE);
    for (auto type : selectTypeAll)
    {
        select[type]->Draw();
    }
    titleBlend->Fade();
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
    titleBlend->NoBlend();
}
