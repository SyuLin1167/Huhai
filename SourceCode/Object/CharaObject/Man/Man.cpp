#include "Man.h"
#include"../../../UI/Action/Action.h"
#include"../../../Scene/Reamarks/Remarks.h"

// @brief Man�R���X�g���N�^ //

Man::Man()
    :ObjectBase(ObjectTag::Man)
    , manAnim(nullptr)
    , rotateNow(false)
    , aimDir{ 0,0,0 }
    , addRemarks(false)
{
    Load();
}

// @brief Man�f�X�g���N�^ //

Man::~Man()
{
    AssetManager::ReleaseMesh(objHandle);
    delete manAnim;
}

// @brief Man�ǂݍ��ݏ��� //

void Man::Load()
{
    //---���f���ǂݍ���---//
    objHandle = AssetManager::GetMesh("../Assets/Chara/Man/ManModel.mv1");
    objPos = { -55.0f,0.0f,30.0f };
    objDir = { 0,0,-1 };
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, VGet(0.02f, 0.02f, 0.02f));


    manAnim = new Animation(objHandle);

    manAnim->AddAnimation("../Assets/Chara/Man/ManCrying.mv1");
    animType = CRYING;
    manAnim->StartAnim(animType);

    ObjManager::Entry(new Action(objPos + VGet(0, 0, 5)));

}

// @brief Man�X�V���� //

void Man::Update(float deltaTime)
{
    manAnim->AddAnimTime(deltaTime);
    MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
    VECTOR negativeVec = VTransform(objDir, rotYMat);
    if (!ObjManager::GetFirstObj(ObjectTag::UI)->IsVisible())
    {
        rotateNow = true;
        aimDir = VSub(ObjManager::GetFirstObj(ObjectTag::Player)->GetPos(), objPos);
        aimDir = VNorm(aimDir);
        Rotate();
        if (!rotateNow && !addRemarks)
        {
            ObjManager::Entry(new Remarks(TextType::Day1Stage));
            addRemarks = true;
        }
    }

    // ���f���ɉ�]���Z�b�g����
    MV1SetRotationZYAxis(objHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

// @brief Man�`�揈 //

void Man::Draw()
{
    MV1DrawModel(objHandle);
}

void Man::Rotate()
{
    if (rotateNow)
    {
        // ��]���ڕW�p�x�ɏ\���߂���Ή�]���[�h�I��
        if (IsSameAngle(aimDir, objDir))
        {
            objDir = aimDir;
            rotateNow = false;
        }
        else
        {
            // ��]������
            VECTOR interPolateDir;
            interPolateDir = RotForAimY(objDir, aimDir, 2.0f);

            // ��]���ڕW�p�x�𒴂��Ă��Ȃ���
            VECTOR cross1, cross2;
            cross1 = VCross(objDir, aimDir);
            cross2 = VCross(interPolateDir, aimDir);

            //�ڕW�p�x�𒴂�����I��
            if (cross1.y * cross2.y < 0.0f)
            {
                interPolateDir = aimDir;
                rotateNow = false;
            }
            // �ڕW�x�N�g����10�x�����߂Â����p�x
            objDir = interPolateDir;
        }
    }
}