#include "ObjectBase.h"

// �R���X�g���N�^ //

ObjBase::ObjBase(ObjectTag tag)
    :objTag(tag)
    , objHandle(-1)
    , objPos(VGet(0,0,0))
    , objDir(VGet(1.0f, 0.0f, 0.0f))
    , objScale(VGet(0.1f, 0.1f, 0.1f))
    , objSpeed(20.0f)
    , isVisible(true)
    , isAlive(true)
    , colType()
    , colLine()
    , colSphere()
    , colCapsule()
    , colModel(-1)
{
}

// �f�X�g���N�^ //

ObjBase::~ObjBase()
{
}

// json�t�@�C���ǂݍ��ݏ��� //

void ObjBase::LoadJsonFile(std::string fileName)
{
    //�t�@�C���ǂݍ���
    std::ifstream ifs(fileName.c_str());

    //�t�@�C�����
    if (ifs.good())
    {
        rapidjson::IStreamWrapper isw(ifs);

        doc.ParseStream(isw);
    }
    ifs.close();
}

// Collision�X�V���� //

void ObjBase::ColUpdate()
{
    //�S�����蔻��X�V
    colLine.Move(objPos);
    colSphere.Move(objPos);
    colCapsule.Move(objPos);

    if (colModel != -1)
    {
        MV1SetPosition(colModel, objPos);
        MV1SetupCollInfo(colModel);
    }
}