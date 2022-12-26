#pragma once
#include<DxLib.h>

class Grid
{
public:
	/// <summary>
	/// Grpdコンストラクタ―
	/// </summary>
	Grid();

	/// <summary>
	/// Grpdデストラクタ―
	/// </summary>
	~Grid(){};

	/// <summary>
	/// グリッド線描画
	/// </summary>
	/// <param name="groundSize">:描画する平面の大きさ</param>
	/// <param name="divideSize">:分割する個数</param>
	void DrawGrid(float groundSize, int divideSize);

private:
    VECTOR start;
    VECTOR end;
	int lineColor;
};

