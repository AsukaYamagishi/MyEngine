#pragma once
#include "BaseCollider.h"
#include "../CollisionPrimitive.h"

class OBBCollider :
    public BaseCollider , public OBB
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="normalDirect">方向ベクトル</param>
    /// <param name="length">長さ</param>
    /// <param name="name"></param>
    /// <param name="offset"></param>
    OBBCollider(DirectX::XMVECTOR normalDirect[3], float length[3], std::string name = "", DirectX::XMVECTOR offset = { 0,0,0,0 }) :
        offset(offset)
    {
        //OBBを示す符号を付与
        shapeType = CollisionShapeType::SHAPE_OBB;

        //各軸の長さをセット
        this->length[0] = length[0];
        this->length[1] = length[1];
        this->length[2] = length[2];

        //各軸の方向ベクトルをセット
        this->normalDirect[0] = normalDirect[0];
        this->normalDirect[1] = normalDirect[1];
        this->normalDirect[2] = normalDirect[2];

    }

    void Update() override;

    void SetOffset(DirectX::XMVECTOR offset) { this->offset = offset; }

private:
    DirectX::XMVECTOR offset = { 0,0,0,0 };
};

