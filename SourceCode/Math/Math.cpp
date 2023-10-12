#include "Math.h"

/// <summary>
/// �x�N�g�����m�̉��Z
/// </summary>
/// <param name="lhs">:����(VECTOR)</param>
/// <param name="rhs">:�E��(VECTOR)</param>
/// <returns>2�̃x�N�g���̘a</returns>
VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = lhs.x + rhs.x;
    vRet.y = lhs.y + rhs.y;
    vRet.z = lhs.z + rhs.z;
    return vRet;
}

/// <summary>
/// �x�N�g�����m�̌��Z
/// </summary>
/// <param name="lhs">:����(VECOTR)</param>
/// <param name="rhs">:�E��(VECOTR)</param>
/// <returns>2�̃x�N�g���̍�</returns>
VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = lhs.x - rhs.x;
    vRet.y = lhs.y - rhs.y;
    vRet.z = lhs.z - rhs.z;
    return vRet;
}

/// <summary>
/// �x�N�g���̃X�J���[�{
/// </summary>
/// <param name="lhs">:����(VECTOR)</param>
/// <param name="s">:�E��(float)</param>
/// <returns>�x�N�g����float���|�����l</returns>
VECTOR operator*(const VECTOR& lhs, float s)
{
    VECTOR vRet{};
    vRet.x = lhs.x * s;
    vRet.y = lhs.y * s;
    vRet.z = lhs.z * s;
    return vRet;
}

/// <summary>
/// �x�N�g���̃X�J���[�{
/// </summary>
/// <param name="s">:����(float)</param>
/// <param name="lhs">:�E��(VECTOR)</param>
/// <returns>�x�N�g����float���|�����l</returns>
VECTOR operator*(float s, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = s * rhs.x;
    vRet.y = s * rhs.y;
    vRet.z = s * rhs.z;
    return vRet;
}

/// <summary>
/// �x�N�g���̉��Z�q
/// </summary>
/// <param name="lhs">:����(VECTOR)</param>
/// <param name="rhs">:�E��(VECTOR)</param>
/// <returns>���ӂɉE�ӂ����Z�����x�N�g���̒l</returns>
VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

/// <summary>
/// �x�N�g���̃X�J���[�{�̉��Z�q
/// </summary>
/// <param name="lhs">:����(VECTOR)</param>
/// <param name="rhs">:�E��(float)</param>
/// <returns>���ӂɉE�ӂ���Z�����x�N�g���̒l</returns>
VECTOR operator*=(VECTOR& lhs, float rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

/// <summary> 
/// �p�x�̑�������
/// </summary>
/// <param name="v1">:��ׂ�p�x</param>
/// /// <param name="v2">:�Ώۂ̊p�x</param>
/// /// <returns>�p�x�̑�������</returns>
bool IsSameAngle(const VECTOR& v1, const VECTOR& v2)
{
    float dot = VDot(v1, v2);                           //2�̃x�N�g���̓���
    if (dot > 0.99f)                                    //���ς�1�����łȂ����
    {
        return true;                                    //������true��Ԃ�
    }
    return false;                                       //��{�͈قȂ�false��Ԃ�
}

/// <summary>
/// Y��]�����Z�o
/// </summary>
/// <param name="nowVec">:���݂̌���</param>
/// <param name="dirVec">:������������</param>
/// <returns>��]�������</returns>
float CalcDirRotY(const VECTOR& nowVec, const VECTOR& dirVec)
{
    VECTOR axis;
    axis = VCross(nowVec, dirVec);                      //2�̃x�N�g���̊O��
    if (axis.y < 0.0f)                                  //�O�ς�0�����Ȃ�
    {
        return -1.0f;                                   //�����v���
    }
    return 1.0f;                                        //��{�͎��v���
}

/// <summary>
/// Y��]����
/// </summary>
/// <param name="nowVec">:���݂̌���</param>
/// <param name="aimVec">:�ڕW�̌���</param>
/// <param name="velocity">:��]���x</param>
/// <returns>��]�p</returns>
VECTOR RotForAimY(const VECTOR& nowVec, const VECTOR& aimVec,float velocity)
{
    
    float rotRadian = (DX_PI_F * velocity / 180.0f);    // �p���x�����W�A���p�ɕϊ�
    rotRadian *= CalcDirRotY(nowVec, aimVec);           //�E��肩����肩�𒲂ׂ�

    MATRIX yrotMat = MGetRotY(rotRadian);               // Y��]�s����쐬

    VECTOR rotVec;
    rotVec = VTransform(nowVec, yrotMat);               //Y����]����

    return rotVec;                                      //��]�p��Ԃ�  
}