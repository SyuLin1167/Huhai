#include "FixedCamera.h"

FixedCamera::FixedCamera()
	:ObjBase(ObjTag::Camera)
{
    objPos = FIRST_POS;
    objDir = FIRST_AIM_POS;
}

FixedCamera::~FixedCamera()
{
    //�����Ȃ�
}

void FixedCamera::Update(const float deltaTime)
{
    //�����Ȃ�
}

void FixedCamera::Draw()
{
    //�����_�Ɍ����ăJ�������Z�b�g
    SetCameraPositionAndTarget_UpVecY(objPos, objDir);
}