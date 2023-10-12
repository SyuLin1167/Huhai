#include "Collision.h"

/// <summary>
/// Line�R���X�g���N�^
/// </summary>
Line::Line()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
{
}

/// <summary>
/// Line�R���X�g���N�^
/// </summary>
/// <param name="startPos">:�n�_</param>
/// <param name="endPos">:�I�_</param>
Line::Line(const VECTOR& startPos, const VECTOR& endPos)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
{
}

/// <summary>
/// Line�ړ�����
/// </summary>
/// <param name="pos">:�����̈ړ����W</param>
void Line::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //���[���h���W�n�_�ړ�
    worldEnd = localEnd + pos;              //���[���h���W�I�_�ړ�
}

/// <summary>
/// Sphere�R���X�g���N�^
/// </summary>
Sphere::Sphere()
    :localCenter()
    ,worldCenter()
    ,Radius(0.0f)
{
}

/// <summary>
/// Sphere�R���X�g���N�^
/// </summary>
/// <param name="center">:���S���W</param>
/// <param name="radius">:���a</param>
Sphere::Sphere(const VECTOR& center,float radius)
    :localCenter(center)
    ,worldCenter(center)
    ,Radius(radius)
{
}

/// <summary>
/// Sphere�ړ�����
/// </summary>
/// <param name="pos">:���̂̈ړ����W</param>
void Sphere::Move(const VECTOR& pos)
{
    worldCenter = localCenter + pos;        //���[���h���S���W�ړ�
}

/// <summary>
/// Capsule�R���X�g���N�^
/// </summary>
Capsule::Capsule()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
    ,Radius(0.0f)
{
}

/// <summary>
/// Capsule�R���X�g���N�^
/// </summary>
/// <param name="startPos">:�n�_</param>
/// <param name="endPos">:�I�_</param>
/// <param name="radius">:���a</param>
Capsule::Capsule(const VECTOR& startPos, const VECTOR& endPos, float radius)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
    ,Radius(radius)
{
}

/// <summary>
/// Capsule�ړ�����
/// </summary>
/// <param name="pos">:�J�v�Z���̈ړ����W</param>
void Capsule::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //���[���h���W�n�_�ړ�
    worldEnd = localEnd + pos;              //���[���h���W�I�_�ړ�
}

/// <summary>
/// ���̓��m�̓����蔻��
/// </summary>
/// <param name="sphere1">:����1</param>
/// <param name="sphere2">:����2</param>
/// <returns>�Ԃ����Ă��邩�ǂ���</returns>
bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
{
    return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.Radius,
        sphere2.worldCenter, sphere2.Radius);
}

/// <summary>
/// ���������̓����蔻��
/// </summary>
/// <param name="line">:����</param>
/// <param name="sphere">:����</param>
/// <returns>�Ԃ����Ă��邩�ǂ���</returns>
bool CollisionPair(const Line& line, const Sphere& sphere)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

/// <summary>
/// ���́����������蔻��
/// </summary>
/// <param name="sphere">:����</param>
/// <param name="line">:����</param>
/// <returns>�Ԃ����Ă��邩�ǂ���</returns>
bool CollisionPair(const Sphere& sphere, const Line& line)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

/// <summary>
/// ���������f�������蔻��
/// </summary>
/// <param name="line">:����</param>
/// <param name="modelHandle">:���f���n���h��</param>
/// <param name="colInfo">:�����蔻����</param>
/// <returns>�Ԃ����Ă��邩�ǂ���</returns>
bool CollisionPair(const Line& line, const int modelHandle, MV1_COLL_RESULT_POLY& colInfo)
{
    colInfo = MV1CollCheck_Line(modelHandle, -1,
        line.worldStart, line.worldEnd);
    return colInfo.HitFlag;
}

/// <summary>
/// ���f�������������蔻��
/// </summary>
/// <param name="modelHandle">:���f���n���h��</param>
/// <param name="line">:����</param>
/// <param name="colInfo">:�����蔻����</param>
/// <returns>�Ԃ����Ă��邩�ǂ���</returns>
bool CollisionPair( const int modelHandle,const Line& line, MV1_COLL_RESULT_POLY& colInfo)
{
    return CollisionPair(line, modelHandle, colInfo);
}

/// <summary>
/// ���́����f�������蔻��
/// </summary>
/// <param name="sphere">:����</param>
/// <param name="modelHandle">:���f���n���h��</param>
/// <param name="colInfo">:�����蔻����</param>
/// <returns>�Ԃ����Ă��邩�ǂ���</returns>
bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& colInfo)
{
    colInfo = MV1CollCheck_Sphere(modelHandle, -1, sphere.worldCenter, sphere.Radius);
    if (colInfo.HitNum == 0)
    {
        return false;
    }
    return true;
}

/// <summary>
/// ���́����f�������蔻�艟���߂��ʎZ�o
/// </summary>
/// <param name="sphere">:����</param>
/// <param name="colInfo">:�����蔻����</param>
/// <returns>�����߂���</returns>
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