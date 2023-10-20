#include "FixedCamera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
FixedCamera::FixedCamera()
	:ObjBase(ObjTag::Camera)
{
    objPos = FIRST_POS;
    objDir = FIRST_AIM_POS;
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
/// <param name="deltaTime">:�f���^�^�C��</param>
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