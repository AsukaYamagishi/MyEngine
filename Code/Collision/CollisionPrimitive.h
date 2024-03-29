#pragma once
///<summary>
///当たり判定プリミティブ
///</summary>

#include <DirectXMath.h>

///<summary>
///球
///</summary>
struct Sphere {
	//中心座標
	DirectX::XMVECTOR centor = { 0,0,0 };
	//半径
	float radius = 1.0f;
};

///<summary>
///OBB
///</summary>
struct OBB {
	//中心座標
	DirectX::XMVECTOR centor = { 0,0,0 };
	//方向ベクトル
	DirectX::XMVECTOR normalDirect[3];
	//各軸方向の長さ
	float length[3];
};
///<summary>
///平面
///</summary>
struct Plane {
	//法線ベクトル
	DirectX::XMVECTOR normal = { 0,1,0 };
	//原点からの距離
	float distance = 0.0f;
};

///<summary>
///法線付き三角形(時計回りが表面)
///</summary>
class Triangle{
public:
	//頂点座標3つ
	DirectX::XMVECTOR p0;
	DirectX::XMVECTOR p1;
	DirectX::XMVECTOR p2;
	//法線ベクトル
	DirectX::XMVECTOR normal;
	//法線の計算
	void ComputeNormal();
};

/// <summary>
/// レイ
/// </summary>
struct Ray {
	//始点
	DirectX::XMVECTOR start = { 0,0,0,1 };
	//方向
	DirectX::XMVECTOR dir = { 1,0,0,0 };
};
