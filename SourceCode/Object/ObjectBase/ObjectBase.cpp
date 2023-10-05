#include "ObjectBase.h"

// コンストラクタ //

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

// デストラクタ //

ObjBase::~ObjBase()
{
}

// jsonファイ理読み込み処理 //

void ObjBase::LoadJsonFile(std::string fileName)
{
    //ファイル読み込み
    std::ifstream ifs(fileName.c_str());

    //ファイル解析
    if (ifs.good())
    {
        rapidjson::IStreamWrapper isw(ifs);

        doc.ParseStream(isw);
    }
    ifs.close();
}

// Collision更新処理 //

void ObjBase::ColUpdate()
{
    //全当たり判定更新
    colLine.Move(objPos);
    colSphere.Move(objPos);
    colCapsule.Move(objPos);

    if (colModel != -1)
    {
        MV1SetPosition(colModel, objPos);
        MV1SetupCollInfo(colModel);
    }
}