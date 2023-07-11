#include "FixedCamera.h"

// �R���X�g���N�^ //

FixedCamera::FixedCamera()
	:ObjBase(ObjectTag::Camera)
{
    objPos = VGet(70, 6, 75);
    objDir = VGet(-10, 10, 25);
}


// �`�揈�� //

void FixedCamera::Draw()
{
    //�����_�Ɍ����ăJ�������Z�b�g
    SetCameraPositionAndTarget_UpVecY(objPos, objDir);
}