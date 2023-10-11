#include "FixedCamera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
FixedCamera::FixedCamera()
	:ObjBase(ObjTag::Camera)
{
    objPos = VGet(70, 6, 75);
    objDir = VGet(-10, 10, 25);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FixedCamera::~FixedCamera()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void FixedCamera::Update(const float deltaTime)
{
    //�����Ȃ�
}

/// <summary>
/// �`�揈��
/// </summary>
void FixedCamera::Draw()
{
    //�����_�Ɍ����ăJ�������Z�b�g
    SetCameraPositionAndTarget_UpVecY(objPos, objDir);
}