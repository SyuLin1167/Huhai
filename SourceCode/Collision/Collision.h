#pragma once
#include<DxLib.h>
#include<math.h>
#include"../Math/Math.h"


    /*�����̍\����*/
    struct Line
    {
        /// <summary>
        /// Line�R���X�g���N�^�[
        /// </summary>
        Line();

        /// <summary>
        /// Line�R���X�g���N�^�[
        /// </summary>
        /// <param name="startPos">:�n�_</param>
        /// <param name="endPos">:�I�_</param>
        Line(const VECTOR& startPos, const VECTOR& endPos);

        /// <summary>
        /// Line�ړ�����
        /// </summary>
        /// <param name="pos">:�����̈ړ����W</param>
        void Move(const VECTOR& pos);

        VECTOR localStart;                  //�����̃��[�J�����W�n�_
        VECTOR localEnd;                    //�����̃��[�J�����W�I�_
        VECTOR worldStart;                  //�����̃��[���h���W�n�_
        VECTOR worldEnd;                    //�����̃��[���h���W�I�_
    };

    /*���̂̍\����*/
    struct Sphere
    {
        /// <summary>
        /// Sphere�R���X�g���N�^�[
        /// </summary>
        Sphere();

        /// <summary>
        /// Sphere�R���X�g���N�^�[(�����t)
        /// </summary>
        /// <param name="center">:���S���W</param>
        /// <param name="radius">:���a</param>
        Sphere(const VECTOR& center, float radius);

        /// <summary>
        /// Sphere�ړ�����
        /// </summary>
        /// <param name="pos">:���̂̈ړ����W</param>
        void Move(const VECTOR& pos);

        VECTOR localCenter;                 //���̂̃��[�J�����S���W
        VECTOR worldCenter;                 //���̂̃��[���h���S���W
        float Radius;                       //���̂̔��a
    };

    /*�J�v�Z���̍\����*/
    struct Capsule
    {
        /// <summary>
        /// Capsule�R���X�g���N�^�[
        /// </summary>
        Capsule();

        /// <summary>
        /// Capsule�R���X�g���N�^�[
        /// </summary>
        /// <param name="startPos">:�n�_</param>
        /// <param name="endPos">:�I�_</param>
        /// <param name="radius">:���a</param>
        Capsule(const VECTOR& startPos, const VECTOR& endPos, float radius);

        /// <summary>
        /// Capsule�ړ�����
        /// </summary>
        /// <param name="pos">:�J�v�Z���̈ړ����W</param>
        void Move(const VECTOR& pos);

        VECTOR localStart;                  //�J�v�Z���̃��[�J�����W�n�_
        VECTOR localEnd;                    //�J�v�Z���̃��[�J�����W�I�_
        VECTOR worldStart;                  //�J�v�Z���̃��[���h���W�n�_
        VECTOR worldEnd;                    //�J�v�Z���̃��[���h���W�I�_
        float Radius;                       //�J�v�Z���̔��a
    };

    /// <summary>
    /// ���̓��m�̓����蔻��
    /// </summary>
    /// <param name="sphere1">:����1</param>
    /// <param name="sphere2">:����2</param>
    /// <returns>�Ԃ����Ă��邩�ǂ���</returns>
    bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2);

    /// <summary>
    /// ���������̓����蔻��
    /// </summary>
    /// <param name="line">:����</param>
    /// <param name="sphere">:����</param>
    /// <returns>�Ԃ����Ă��邩�ǂ���</returns>
    bool CollisionPair(const Line& line, const Sphere& sphere);

    /// <summary>
    /// ���́����������蔻��
    /// </summary>
    /// <param name="sphere">:����</param>
    /// <param name="line">:����</param>
    /// <returns>�Ԃ����Ă��邩�ǂ���</returns>
    bool CollisionPair(const Sphere& sphere, const Line& line);

    /// <summary>
    /// ���������f�������蔻��
    /// </summary>
    /// <param name="line">:����</param>
    /// <param name="modelHandle">:���f���n���h��</param>
    /// <param name="colInfo">:�����蔻����</param>
    /// <returns>�Ԃ����Ă��邩�ǂ���</returns>
    bool CollisionPair(const Line& line, const int modelHandle,MV1_COLL_RESULT_POLY& colInfo);

    /// <summary>
    /// ���f�������������蔻��
    /// </summary>
    /// <param name="modelHandle">:���f���n���h��</param>
    /// <param name="line">:����</param>
    /// <param name="colInfo">:�����蔻����</param>
    /// <returns>�Ԃ����Ă��邩�ǂ���</returns>
    bool CollisionPair(const int modelHandle, const Line& line,MV1_COLL_RESULT_POLY& colInfo);

    /// <summary>
    /// ���́����f�������蔻��
    /// </summary>
    /// <param name="sphere">:����</param>
    /// <param name="modelHandle">:���f���n���h��</param>
    /// <param name="colInfo">:�����蔻����</param>
    /// <returns>�Ԃ����Ă��邩�ǂ���</returns>
    bool CollisionPair(const Sphere& sphere, const int modelHandle,MV1_COLL_RESULT_POLY_DIM& colInfo);

    /// <summary>
    /// ���́����f�������蔻�艟���߂��ʎZ�o
    /// </summary>
    /// <param name="sphere">:����</param>
    /// <param name="colInfo">:�����蔻����</param>
    /// <returns>�����߂���</returns>
    VECTOR CalcSpherePushBackFromMesh(const Sphere& sphere,const MV1_COLL_RESULT_POLY_DIM& colInfo);
