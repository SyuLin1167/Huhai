#pragma once
#include<DxLib.h>

#include"ObjectTag.h"
#include"../../Math/Math.h"
#include"../../Collision/Collision.h"
#include"../../Collision/CollisionType.h"

constexpr auto SCREEN_WIDTH = 1920;       //�X�N���[�����w��
constexpr auto SCREEN_HEIGHT = 1080;      //�X�N���[�������w��
//---�X�N���[���T�C�Y�̗�: 640*480, 800*600, 1024*768, 1280*1024, 1280*720, 1920*1080---//

/*�e�N���X*/
class ObjectBase
{
public:
    /// <summary>
    /// �R���X�g���N�^�\
    /// </summary>
    /// <param name="tag">:�^�O</param>
    ObjectBase(ObjectTag tag);

    /// <summary>
    /// �R���X�g���N�^�\(�ʒu�E�����Z�b�g)
    /// </summary>
    /// <param name="tag">:�^�O</param>
    /// <param name="pos">:���W</param>
    /// <param name="angle">:����</param>
    ObjectBase(ObjectTag tag, VECTOR pos, VECTOR angle = { 0,0,0 });
    
    /// <summary>
    /// �f�X�g���N�^�[
    /// </summary>
    virtual ~ObjectBase();

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
    bool IsVisible() { return isVisible; }

    /// <summary>
    /// �����ݒ�
    /// </summary>
    /// <param name="visible">�����邩�ǂ���</param>
    void SetVisible(bool visible) { isVisible = visible; }

    /// <summary>
    /// ��������
    /// </summary>
    /// <returns>�������</returns>
    bool IsAlive() { return isAlive; }

    /// <summary>
    /// �����ݒ�
    /// </summary>
    /// <param name="alive">:�����Ă��邩�ǂ���</param>
    void SetAlive(bool alive) { isAlive = alive; }


    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    virtual void Update(float deltaTime) = 0;

    /// <summary>
    /// �`�揈��
    /// </summary>
    virtual void Draw();

    /// <summary>
    /// �I�u�W�F�N�g�̃^�O�擾
    /// </summary>
    /// <returns>�^�O���</returns>
    ObjectTag GetTag()const { return objTag; }

    //---�����蔻��֘A---//

    /// <summary>
    /// �Փˎ�����
    /// </summary>
    /// <param name="other">:�I�u�W�F�N�g</param>
    virtual void OnCollisionEnter(const ObjectBase*other){}

    /// <summary>
    /// �I�u�W�F�N�g�Ƃ̓����蔻��
    /// </summary>
    /// <param name="other">:�I�u�W�F�N�g</param>
    virtual void ColWithOther(ObjectBase* other) {};

    /// <summary>
    /// �I�u�W�F�N�g�̓����蔻���
    /// </summary>
    /// <returns>�����蔻���</returns>
    CollisionType GetColType()const { return colType; }

    /// <summary>
    /// ���������蔻��
    /// </summary>
    /// <returns>�����蔻��Line</returns>
    Line GetColLine()const { return colLine; }

    /// <summary>
    /// �������蔻��
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

protected:
    /// <summary>
    /// Collision�X�V����
    /// </summary>
    void ColUpdate();

    /// <summary>
    /// Collision�`�揈��
    /// </summary>
    void ColDraw();

    ObjectTag objTag;                           //�I�u�W�F�N�g�̎��
    int objHandle;                              //���f���n���h��
    VECTOR objPos;                              //���[���h���W
    VECTOR objDir;                              //���[���h����
    VECTOR objScale;                            //�I�u�W�F�N�g�̑傫��

    float objSpeed;                             //�I�u�W�F�N�g�̑��x

    bool isVisible;                             //�������
    bool isAlive;                               //�������

    //---�����蔻��֘A---//
    CollisionType colType;                      //�����蔻���
    Line colLine;                    //�����蔻��Line
    Sphere colSphere;                //�����蔻��Sphere
    Capsule colCapsule;              //�����蔻��Capsule
    int colModel;                               //�����蔻��Model
};

