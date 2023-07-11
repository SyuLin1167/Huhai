#include "Math.h"

// ベクトル同士の加算 //

VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = lhs.x + rhs.x;
    vRet.y = lhs.y + rhs.y;
    vRet.z = lhs.z + rhs.z;
    return vRet;
}

// ベクトル同士の減算 //

VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = lhs.x - rhs.x;
    vRet.y = lhs.y - rhs.y;
    vRet.z = lhs.z - rhs.z;
    return vRet;
}

// ベクトルのスカラー倍 //

VECTOR operator*(const VECTOR& lhs, float s)
{
    VECTOR vRet{};
    vRet.x = lhs.x * s;
    vRet.y = lhs.y * s;
    vRet.z = lhs.z * s;
    return vRet;
}

// ベクトルのスカラー倍 //

VECTOR operator*(float s, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = s * rhs.x;
    vRet.y = s * rhs.y;
    vRet.z = s * rhs.z;
    return vRet;
}

// ベクトルの演算子 //

VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

// ベクトルのスカラー倍の演算子 //

VECTOR operator*=(VECTOR& lhs, float rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

// 角度の相似判定 //

bool IsSameAngle(const VECTOR& v1, const VECTOR& v2)
{
    float dot = VDot(v1, v2);                           //2つのベクトルの内積
    if (dot > 0.99f)                                    //内積が1未満でなければ
    {
        return true;                                    //相似のtrueを返す
    }
    return false;                                       //基本は異なるfalseを返す
}

// Y回転方向算出 //

float CalcDirRotY(const VECTOR& nowVec, const VECTOR& dirVec)
{
    VECTOR axis;
    axis = VCross(nowVec, dirVec);                      //2つのベクトルの外積
    if (axis.y < 0.0f)                                  //外積が0未満なら
    {
        return -1.0f;                                   //反時計回り
    }
    return 1.0f;                                        //基本は時計回り
}

// Y回転処理 //

VECTOR RotForAimY(const VECTOR& nowVec, const VECTOR& aimVec,float velocity)
{
    
    float rotRadian = (DX_PI_F * velocity / 180.0f);    // 角速度をラジアン角に変換
    rotRadian *= CalcDirRotY(nowVec, aimVec);           //右回りか左回りかを調べる

    MATRIX yrotMat = MGetRotY(rotRadian);               // Y回転行列を作成

    VECTOR rotVec;
    rotVec = VTransform(nowVec, yrotMat);               //Y軸回転する

    return rotVec;                                      //回転角を返す  
}