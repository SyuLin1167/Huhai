#pragma once
#include<DxLib.h>

/// <summary>
/// ベクトル同士の加算
/// </summary>
/// <param name="lhs">左辺(VECTOR)</param>
/// <param name="rhs">右辺(VECTOR)</param>
/// <returns>2つのベクトルの和</returns>
VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

/// <summary>
/// ベクトル同士の減算
/// </summary>
/// <param name="lhs">左辺(VECOTR)</param>
/// <param name="rhs">右辺(VECOTR)</param>
/// <returns>2つのベクトルの差</returns>
VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

/// <summary>
/// ベクトルのスカラー倍
/// </summary>
/// <param name="lhs">左辺(VECTOR)</param>
/// <param name="s">右辺(float)</param>
/// <returns>ベクトルにfloatを掛けた値</returns>
VECTOR operator*(const VECTOR& lhs, float s);

/// <summary>
/// ベクトルの演算子
/// </summary>
/// <param name="lhs">左辺(VECTOR)</param>
/// <param name="rhs">右辺(VECTOR)</param>
/// <returns>左辺に右辺を加算したベクトルの値</returns>
VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

/// <summary>
/// ベクトルのスカラー倍の演算子
/// </summary>
/// <param name="lhs">左辺(VECTOR)</param>
/// <param name="rhs">右辺(float)</param>
/// <returns>左辺に右辺を乗算したベクトルの値</returns>
VECTOR operator*=(VECTOR& lhs, float rhs);
