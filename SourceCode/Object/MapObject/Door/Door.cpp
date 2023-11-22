#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<fstream>

#include "Door.h"

#include"../../ObjectManager/ObjManager.h"
#include"../../../Asset/Animation/Animation.h"
#include"../../../Asset/AssetManager/AssetManager.h"
#include"../../../Asset/Sound/Sound.h"
#include"../../../UI/Action/Action.h"

Door::Door(std::string scene, std::string num)
    :ObjBase(ObjTag::Furniture)
    , animType(IDLE)
    , doorSound(new Sound)
    , player(nullptr)
    , rotateNow(true)
{

    //�t�@�C���ǂݍ���
    std::ifstream ifs("../SourceCode/Object/MapObject/Door/DoorData.json");
    rapidjson::Document doc;

    //�t�@�C�����
    if (ifs.good())
    {
        rapidjson::IStreamWrapper isw(ifs);

        doc.ParseStream(isw);
    }
    ifs.close();

    //�f�[�^��ǂݎ���č��W�E�����ɑ��
    auto& data = doc[scene.c_str()][num.c_str()];
    objPos.x = data["pos"].GetArray()[0].GetFloat();
    objPos.z = data["pos"].GetArray()[1].GetFloat();
    objDir.x = data["dir"].GetArray()[0].GetFloat();
    objDir.z = data["dir"].GetArray()[1].GetFloat();

    //���f���ݒ�
    objHandle = AssetManager::GetMesh("../Assets/Map/Door/Door.mv1");
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.11f, 0.12f, 0.11f));
    MATRIX rotYMat = MGetRotY(ONE_HALF_PI_DEGREE * (float)(DX_PI / PI_DEGREE));
    VECTOR negativeVec = VTransform(objDir, rotYMat);
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    //�A�j���[�V�����ݒ�
    doorAnim.reset(new Animation(objHandle));
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorOpen.mv1", 30.0f, false);
    doorAnim->AddAnimation("../Assets/Map/Door/DoorClose.mv1", 30.0f, false);
    doorAnim->StartAnim(animType);
    doorAnim->StopAnim();

    //�����蔻��ݒ�
    colType = CollisionType::Sphere;
    colSphere.localCenter = VGet(0, 5, 0);
    colSphere.Radius = 15.0f;
    colSphere.worldCenter = objPos;

    //�T�E���h�ݒ�
    doorSound->AddSound("../Assets/Sound/DoorOpenSE.mp3", SoundTag::DoorOpen, true, true);
    doorSound->AddSound("../Assets/Sound/DoorCloseSE.mp3", SoundTag::DoorClose, true, true);

    //�A�N�V�����{�^���ǉ�
    action = new Action(objPos);
    ObjManager::AddObj(action);
}

Door::~Door()
{
    //�����Ȃ�
}

void Door::Update(const float deltaTime)
{
    //�A�j���[�V�������ԍĐ�
    doorAnim->AddAnimTime(deltaTime);

    //�h�A�̊J����
    player = ObjManager::GetFirstObj(ObjTag::Player);
    if (player)
    {
        //�v���C���[���߂Â�����{�^���\��
        VECTOR actionPos = player->GetPos() - objPos;
        actionPos = VNorm(actionPos);
        action->SetPos(objPos + actionPos + DOOR_ACION_ICON);

        if (!doorAnim->IsPlaying())
        {

            //E�L�[���͂Ńh�A�J��
            if (!action->IsVisible())
            {
                if (animType != OPEN)
                {
                    MoveAnim(OPEN);
                }
            }
            //Q�L�[���͂Ńh�A��
            if (CheckHitKey(KEY_INPUT_Q))
            {
                if (animType == OPEN)
                {
                    MoveAnim(CLOSE);
                }
            }
        }
    }

    //�����蔻��X�V
    colModel = objHandle;
    ColUpdate();

    //�T�E���h�X�V
    doorSound->Doppler(SoundTag::DoorOpen, objPos);
    doorSound->Doppler(SoundTag::DoorClose, objPos);
}

void Door::MoveAnim(int animtype)
{
    //�w�肵���A�j���[�V�������Đ�����
    if (animType != animtype)
    {
        animType = animtype;
        doorAnim->StartAnim(animType);
        if (animtype == OPEN)
        {
            action->SetVisible(false);
            doorSound->StartSound(SoundTag::DoorOpen, DX_PLAYTYPE_BACK);
        }
        else if (animtype == CLOSE)
        {
            doorSound->StartSound(SoundTag::DoorClose, DX_PLAYTYPE_BACK);
        }
    }
}

void Door::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}