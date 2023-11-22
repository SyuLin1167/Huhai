#include "Collision.h"

Line::Line()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
{
}

Line::Line(const VECTOR& startPos, const VECTOR& endPos)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
{
}

void Line::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //���[���h���W�n�_�ړ�
    worldEnd = localEnd + pos;              //���[���h���W�I�_�ړ�
}

Sphere::Sphere()
    :localCenter()
    ,worldCenter()
    ,Radius(0.0f)
{
}

Sphere::Sphere(const VECTOR& center,float radius)
    :localCenter(center)
    ,worldCenter(center)
    ,Radius(radius)
{
}

void Sphere::Move(const VECTOR& pos)
{
    worldCenter = localCenter + pos;        //���[���h���S���W�ړ�
}

Capsule::Capsule()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
    ,Radius(0.0f)
{
}

Capsule::Capsule(const VECTOR& startPos, const VECTOR& endPos, float radius)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
    ,Radius(radius)
{
}

void Capsule::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //���[���h���W�n�_�ړ�
    worldEnd = localEnd + pos;              //���[���h���W�I�_�ړ�
}

bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
{
    return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.Radius,
        sphere2.worldCenter, sphere2.Radius);
}

bool CollisionPair(const Line& line, const Sphere& sphere)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

bool CollisionPair(const Sphere& sphere, const Line& line)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

bool CollisionPair(const Line& line, const int modelHandle, MV1_COLL_RESULT_POLY& colInfo)
{
    colInfo = MV1CollCheck_Line(modelHandle, -1,
        line.worldStart, line.worldEnd);
    return colInfo.HitFlag;
}

bool CollisionPair( const int modelHandle,const Line& line, MV1_COLL_RESULT_POLY& colInfo)
{
    return CollisionPair(line, modelHandle, colInfo);
}

bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& colInfo)
{
    colInfo = MV1CollCheck_Sphere(modelHandle, -1, sphere.worldCenter, sphere.Radius);
    if (colInfo.HitNum == 0)
    {
        return false;
    }
    return true;
}

VECTOR CalcSpherePushBackFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& colInfo)
{
    VECTOR planeNormal;                //���ʖ@��
    VECTOR canditateCenter = sphere.worldCenter;                                           //�����S�������̂̒��S���W�ɂ��� 
    float Rad = sphere.Radius;                                                            //�����a

    VECTOR canditateMove = sphere.worldCenter;                                             //�ړ��������̂̒��S���W�ɂ���


    // �Փ˃|���S�������ׂĉ���āA���̂߂荞�݂���������
    for (int i = 0; i < colInfo.HitNum; ++i)                                        //�Փ˃|���S�����߂荞�݉���
    {
        //---�Փ˃|���S���̕�---// 
        VECTOR edge1, edge2;                                                        //�Փ˃|���S���̕�
        edge1 = colInfo.Dim[i].Position[1] - colInfo.Dim[i].Position[0];            //��(pos0�Epos1)�x�N�g��
        edge2 = colInfo.Dim[i].Position[2] - colInfo.Dim[i].Position[0];            //��(pos0�Epos2)�x�N�g��

        planeNormal = VCross(edge1, edge2);                                         //�ӂ���|���S���ʂ̖@���x�N�g���Z�o
        planeNormal = VNorm(planeNormal);                                           //�@���x�N�g�����K��

        //---���S�����߂�---//
        if (HitCheck_Sphere_Triangle(canditateCenter, Rad,
            colInfo.Dim[i].Position[0],
            colInfo.Dim[i].Position[1],
            colInfo.Dim[i].Position[2]) == TRUE)                                    //�����߂荞��ł�����
        {
            //---�����S�ɍł��߂��|���S�����ʂ̓_���Z�o---//
            VECTOR calc1, calc2;                                                        //�Z�o�x�N�g��

            calc1 = canditateCenter - colInfo.Dim[i].Position[0];                       //��(pos0�E�����S)�x�N�g��
            float  dot = VDot(planeNormal, calc1);                                      //�@���ƕӂ̓���

            VECTOR hitPos = canditateCenter - planeNormal * dot;                        //�Փ˓_

            //--���̂߂荞�ݗʎZ�o---//
            calc2 = canditateCenter - hitPos;                                           //�ӏՓ˓_�E�����S�x�N�g��
            float  len = VSize(calc2);                                                  //�߂荞�ݗʂ̑傫��

            VECTOR moveVec;
            len = Rad - len;                                                        //�����a����߂荞�ݗʂ��������傫��
            moveVec = planeNormal * len;                                            //�ړ��ʎZ�o
            canditateCenter += moveVec;                                             //�����S�����߂�
        }
        else
        {
            continue;
        }
    }

    canditateMove = canditateCenter;                                                //�ړ������ړ��ʒu��

    return canditateMove - sphere.worldCenter;                                      // �����߂��ʂ�ԋp
}