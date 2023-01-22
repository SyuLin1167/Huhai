#include "Collision.h"

//---線分当たり判定関連---//
// @brief Lineコンストラクター //

Line::Line()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
{
}

// @brief Lineコンストラクター(引数付) //

Line::Line(const VECTOR& startPos, const VECTOR& endPos)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
{
}

// @brief Line移動処理 //

void Line::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //ワールド座標始点移動
    worldEnd = localEnd + pos;              //ワールド座標終点移動
}

//---扇型当たり判定関連---//
// @brief Fanコンストラクター //

Fan::Fan()
    :localCenter()
    , worldCenter()
    , Range()
    , Radius()
{
}

// @brief Fanコンストラクター(引数付) //

Fan::Fan(const VECTOR& center, float radius)
    :localCenter(center)
    , worldCenter(center)
    , Range()
    , Radius(radius)
{
}

// @brief Fan移動処理 //

void Fan::Move(const VECTOR& pos)
{
    worldCenter = localCenter + pos;        //ワールド中心座標移動
}

//---球体当たり判定関連---//
// @brief Sphereコンストラクター //

Sphere::Sphere()
    :localCenter()
    ,worldCenter()
    ,Radius(0.0f)
{
}

// @brief Sphereコンストラクター(引数付)

Sphere::Sphere(const VECTOR& center,float radius)
    :localCenter(center)
    ,worldCenter(center)
    ,Radius(radius)
{
}

// @brief Sphere移動処理 //
void Sphere::Move(const VECTOR& pos)
{
    worldCenter = localCenter + pos;        //ワールド中心座標移動
}

//---カプセル当たり判定関連---//
// @brief Capsuleコンストラクター //

Capsule::Capsule()
    :localStart()
    ,localEnd()
    ,worldStart()
    ,worldEnd()
    ,Radius(0.0f)
{
}

// @brief Capsuleコンストラクター //

Capsule::Capsule(const VECTOR& startPos, const VECTOR& endPos, float radius)
    :localStart(startPos)
    ,localEnd(endPos)
    ,worldStart(startPos)
    ,worldEnd(endPos)
    ,Radius(radius)
{
}

// @brief Capsule移動処理　//

void Capsule::Move(const VECTOR& pos)
{
    worldStart = localStart + pos;          //ワールド座標始点移動
    worldEnd = localEnd + pos;              //ワールド座標終点移動
}

// @brief 球体同士の当たり判定 //

bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
{
    return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.Radius,
        sphere2.worldCenter, sphere2.Radius);
}

// @brief 線分＆球体当たり判定 //

bool CollisionPair(const Line& line, const Sphere& sphere)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

// @brief 球体＆線分当たり判定 //

bool CollisionPair(const Sphere& sphere, const Line& line)
{
    return HitCheck_Line_Sphere(line.worldStart, line.worldEnd,
        sphere.worldCenter, sphere.Radius);
}

// @brief 線分＆モデル当たり判定 //

bool CollisionPair(const Line& line, const int modelHandle, MV1_COLL_RESULT_POLY& colInfo)
{
    colInfo = MV1CollCheck_Line(modelHandle, -1,
        line.worldStart, line.worldEnd);
    return colInfo.HitFlag;
}

// @brief 扇型&座標当たり判定 //

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

// @brief モデル＆線分当たり判定 //

bool CollisionPair( const int modelHandle,const Line& line, MV1_COLL_RESULT_POLY& colInfo)
{
    return CollisionPair(line, modelHandle, colInfo);
}

// @brief 球体＆モデル当たり判定 //

bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& colInfo)
{
    colInfo = MV1CollCheck_Sphere(modelHandle, -1, sphere.worldCenter, sphere.Radius);
    if (colInfo.HitNum == 0)
    {
        return false;
    }
    return true;
}

// @brief 球体＆モデル当たり判定押し戻し量算出 //

VECTOR CalcSpherePushBackFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& colInfo)
{
    VECTOR planeNormal;                //平面法線
    VECTOR pushOut;                    //押し出し
    VECTOR canditateCenter = sphere.worldCenter;                                           //球中心候補を球体の中心座標にする 
    float Rad = sphere.Radius;                                                            //球半径

    VECTOR canditateMove = sphere.worldCenter;                                             //移動候補を球体の中心座標にする


    // 衝突ポリゴンをすべて回って、球のめり込みを解消する
    for (int i = 0; i < colInfo.HitNum; ++i)                                        //衝突ポリゴン分めり込み解消
    {
        //---衝突ポリゴンの辺---// 
        VECTOR edge1, edge2;                                                        //衝突ポリゴンの辺
        edge1 = colInfo.Dim[i].Position[1] - colInfo.Dim[i].Position[0];            //辺pos0・pos1ベクトル
        edge2 = colInfo.Dim[i].Position[2] - colInfo.Dim[i].Position[0];            //辺pos0・pos2ベクトル

        planeNormal = VCross(edge1, edge2);                                         //辺からポリゴン面の法線ベクトル算出
        planeNormal = VNorm(planeNormal);                                           //法線ベクトル正規化

        //---球中心に最も近いポリゴン平面の点を算出---//
        VECTOR calc1, calc2;                                                        //算出
        // 球中心に最も近いポリゴン平面の点を求める
        calc1 = canditateCenter - colInfo.Dim[i].Position[0];                       //辺pos0・球中心ベクトル
        float  dot = VDot(planeNormal, calc1);                                      //法線と辺の内積

        VECTOR hitPos = canditateCenter - planeNormal * dot;                        //衝突点

        //--球のめり込み量算出---//
        calc2 = canditateCenter - hitPos;                                           //辺衝突点・球中心ベクトル
        float  len = VSize(calc2);                                                  //めり込み量の大きさ

        //---中心押し戻し---//
        if (HitCheck_Sphere_Triangle(canditateCenter, Rad,
            colInfo.Dim[i].Position[0],
            colInfo.Dim[i].Position[1],
            colInfo.Dim[i].Position[2]) == TRUE)                                    //球がめり込んでいたら
        {
            VECTOR moveVec;
            len = Rad - len;                                                        //球半径からめり込み量を引いた大きさ
            moveVec = planeNormal * len;                                            //移動量算出
            canditateCenter += moveVec;                                             //球中心押し戻し
        }
    }

    canditateMove = canditateCenter;                                                //移動候補を移動位置に

    return canditateMove - sphere.worldCenter;                                      // 押し戻し量を返却
}
