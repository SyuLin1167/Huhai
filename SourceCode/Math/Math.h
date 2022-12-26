#pragma once
#include<DxLib.h>

/// <summary>
/// �x�N�g�����m�̉��Z
/// </summary>
/// <param name="lhs">:����(VECTOR)</param>
/// <param name="rhs">:�E��(VECTOR)</param>
/// <returns>2�̃x�N�g���̘a</returns>
VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

/// <summary>
/// �x�N�g�����m�̌��Z
/// </summary>
/// <param name="lhs">:����(VECOTR)</param>
/// <param name="rhs">:�E��(VECOTR)</param>
/// <returns>2�̃x�N�g���̍�</returns>
VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

/// <summary>
/// �x�N�g���̃X�J���[�{
/// </summary>
/// <param name="lhs">:����(VECTOR)</param>
/// <param name="s">:�E��(float)</param>
/// <returns>�x�N�g����float���|�����l</returns>
VECTOR operator*(const VECTOR& lhs, float s);

/// <summary>
/// �x�N�g���̃X�J���[�{
/// </summary>
/// <param name="s">:����(float)</param>
/// <param name="lhs">:�E��(VECTOR)</param>
/// <returns>�x�N�g����float���|�����l</returns>
VECTOR operator*(float s,const VECTOR& rhs);

/// <summary>
/// �x�N�g���̉��Z�q
/// </summary>
/// <param name="lhs">:����(VECTOR)</param>
/// <param name="rhs">:�E��(VECTOR)</param>
/// <returns>���ӂɉE�ӂ����Z�����x�N�g���̒l</returns>
VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

/// <summary>
/// �x�N�g���̃X�J���[�{�̉��Z�q
/// </summary>
/// <param name="lhs">:����(VECTOR)</param>
/// <param name="rhs">:�E��(float)</param>
/// <returns>���ӂɉE�ӂ���Z�����x�N�g���̒l</returns>
VECTOR operator*=(VECTOR& lhs, float rhs);

/// <summary> 
/// �p�x�̑�������
/// </summary>
/// <param name="v1">:��ׂ�p�x</param>
/// /// <param name="v2">:�Ώۂ̊p�x</param>
/// /// <returns>�p�x�̑�������</returns>
bool IsSameAngle(const VECTOR& v1, const VECTOR& v2);

/// <summary>
/// Y��]�����Z�o
/// </summary>
/// <param name="nowVec">:���݂̌���</param>
/// <param name="dirVec">:������������</param>
/// <returns>��]�������</returns>
float CalcDirRotY(const VECTOR& nowVec, const VECTOR& dirVec);

/// <summary>
/// Y��]����
/// </summary>
/// <param name="nowVec">:���݂̌���</param>
/// <param name="aimVec">:�ڕW�̌���</param>
/// <param name="velocity">:��]���x</param>
/// <returns>��]�p</returns>
VECTOR RotForAimY(const VECTOR& nowVec, const VECTOR& aimVec,
	float velocity);