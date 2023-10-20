#pragma once
#include<DxLib.h>

#include"ObjTag.h"
#include"../../Math/Math.h"
#include"../../Collision/Collision.h"
#include"../../Collision/CollisionType.h"

/// <summary>
/// ObjBase�N���X
/// </summary>
class ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="tag">:�I�u�W�F�N�g�^�O</param>
    ObjBase(ObjTag tag);


    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ObjBase();

    /// <summary>
    /// ���W�擾
    /// </summary>
    /// <returns>�Z�b�g���ꂽ���W</returns>
    const VECTOR& GetPos()const { return objPos; }

    /// <summary>
    /// ���W�ݒ�
    /// </summary>
    /// <param name="setPos">:���W�ɃZ�b�g����l</param>
    void SetPos(const VECTOR setPos) { objPos = setPos; }

    /// <summary>
    /// �����擾
    /// </summary>
    /// <returns>�Z�b�g���ꂽ����</returns>
    const VECTOR& GetDir()const { return objDir; }

    /// <summary>
    /// �����ݒ�
    /// </summary>
    /// <param name="dir">:�����ɃZ�b�g����l</param>
    void SetDir(const VECTOR dir) { objDir = dir; }

    /// <summary>
    /// ��������
    /// </summary>
    /// <returns>�������</returns>
    bool IsVisible()const { return isVisible; }

    /// <summary>
    /// �����ݒ�
    /// </summary>
    /// <param name="visible">�����邩�ǂ���</param>
    void SetVisible(const bool visible) { isVisible = visible; }

    /// <summary>
    /// ��������
    /// </summary>
    /// <returns>�������</returns>
    bool IsAlive()const { return isAlive; }

    /// <summary>
    /// �����ݒ�
    /// </summary>
    /// <param name="alive">:�����Ă��邩�ǂ���</param>
    void SetAlive(const bool alive) { isAlive = alive; }

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    virtual void Update(const float deltaTime) = 0;

    /// <summary>
    /// �`�揈��
    /// </summary>
    virtual void Draw() = 0;

    /// <summary>
    /// �I�u�W�F�N�g�̃^�O�擾
    /// </summary>
    /// <returns>�^�O���</returns>
    ObjTag GetTag()const { return objTag; }

    /// <summary>
    /// �Փˎ�����
    /// </summary>
    /// <param name="other">:�I�u�W�F�N�g</param>
    virtual void OnCollisionEnter(const ObjBase* other) {}

    /// <summary>
    /// �����蔻���
    /// </summary>
    /// <returns>�����蔻���</returns>
    CollisionType GetColType()const { return colType; }

    /// <summary>
    /// ���������蔻��
    /// </summary>
    /// <returns>�����蔻��Line</returns>
    Line GetColLine()const { return colLine; }

    /// <summary>
    /// ���̓����蔻��
    /// </summary>
    /// <returns>�����蔻��Sphere</returns>
    Sphere GetColSphere()const { return colSphere; }

    /// <summary>
    /// �J�v�Z�������蔻��
    /// </summary>
    /// <returns>�����蔻��Capsule</returns>
    Capsule GetColCapsule()const { return colCapsule; }

    /// <summary>
    /// ���f�������蔻��
    /// </summary>
    /// <returns>�����蔻��Model</returns>
    int GetColModel()const { return colModel; }


    /// <summary>
    /// ��]����
    /// </summary>
    void Rotate();

protected:
    /// <summary>
    /// Collision�X�V����
    /// </summary>
    void ColUpdate();

    const float PI_DEGREE = 180.0f;             //180�x
    const float ONE_HALF_PI_DEGREE = 90.0f;     //90�x
    const float ROTATE_VELOCITY = 5.0f;         //��]���x
    bool rotateNow;                             //��]���
    VECTOR aimDir;                              //�ڕW����

    ObjTag objTag;                              //�I�u�W�F�N�g�^�O
    int objHandle;                              //�I�u�W�F�N�g�n���h��
    VECTOR objPos;                              //���[���h���W
    VECTOR objDir;                              //���[���h����
    VECTOR objScale;                            //�I�u�W�F�N�g�T�C�Y

    float objSpeed;                             //�ړ����x

    bool isVisible;                             //�������
    bool isAlive;                               //�������

    CollisionType colType;                      //�����蔻���
    Line colLine;                               //����
    Sphere colSphere;                           //����
    Capsule colCapsule;                         //�J�v�Z��
    int colModel;                               //���f��
};

