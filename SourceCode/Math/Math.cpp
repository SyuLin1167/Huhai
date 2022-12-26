#include "Math.h"

// @brief �x�N�g�����m�̉��Z //

VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = lhs.x + rhs.x;
    vRet.y = lhs.y + rhs.y;
    vRet.z = lhs.z + rhs.z;
    return vRet;
}

// @brief �x�N�g�����m�̌��Z //

VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = lhs.x - rhs.x;
    vRet.y = lhs.y - rhs.y;
    vRet.z = lhs.z - rhs.z;
    return vRet;
}

// @brief �x�N�g���̃X�J���[�{ //

VECTOR operator*(const VECTOR& lhs, float s)
{
    VECTOR vRet{};
    vRet.x = lhs.x * s;
    vRet.y = lhs.y * s;
    vRet.z = lhs.z * s;
    return vRet;
}

// @brief �x�N�g���̃X�J���[�{ //

VECTOR operator*(float s, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = s * rhs.x;
    vRet.y = s * rhs.y;
    vRet.z = s * rhs.z;
    return vRet;
}

// @brief �x�N�g���̉��Z�q //

VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

// @brief �x�N�g���̃X�J���[�{�̉��Z�q //

VECTOR operator*=(VECTOR& lhs, float rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

// @brief �p�x�̑������� //

bool IsSameAngle(const VECTOR& v1, const VECTOR& v2)
{
    float dot = VDot(v1, v2);               //2�̃x�N�g���̓���
    if (dot > 0.99f)                               //���ς�1�����łȂ����
    {
        return true;                                //������true��Ԃ�
    }
    return false;                                  //��{�͈قȂ�false��Ԃ�
}

// @brief Y��]�����Z�o //

float CalcDirRotY(const VECTOR& nowVec, const VECTOR& dirVec)
{
    VECTOR axis;
    axis = VCross(nowVec, dirVec);          //2�̃x�N�g���̊O��
    if (axis.y < 0.0f)                              //�O�ς�0�����Ȃ�
    {
        return -1.0f;                               //�����v���
    }
    return 1.0f;                                    //��{�͎��v���
}

// @brief Y��]���� //

VECTOR RotForAimY(const VECTOR& nowVec, const VECTOR& aimVec,float velocity)
{
    
    float rotRadian = (DX_PI_F * velocity / 180.0f);    // �p���x�����W�A���p�ɕϊ�
    rotRadian *= CalcDirRotY(nowVec, aimVec);        //�E��肩����肩�𒲂ׂ�

    MATRIX yrotMat = MGetRotY(rotRadian);       // Y��]�s����쐬

    VECTOR rotVec;
    rotVec = VTransform(nowVec, yrotMat);           //Y����]����

    return rotVec;                                      //��]�p��Ԃ�  
}