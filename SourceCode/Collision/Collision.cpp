#include "Collision.h"

//---���������蔻��֘A---//
// @brief Line�R���X�g���N�^�[ //

Line::Line()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
{
}

// @brief Line�R���X�g���N�^�[(�����t) //

Line::Line(const VECTOR& startPos, const VECTOR& endPos)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
{
}

// @brief Line�ړ����� //

void Line::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //���[���h���W�n�_�ړ�
    worldEnd = localEnd + pos;              //���[���h���W�I�_�ړ�
}

//---��^�����蔻��֘A---//
// @brief Fan�R���X�g���N�^�[ //

Fan::Fan()
    :localCenter()
    , worldCenter()
    , Range()
    , Radius()
{
}

// @brief Fan�R���X�g���N�^�[(�����t) //

Fan::Fan(const VECTOR& center, float radius)
    :localCenter(center)
    , worldCenter(center)
    , Range()
    , Radius(radius)
{
}

// @brief Fan�ړ����� //

void Fan::Move(const VECTOR& pos)
{
    worldCenter = localCenter + pos;        //���[���h���S���W�ړ�
}

//---���̓����蔻��֘A---//
// @brief Sphere�R���X�g���N�^�[ //

Sphere::Sphere()
    :localCenter()
    ,worldCenter()
    ,Radius(0.0f)
{
}

// @brief Sphere�R���X�g���N�^�[(�����t)

Sphere::Sphere(const VECTOR& center,float radius)
    :localCenter(center)
    ,worldCenter(center)
    ,Radius(radius)
{
}

// @brief Sphere�ړ����� //
void Sphere::Move(const VECTOR& pos)
{
    worldCenter = localCenter + pos;        //���[���h���S���W�ړ�
}

//---�J�v�Z�������蔻��֘A---//
// @brief Capsule�R���X�g���N�^�[ //

Capsule::Capsule()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
    ,Radius(0.0f)
{
}

// @brief Capsule�R���X�g���N�^�[ //

Capsule::Capsule(const VECTOR& startPos, const VECTOR& endPos, float radius)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
    ,Radius(radius)
{
}

// @brief Capsule�ړ������@//

void Capsule::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //���[���h���W�n�_�ړ�
    worldEnd = localEnd + pos;              //���[���h���W�I�_�ړ�
}

// @brief ���̓��m�̓����蔻�� //

bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
{
    return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.Radius,
        sphere2.worldCenter, sphere2.Radius);
}

// @brief ���������̓����蔻�� //

bool CollisionPair(const Line& line, const Sphere& sphere)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

// @brief ���́����������蔻�� //

bool CollisionPair(const Sphere& sphere, const Line& line)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

// @brief ���������f�������蔻�� //

bool CollisionPair(const Line& line, const int modelHandle, MV1_COLL_RESULT_POLY& colInfo)
{
    colInfo = MV1CollCheck_Line(modelHandle, -1,
        line.worldStart, line.worldEnd);
    return colInfo.HitFlag;
}

// @brief ��^&���W�����蔻�� //

bool CollisionPair(const Fan& fan, const VECTOR& targetPos, const VECTOR& dir)
{
    VECTOR direction=targetPos - fan.worldCenter;
    float targetLength = VSize(direction);
    if (fan.Radius > targetLength)
    {
        float dot = VDot(direction, dir);
        if (dot<dir.x * cosf(fan.Radius) && dot>dir.z * sinf(fan.Radius))
        {
            return true;
        }
    }
    return false;
}

// @brief ���f�������������蔻�� //

bool CollisionPair( const int modelHandle,const Line& line, MV1_COLL_RESULT_POLY& colInfo)
{
    return CollisionPair(line, modelHandle, colInfo);
}

// @brief ���́����f�������蔻�� //

bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& colInfo)
{
    colInfo = MV1CollCheck_Sphere(modelHandle, -1, sphere.worldCenter, sphere.Radius);
    if (colInfo.HitNum == 0)
    {
        return false;
    }
    return true;
}

// @brief ���́����f�������蔻�艟���߂��ʎZ�o //

VECTOR CalcSpherePushBackFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& colInfo)
{
    VECTOR planeNormal;                //���ʖ@��
    VECTOR pushOut;                    //�����o��
    VECTOR canditateCenter = sphere.worldCenter;                                           //�����S�������̂̒��S���W�ɂ��� 
    float Rad = sphere.Radius;                                                            //�����a

    VECTOR canditateMove = sphere.worldCenter;                                             //�ړ��������̂̒��S���W�ɂ���


    // �Փ˃|���S�������ׂĉ���āA���̂߂荞�݂���������
    for (int i = 0; i < colInfo.HitNum; ++i)                                        //�Փ˃|���S�����߂荞�݉���
    {
        //---�Փ˃|���S���̕�---// 
        VECTOR edge1, edge2;                                                        //�Փ˃|���S���̕�
        edge1 = colInfo.Dim[i].Position[1] - colInfo.Dim[i].Position[0];            //��pos0�Epos1�x�N�g��
        edge2 = colInfo.Dim[i].Position[2] - colInfo.Dim[i].Position[0];            //��pos0�Epos2�x�N�g��

        planeNormal = VCross(edge1, edge2);                                         //�ӂ���|���S���ʂ̖@���x�N�g���Z�o
        planeNormal = VNorm(planeNormal);                                           //�@���x�N�g�����K��

        //---�����S�ɍł��߂��|���S�����ʂ̓_���Z�o---//
        VECTOR calc1, calc2;                                                        //�Z�o
        // �����S�ɍł��߂��|���S�����ʂ̓_�����߂�
        calc1 = canditateCenter - colInfo.Dim[i].Position[0];                       //��pos0�E�����S�x�N�g��
        float  dot = VDot(planeNormal, calc1);                                      //�@���ƕӂ̓���

        VECTOR hitPos = canditateCenter - planeNormal * dot;                        //�Փ˓_

        //--���̂߂荞�ݗʎZ�o---//
        calc2 = canditateCenter - hitPos;                                           //�ӏՓ˓_�E�����S�x�N�g��
        float  len = VSize(calc2);                                                  //�߂荞�ݗʂ̑傫��

        //---���S�����߂�---//
        if (HitCheck_Sphere_Triangle(canditateCenter, Rad,
            colInfo.Dim[i].Position[0],
            colInfo.Dim[i].Position[1],
            colInfo.Dim[i].Position[2]) == TRUE)                                    //�����߂荞��ł�����
        {
            VECTOR moveVec;
            len = Rad - len;                                                        //�����a����߂荞�ݗʂ��������傫��
            moveVec = planeNormal * len;                                            //�ړ��ʎZ�o
            canditateCenter += moveVec;                                             //�����S�����߂�
        }
    }

    canditateMove = canditateCenter;                                                //�ړ������ړ��ʒu��

    return canditateMove - sphere.worldCenter;                                      // �����߂��ʂ�ԋp
}
