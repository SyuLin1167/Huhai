#include "Result.h"
#include "../TitleScene/Title.h"
#include "../../UI/Reamarks/Remarks.h"
#include "../../Object/MapObject/Map/Map.h"
#include"../../Object/MapObject/Bed/Bed.h"
#include "../../Object/MapObject/Light/NomalLight/NomalLight.h"
#include "../../Object/MapObject/Furniture/Furniture.h"

    // @brief ResultScene�R���X�g���N�^�[ //

Result::Result()
    :SceneBase()
{
    ObjManager::Entry(new Remarks(TextType::GameClear));

    SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 20.0f, 0.0f), VGet(30.0f, 10.0f, 0.0f));
}

    // @brief ResultScene�f�X�g���N�^�[ //

Result::~Result()
{
    if (BgHandle != -1)
    {
        DeleteGraph(BgHandle);
    }
}

    // @brief ResultScene�X�V���� //

SceneBase* Result::Update(float deltaTime)
{
    ObjManager::Update(deltaTime);
    if (!ObjManager::GetFirstObj(ObjectTag::Remarks))
    {
        AssetManager::ReleaseAllAsset();
        ObjManager::ReleaseAllObj();
        return new Title;
    }
    return this;
}

    // @brief ResultScene�`�揈�� //

void Result::Draw()
{
    ObjManager::Draw();
}