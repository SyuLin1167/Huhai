#include "Grid.h"

Grid::Grid()
    :start{0,0,0}
    ,end{0,0,0}
{
    lineColor = GetColor(0, 128, 0);
}


// @brief 

void Grid::DrawGrid(float groundSize, int divideNum)
{
    float halfWidth = groundSize * 0.5f;              // グリッド線を引く範囲の半分の幅
    float addWidth = groundSize / (float)divideNum;  // グリッド線を引く間隔

    
    //---縦線を引く---//
    start.z = -halfWidth;                           //始点Zは中心から負の方向で描画範囲の半分の幅
    end.z = halfWidth;                              //終点Zは中心から正の方向で描画範囲の半分の幅
    for (int ix = 0; ix < divideNum + 1; ix++)
    {
        start.x = end.x = -halfWidth + ix * addWidth;   //描画するX座標は等間隔
        DrawLine3D(start, end, lineColor);      //縦線描画
    }

    //---横線を引く---//
    start.x = -halfWidth;       //始点Xは中心から負の方向で描画範囲の半分の幅
    end.x = halfWidth;          //終点Xは中心から正の方向で描画範囲の半分の幅
    for (int iz = 0; iz < divideNum + 1; iz++)
    {
        start.z = end.z = -halfWidth + iz * addWidth;   //描画するY座標は等間隔
        DrawLine3D(start, end, lineColor);      //横線描画
    }
}