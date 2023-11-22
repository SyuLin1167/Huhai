#include "Math.h"

VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = lhs.x + rhs.x;
    vRet.y = lhs.y + rhs.y;
    vRet.z = lhs.z + rhs.z;
    return vRet;
}

VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = lhs.x - rhs.x;
    vRet.y = lhs.y - rhs.y;
    vRet.z = lhs.z - rhs.z;
    return vRet;
}

VECTOR operator*(const VECTOR& lhs, float s)
{
    VECTOR vRet{};
    vRet.x = lhs.x * s;
    vRet.y = lhs.y * s;
    vRet.z = lhs.z * s;
    return vRet;
}

VECTOR operator*(float s, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = s * rhs.x;
    vRet.y = s * rhs.y;
    vRet.z = s * rhs.z;
    return vRet;
}

VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

VECTOR operator*=(VECTOR& lhs, float rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

bool IsSameAngle(const VECTOR& v1, const VECTOR& v2)
{
    //内積から相似を判定
    float dot = VDot(v1, v2);
    if (dot > 0.99f)
    {
        return true;
    }
    return false;
}

float CalcDirRotY(const VECTOR& nowVec, const VECTOR& dirVec)
{
    //外積から回転方向算出
    VECTOR axis;
    axis = VCross(nowVec, dirVec);
    if (axis.y < 0.0f)
    {
        return -1.0f;
    }
    return 1.0f;
}

VECTOR RotForAimY(const VECTOR& nowVec, const VECTOR& aimVec,float velocity)
{
    //回転量と向きを決める
    float rotRadian = (DX_PI_F * velocity / 180.0f);
    rotRadian *= CalcDirRotY(nowVec, aimVec);

    //回転ベクトルを計算して返す
    MATRIX yrotMat = MGetRotY(rotRadian);
    VECTOR rotVec = VTransform(nowVec, yrotMat);

    return rotVec;
}