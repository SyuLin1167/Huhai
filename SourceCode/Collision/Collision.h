#pragma once
#include<DxLib.h>
#include<math.h>
#include"../Math/Math.h"


    /*線分の構造体*/
    struct Line
    {
        /// <summary>
        /// Lineコンストラクター
        /// </summary>
        Line();

        /// <summary>
        /// Lineコンストラクター
        /// </summary>
        /// <param name="startPos">:始点</param>
        /// <param name="endPos">:終点</param>
        Line(const VECTOR& startPos, const VECTOR& endPos);

        /// <summary>
        /// Line移動処理
        /// </summary>
        /// <param name="pos">:線分の移動座標</param>
        void Move(const VECTOR& pos);

        VECTOR localStart;                  //線分のローカル座標始点
        VECTOR localEnd;                    //線分のローカル座標終点
        VECTOR worldStart;                  //線分のワールド座標始点
        VECTOR worldEnd;                    //線分のワールド座標終点
    };

    /*球体の構造体*/
    struct Sphere
    {
        /// <summary>
        /// Sphereコンストラクター
        /// </summary>
        Sphere();

        /// <summary>
        /// Sphereコンストラクター(引数付)
        /// </summary>
        /// <param name="center">:中心座標</param>
        /// <param name="radius">:半径</param>
        Sphere(const VECTOR& center, float radius);

        /// <summary>
        /// Sphere移動処理
        /// </summary>
        /// <param name="pos">:球体の移動座標</param>
        void Move(const VECTOR& pos);

        VECTOR localCenter;                 //球体のローカル中心座標
        VECTOR worldCenter;                 //球体のワールド中心座標
        float Radius;                       //球体の半径
    };

    /*カプセルの構造体*/
    struct Capsule
    {
        /// <summary>
        /// Capsuleコンストラクター
        /// </summary>
        Capsule();

        /// <summary>
        /// Capsuleコンストラクター
        /// </summary>
        /// <param name="startPos">:始点</param>
        /// <param name="endPos">:終点</param>
        /// <param name="radius">:半径</param>
        Capsule(const VECTOR& startPos, const VECTOR& endPos, float radius);

        /// <summary>
        /// Capsule移動処理
        /// </summary>
        /// <param name="pos">:カプセルの移動座標</param>
        void Move(const VECTOR& pos);

        VECTOR localStart;                  //カプセルのローカル座標始点
        VECTOR localEnd;                    //カプセルのローカル座標終点
        VECTOR worldStart;                  //カプセルのワールド座標始点
        VECTOR worldEnd;                    //カプセルのワールド座標終点
        float Radius;                       //カプセルの半径
    };

    /// <summary>
    /// 球体同士の当たり判定
    /// </summary>
    /// <param name="sphere1">:球体1</param>
    /// <param name="sphere2">:球体2</param>
    /// <returns>ぶつかっているかどうか</returns>
    bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2);

    /// <summary>
    /// 線分＆球体当たり判定
    /// </summary>
    /// <param name="line">:線分</param>
    /// <param name="sphere">:球体</param>
    /// <returns>ぶつかっているかどうか</returns>
    bool CollisionPair(const Line& line, const Sphere& sphere);

    /// <summary>
    /// 球体＆線分当たり判定
    /// </summary>
    /// <param name="sphere">:球体</param>
    /// <param name="line">:線分</param>
    /// <returns>ぶつかっているかどうか</returns>
    bool CollisionPair(const Sphere& sphere, const Line& line);

    /// <summary>
    /// 線分＆モデル当たり判定
    /// </summary>
    /// <param name="line">:線分</param>
    /// <param name="modelHandle">:モデルハンドル</param>
    /// <param name="colInfo">:当たり判定情報</param>
    /// <returns>ぶつかっているかどうか</returns>
    bool CollisionPair(const Line& line, const int modelHandle,MV1_COLL_RESULT_POLY& colInfo);

    /// <summary>
    /// モデル＆線分当たり判定
    /// </summary>
    /// <param name="modelHandle">:モデルハンドル</param>
    /// <param name="line">:線分</param>
    /// <param name="colInfo">:当たり判定情報</param>
    /// <returns>ぶつかっているかどうか</returns>
    bool CollisionPair(const int modelHandle, const Line& line,MV1_COLL_RESULT_POLY& colInfo);

    /// <summary>
    /// 球体＆モデル当たり判定
    /// </summary>
    /// <param name="sphere">:球体</param>
    /// <param name="modelHandle">:モデルハンドル</param>
    /// <param name="colInfo">:当たり判定情報</param>
    /// <returns>ぶつかっているかどうか</returns>
    bool CollisionPair(const Sphere& sphere, const int modelHandle,MV1_COLL_RESULT_POLY_DIM& colInfo);

    /// <summary>
    /// 球体＆モデル当たり判定押し戻し量算出
    /// </summary>
    /// <param name="sphere">:球体</param>
    /// <param name="colInfo">:当たり判定情報</param>
    /// <returns>押し戻し量</returns>
    VECTOR CalcSpherePushBackFromMesh(const Sphere& sphere,const MV1_COLL_RESULT_POLY_DIM& colInfo);
