#include "Math.h"

/// <summary>
/// ベクトル同士の加算
/// </summary>
/// <param name="lhs">:左辺(VECTOR)</param>
/// <param name="rhs">:右辺(VECTOR)</param>
/// <returns>2つのベクトルの和</returns>
VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = lhs.x + rhs.x;
    vRet.y = lhs.y + rhs.y;
    vRet.z = lhs.z + rhs.z;
    return vRet;
}

/// <summary>
/// ベクトル同士の減算
/// </summary>
/// <param name="lhs">:左辺(VECOTR)</param>
/// <param name="rhs">:右辺(VECOTR)</param>
/// <returns>2つのベクトルの差</returns>
VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = lhs.x - rhs.x;
    vRet.y = lhs.y - rhs.y;
    vRet.z = lhs.z - rhs.z;
    return vRet;
}

/// <summary>
/// ベクトルのスカラー倍
/// </summary>
/// <param name="lhs">:左辺(VECTOR)</param>
/// <param name="s">:右辺(float)</param>
/// <returns>ベクトルにfloatを掛けた値</returns>
VECTOR operator*(const VECTOR& lhs, float s)
{
    VECTOR vRet{};
    vRet.x = lhs.x * s;
    vRet.y = lhs.y * s;
    vRet.z = lhs.z * s;
    return vRet;
}

/// <summary>
/// ベクトルのスカラー倍
/// </summary>
/// <param name="s">:左辺(float)</param>
/// <param name="lhs">:右辺(VECTOR)</param>
/// <returns>ベクトルにfloatを掛けた値</returns>
VECTOR operator*(float s, const VECTOR& rhs)
{
    VECTOR vRet{};
    vRet.x = s * rhs.x;
    vRet.y = s * rhs.y;
    vRet.z = s * rhs.z;
    return vRet;
}

/// <summary>
/// ベクトルの演算子
/// </summary>
/// <param name="lhs">:左辺(VECTOR)</param>
/// <param name="rhs">:右辺(VECTOR)</param>
/// <returns>左辺に右辺を加算したベクトルの値</returns>
VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

/// <summary>
/// ベクトルのスカラー倍の演算子
/// </summary>
/// <param name="lhs">:左辺(VECTOR)</param>
/// <param name="rhs">:右辺(float)</param>
/// <returns>左辺に右辺を乗算したベクトルの値</returns>
VECTOR operator*=(VECTOR& lhs, float rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

/// <summary> 
/// 角度の相似判定
/// </summary>
/// <param name="v1">:比べる角度</param>
/// /// <param name="v2">:対象の角度</param>
/// /// <returns>角度の相似判定</returns>
bool IsSameAngle(const VECTOR& v1, const VECTOR& v2)
{
    float dot = VDot(v1, v2);                           //2つのベクトルの内積
    if (dot > 0.99f)                                    //内積が1未満でなければ
    {
        return true;                                    //相似のtrueを返す
    }
    return false;                                       //基本は異なるfalseを返す
}

/// <summary>
/// Y回転方向算出
/// </summary>
/// <param name="nowVec">:現在の向き</param>
/// <param name="dirVec">:向きたい方向</param>
/// <returns>回転する方向</returns>
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

/// <summary>
/// Y回転処理
/// </summary>
/// <param name="nowVec">:現在の向き</param>
/// <param name="aimVec">:目標の向き</param>
/// <param name="velocity">:回転速度</param>
/// <returns>回転角</returns>
VECTOR RotForAimY(const VECTOR& nowVec, const VECTOR& aimVec,float velocity)
{
    
    float rotRadian = (DX_PI_F * velocity / 180.0f);    // 角速度をラジアン角に変換
    rotRadian *= CalcDirRotY(nowVec, aimVec);           //右回りか左回りかを調べる

    MATRIX yrotMat = MGetRotY(rotRadian);               // Y回転行列を作成

    VECTOR rotVec;
    rotVec = VTransform(nowVec, yrotMat);               //Y軸回転する

    return rotVec;                                      //回転角を返す  
}