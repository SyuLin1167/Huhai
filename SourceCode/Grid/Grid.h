#pragma once
#include<DxLib.h>

class Grid
{
public:
	/// <summary>
	/// Grpd�R���X�g���N�^�\
	/// </summary>
	Grid();

	/// <summary>
	/// Grpd�f�X�g���N�^�\
	/// </summary>
	~Grid(){};

	/// <summary>
	/// �O���b�h���`��
	/// </summary>
	/// <param name="groundSize">:�`�悷�镽�ʂ̑傫��</param>
	/// <param name="divideSize">:���������</param>
	void DrawGrid(float groundSize, int divideSize);

private:
    VECTOR start;
    VECTOR end;
	int lineColor;
};

