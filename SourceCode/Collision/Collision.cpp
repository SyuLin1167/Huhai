#include "Collision.h"

// @brief Collsionコンストラクター //

Collision::Collision()
    :canditateCenter{0,0,0}
    ,canditateMove{0,0,0}
    ,planeNormal{0,0,0}
    ,pushOut{0,0,0}
    ,Rad(0.0f)
{
}

// @brief Lineコンストラクター //

Collision::Line::Line()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
{
}

// @brief Lineコンストラクター(引数付) //

Collision::Line::Line(const VECTOR& startPos, const VECTOR& endPos)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
{
}

// @brief Line移動処理 //

void Collision::Line::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //ワールド座標始点移動
    worldEnd = localEnd + pos;              //ワールド座標終点移動
}

// @brief Sphereコンストラクター //

Collision::Sphere::Sphere()
    :localCenter()
    ,worldCenter()
    ,Radius(0.0f)
{
}

// @brief Sphereコンストラクター(引数付)

Collision::Sphere::Sphere(const VECTOR& center,float radius)
    :localCenter(center)
    ,worldCenter(center)
    ,Radius(radius)
{
}

// @brief Sphere移動処理 //
void Collision::Sphere::Move(const VECTOR& pos)
{
    worldCenter = localCenter + pos;        //ワールド中心座標移動
}

// @brief Capsuleコンストラクター //

Collision::Capsule::Capsule()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
    ,Radius(0.0f)
{
}

// @brief Capsuleコンストラクター //

Collision::Capsule::Capsule(const VECTOR& startPos, const VECTOR& endPos, float radius)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
    ,Radius(radius)
{
}

// @brief Capsule移動処理　//

void Collision::Capsule::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //ワールド座標始点移動
    worldEnd = localEnd + pos;              //ワールド座標終点移動
}

// @brief 球体同士の当たり判定 //

bool Collision::CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
{
    return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.Radius,
        sphere2.worldCenter, sphere2.Radius);
}

// @brief 線分＆球体当たり判定 //

bool Collision::CollisionPair(const Line& line, const Sphere& sphere)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

// @brief 球体＆線分当たり判定 //

bool Collision::CollisionPair(const Sphere& sphere, const Line& line)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

// @brief 線分＆モデル当たり判定 //

bool Collision::CollisionPair(const Line& line, const int modelHandle, MV1_COLL_RESULT_POLY& colInfo)
{
    colInfo = MV1CollCheck_Line(modelHandle, -1,
        line.worldStart, line.worldEnd);
    return colInfo.HitFlag;
}

// @brief モデル＆線分当たり判定 //

bool Collision::CollisionPair( const int modelHandle,const Line& line, MV1_COLL_RESULT_POLY& colInfo)
{
    return CollisionPair(line, modelHandle, colInfo);
}

// @brief 球体＆モデル当たり判定 //

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

// @brief 球体＆モデル当たり判定押し戻し量算出 //

VECTOR Collision::CalcSpherePushBackFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& colInfo)
{
    canditateCenter = sphere.worldCenter;                                           //球中心候補を球体の中心座標にする
    Rad = sphere.Radius;

    for (int i = 0 ; i < colInfo.HitNum ; i++)                                      //衝突ポリゴン分めり込み解消
    {
        VECTOR edge1, edge2;                                                        //衝突ポリゴンの辺
        edge1 = colInfo.Dim[i].Position[1] - colInfo.Dim[i].Position[0];            //辺pos0・pos1ベクトル
        edge2 = colInfo.Dim[i].Position[2] - colInfo.Dim[i].Position[0];            //辺pos0・pos2ベクトル

        planeNormal = VCross(edge1, edge2);                                  //辺からポリゴン面の法線ベクトル算出
        planeNormal = VNorm(planeNormal);                                        //法線ベクトル正規化

        VECTOR calc1, calc2;                                                        //算出

        //---球中心に最も近いポリゴン平面の点を算出---//
        calc1 = canditateCenter - colInfo.Dim[i].Position[0];                       //辺pos0・球中心ベクトル                   
        float dot = VDot(planeNormal, calc1);                                //法線と辺の内積

        VECTOR hitPos = canditateCenter - planeNormal * dot;                        //衝突点

        //--球のめり込み量算出---//
        calc2 = canditateCenter - hitPos;                                           //辺衝突点・球中心ベクトル
        float len = VSize(calc2);                                                //めり込み量の大きさ

        if (HitCheck_Sphere_Triangle(canditateCenter, Rad,
            colInfo.Dim[i].Position[0],
            colInfo.Dim[i].Position[1],
            colInfo.Dim[i].Position[2]) == TRUE)                          //球がめり込んでいたら
        {
            len = Rad - len;                                                        //球半径からめり込み量を引いた大きさ
            VECTOR moveVec = planeNormal * len;                                     //移動量算出
            canditateCenter += moveVec;                                             //球中心押し戻し
        }

        canditateMove = canditateCenter;                                            //移動候補を移動位置に

        return canditateMove - sphere.worldCenter;
    }

}
