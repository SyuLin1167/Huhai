#include "Collision.h"

// @brief Collsion�R���X�g���N�^�[ //

Collision::Collision()
    :canditateCenter{0,0,0}
    ,canditateMove{0,0,0}
    ,planeNormal{0,0,0}
    ,pushOut{0,0,0}
    ,Rad(0.0f)
{
}

// @brief Line�R���X�g���N�^�[ //

Collision::Line::Line()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
{
}

// @brief Line�R���X�g���N�^�[(�����t) //

Collision::Line::Line(const VECTOR& startPos, const VECTOR& endPos)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
{
}

// @brief Line�ړ����� //

void Collision::Line::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //���[���h���W�n�_�ړ�
    worldEnd = localEnd + pos;              //���[���h���W�I�_�ړ�
}

// @brief Sphere�R���X�g���N�^�[ //

Collision::Sphere::Sphere()
    :localCenter()
    ,worldCenter()
    ,Radius(0.0f)
{
}

// @brief Sphere�R���X�g���N�^�[(�����t)

Collision::Sphere::Sphere(const VECTOR& center,float radius)
    :localCenter(center)
    ,worldCenter(center)
    ,Radius(radius)
{
}

// @brief Sphere�ړ����� //
void Collision::Sphere::Move(const VECTOR& pos)
{
    worldCenter = localCenter + pos;        //���[���h���S���W�ړ�
}

// @brief Capsule�R���X�g���N�^�[ //

Collision::Capsule::Capsule()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
    ,Radius(0.0f)
{
}

// @brief Capsule�R���X�g���N�^�[ //

Collision::Capsule::Capsule(const VECTOR& startPos, const VECTOR& endPos, float radius)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
    ,Radius(radius)
{
}

// @brief Capsule�ړ������@//

void Collision::Capsule::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //���[���h���W�n�_�ړ�
    worldEnd = localEnd + pos;              //���[���h���W�I�_�ړ�
}

// @brief ���̓��m�̓����蔻�� //

bool Collision::CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
{
    return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.Radius,
        sphere2.worldCenter, sphere2.Radius);
}

// @brief ���������̓����蔻�� //

bool Collision::CollisionPair(const Line& line, const Sphere& sphere)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

// @brief ���́����������蔻�� //

bool Collision::CollisionPair(const Sphere& sphere, const Line& line)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

// @brief ���������f�������蔻�� //

bool Collision::CollisionPair(const Line& line, const int modelHandle, MV1_COLL_RESULT_POLY& colInfo)
{
    colInfo = MV1CollCheck_Line(modelHandle, -1,
        line.worldStart, line.worldEnd);
    return colInfo.HitFlag;
}

// @brief ���f�������������蔻�� //

bool Collision::CollisionPair( const int modelHandle,const Line& line, MV1_COLL_RESULT_POLY& colInfo)
{
    return CollisionPair(line, modelHandle, colInfo);
}

// @brief ���́����f�������蔻�� //

bool Collision::CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& colInfo)
{
    colInfo = MV1CollCheck_Sphere(modelHandle, -1,
        sphere.worldCenter, sphere.Radius);
    if (colInfo.HitNum == 0)
    {
        return false;
    }
    return true;
}

// @brief ���́����f�������蔻�艟���߂��ʎZ�o //

VECTOR Collision::CalcSpherePushBackFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& colInfo)
{
    canditateCenter = sphere.worldCenter;                                           //�����S�������̂̒��S���W�ɂ���
    Rad = sphere.Radius;

    for (int i = 0 ; i < colInfo.HitNum ; i++)                                      //�Փ˃|���S�����߂荞�݉���
    {
        VECTOR edge1, edge2;                                                        //�Փ˃|���S���̕�
        edge1 = colInfo.Dim[i].Position[1] - colInfo.Dim[i].Position[0];            //��pos0�Epos1�x�N�g��
        edge2 = colInfo.Dim[i].Position[2] - colInfo.Dim[i].Position[0];            //��pos0�Epos2�x�N�g��

        planeNormal = VCross(edge1, edge2);                                  //�ӂ���|���S���ʂ̖@���x�N�g���Z�o
        planeNormal = VNorm(planeNormal);                                        //�@���x�N�g�����K��

        VECTOR calc1, calc2;                                                        //�Z�o

        //---�����S�ɍł��߂��|���S�����ʂ̓_���Z�o---//
        calc1 = canditateCenter - colInfo.Dim[i].Position[0];                       //��pos0�E�����S�x�N�g��                   
        float dot = VDot(planeNormal, calc1);                                //�@���ƕӂ̓���

        VECTOR hitPos = canditateCenter - planeNormal * dot;                        //�Փ˓_

        //--���̂߂荞�ݗʎZ�o---//
        calc2 = canditateCenter - hitPos;                                           //�ӏՓ˓_�E�����S�x�N�g��
        float len = VSize(calc2);                                                //�߂荞�ݗʂ̑傫��

        if (HitCheck_Sphere_Triangle(canditateCenter, Rad,
            colInfo.Dim[i].Position[0],
            colInfo.Dim[i].Position[1],
            colInfo.Dim[i].Position[2]) == TRUE)                          //�����߂荞��ł�����
        {
            len = Rad - len;                                                        //�����a����߂荞�ݗʂ��������傫��
            VECTOR moveVec = planeNormal * len;                                     //�ړ��ʎZ�o
            canditateCenter += moveVec;                                             //�����S�����߂�
        }

        canditateMove = canditateCenter;                                            //�ړ������ړ��ʒu��

        return canditateMove - sphere.worldCenter;
    }

}
