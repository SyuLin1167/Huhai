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
    float halfWidth = groundSize * 0.5f;              // �O���b�h���������͈͂̔����̕�
    float addWidth = groundSize / (float)divideNum;  // �O���b�h���������Ԋu

    
    //---�c��������---//
    start.z = -halfWidth;                           //�n�_Z�͒��S���畉�̕����ŕ`��͈͂̔����̕�
    end.z = halfWidth;                              //�I�_Z�͒��S���琳�̕����ŕ`��͈͂̔����̕�
    for (int ix = 0; ix < divideNum + 1; ix++)
    {
        start.x = end.x = -halfWidth + ix * addWidth;   //�`�悷��X���W�͓��Ԋu
        DrawLine3D(start, end, lineColor);      //�c���`��
    }

    //---����������---//
    start.x = -halfWidth;       //�n�_X�͒��S���畉�̕����ŕ`��͈͂̔����̕�
    end.x = halfWidth;          //�I�_X�͒��S���琳�̕����ŕ`��͈͂̔����̕�
    for (int iz = 0; iz < divideNum + 1; iz++)
    {
        start.z = end.z = -halfWidth + iz * addWidth;   //�`�悷��Y���W�͓��Ԋu
        DrawLine3D(start, end, lineColor);      //�����`��
    }
}