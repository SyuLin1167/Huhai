#pragma once
#include<DxLib.h>

/// <summary>
/// ベクトル同士の加算
/// </summary>
/// <param name="lhs">:左辺(VECTOR)</param>
/// <param name="rhs">:右辺(VECTOR)</param>
/// <returns>2つのベクトルの和</returns>
VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

/// <summary>
/// ベクトル同士の減算
/// </summary>
/// <param name="lhs">:左辺(VECOTR)</param>
/// <param name="rhs">:右辺(VECOTR)</param>
/// <returns>2つのベクトルの差</returns>
VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

/// <summary>
/// ベクトルのスカラー倍
/// </summary>
/// <param name="lhs">:左辺(VECTOR)</param>
/// <param name="s">:右辺(float)</param>
/// <returns>ベクトルにfloatを掛けた値</returns>
VECTOR operator*(const VECTOR& lhs, float s);

/// <summary>
/// ベクトルのスカラー倍
/// </summary>
/// <param name="s">:左辺(float)</param>
/// <param name="lhs">:右辺(VECTOR)</param>
/// <returns>ベクトルにfloatを掛けた値</returns>
VECTOR operator*(float s,const VECTOR& rhs);

/// <summary>
/// ベクトルの演算子
/// </summary>
/// <param name="lhs">:左辺(VECTOR)</param>
/// <param name="rhs">:右辺(VECTOR)</param>
/// <returns>左辺に右辺を加算したベクトルの値</returns>
VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

/// <summary>
/// ベクトルのスカラー倍の演算子
/// </summary>
/// <param name="lhs">:左辺(VECTOR)</param>
/// <param name="rhs">:右辺(float)</param>
/// <returns>左辺に右辺を乗算したベクトルの値</returns>
VECTOR operator*=(VECTOR& lhs, float rhs);

/// <summary> 
/// 角度の相似判定
/// </summary>
/// <param name="v1">:比べる角度</param>
/// /// <param name="v2">:対象の角度</param>
/// /// <returns>角度の相似判定</returns>
bool IsSameAngle(const VECTOR& v1, const VECTOR& v2);

/// <summary>
/// Y回転方向算出
/// </summary>
/// <param name="nowVec">:現在の向き</param>
/// <param name="dirVec">:向きたい方向</param>
/// <returns>回転する方向</returns>
float CalcDirRotY(const VECTOR& nowVec, const VECTOR& dirVec);

/// <summary>
/// Y回転処理
/// </summary>
/// <param name="nowVec">:現在の向き</param>
/// <param name="aimVec">:目標の向き</param>
/// <param name="velocity">:回転速度</param>
/// <returns>回転角</returns>
VECTOR RotForAimY(const VECTOR& nowVec, const VECTOR& aimVec,
	float velocity);