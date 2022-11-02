#pragma once
#include <DirectXMath.h>
#include "Mathf.h"

using namespace DirectX;

struct Vector3 : public XMFLOAT3
{
#pragma region コンストラクタ
	Vector3(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3(const XMFLOAT3& num) {
		this->x = num.x;
		this->y = num.y;
		this->z = num.z;
	}
	Vector3(const XMVECTOR& other) :XMFLOAT3() {
		XMVECTOR temp = other;
		XMStoreFloat3(this, temp);
	}
#pragma endregion

#pragma region 静的メンバ変数
	static const Vector3 forward; //( 0, 0, 1) 前ベクトル
	static const Vector3 back;    //( 0, 0,-1) 後ろベクトル
	static const Vector3 up;	  //( 0, 1, 0) 上ベクトル
	static const Vector3 down;	  //( 0,-1, 0) 下ベクトル
	static const Vector3 right;	  //( 1, 0, 0) 右ベクトル
	static const Vector3 left;	  //(-1, 0, 0) 左ベクトル
	static const Vector3 zero;	  //( 0, 0, 0) ゼロベクトル
	static const Vector3 one;	  //( 1, 1, 1) 1(単位)ベクトル
	static const Vector3 positive_infinity; //( inf, inf, inf) 正の無限
	static const Vector3 negative_infinity; //(-inf,-inf,-inf) 負の無限

#pragma endregion

#pragma region 静的メンバ関数
	/// <summary>
	/// 2点間の角度を求める
	/// </summary>
	/// <param name="from">測定元ベクトル</param>
	/// <param name="to">測定先ベクトル</param>
	/// <returns>角度：degree（float）</returns>
	static float Angle(const Vector3& from, const Vector3& to);

	/// <summary>
	/// 2つのベクトルの内積
	/// </summary>
	/// <returns>内積（float）</returns>
	static float Dot(const Vector3& lhs, const Vector3& rhs);

	/// <summary>
	/// 2つのベクトルの外積
	/// </summary>
	/// <returns>外積（Vector3）</returns>
	static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

	/// <summary>
	/// 正規化ベクトルの作成（元値書き換え）
	/// </summary>
	/// <param name="valuse">正規化したいベクトル</param>
	/// <returns>作成した正規化ベクトル（Vector3）</returns>
	static Vector3 Nomalize(Vector3& valuse);

	/// <summary>
	/// 2つのベクトルの各成分から一番大きな値でベクトルを作成
	/// </summary>
	/// <returns>作成したベクトル（Vector3）</returns>
	static Vector3 Max(const Vector3& lhs, const Vector3& rhs);

	/// <summary>
	/// 2つのベクトルの各成分から一番小さな値でベクトルを作成
	/// </summary>
	/// <returns>作成したベクトル（Vector3）</returns>
	static Vector3 Min(const Vector3& lhs, const Vector3& rhs);

	/// <summary>
	/// 目標値まで指定した移動量で移動する
	/// </summary>
	/// <param name="current">現在値</param>
	/// <param name="target">目標値</param>
	/// <param name="max_distance_delta">1フレームで進む距離</param>
	/// <returns>移動結果（Vector3）</returns>
	static Vector3 MoveTowards(const Vector3& current, const Vector3& target, float max_distance_delta);

	/// <summary>
	/// ベクトルの大きさを制限
	/// </summary>
	/// <param name="vec">コピーするベクトル</param>
	/// <param name="max_length">最大の大きさ</param>
	/// <returns>大きさを max_length 以下に制限した vec のコピー</returns>
	static Vector3 ClampLength(const Vector3& vec, const float& max_length);

	/// <summary>
	/// 法線で定義された平面でベクトルを反射
	/// </summary>
	/// <param name="inDirection">平面に入る方向ベクトル</param>
	/// <param name="inNormal">平面を定義する正規化済みの垂直ベクトル</param>
	/// <returns>反射後のベクトル（Vector3）</returns>
	static Vector3 Reflect(const Vector3& inDirection, const Vector3& inNormal);

	/// <summary>
	/// 2点間の距離を求める
	/// </summary>
	/// <returns>2点間の距離（float）</returns>
	static float Distance(const Vector3& lhs, const Vector3& rhs);

	/// <summary>
	/// 2つのベクトルの各成分を乗算する
	/// </summary>
	/// <returns>乗算結果（Vector3）</returns>
	static Vector3 Scale(const Vector3& lhs, const Vector3& rhs);

#pragma endregion

#pragma region メンバ関数
	/// <summary>
	/// ベクトルの長さ
	/// </summary>
	/// <returns>ベクトルの長さ（float）</returns>
	float Length() const;

	/// <summary>
	/// ベクトルの長さの二乗
	/// </summary>
	/// <returns>ベクトルの長さの二乗（float）</returns>
	float SqrLength() const;

	/// <summary>
	/// 正規化ベクトル
	/// </summary>
	/// <returns>正規化ベクトル（Vector3）</returns>
	Vector3 Normalized() const;

	/// <summary>
	/// 2つのベクトルの内積(引数1つ)
	/// </summary>
	/// <returns>内積（float）</returns>
	float Dot(const Vector3& vec);

#pragma endregion

#pragma region 演算子
	//単項演算子
	Vector3 operator +() const { return *this; }
	Vector3 operator -() const
	{
		Vector3 temp = {
			-this->x,
			-this->y,
			-this->z
		};
		return temp;
	}

	//二項演算子
	Vector3 operator +(const Vector3& vec) const
	{
		Vector3 temp = {
			this->x + vec.x,
			this->y + vec.y,
			this->z + vec.z
		};
		return temp;
	}
	Vector3 operator -(const Vector3& vec) const { return *this + -vec; }
	Vector3& operator +=(const Vector3& vec) {
		*this = *this + vec;
		return *this;
	}
	Vector3& operator -=(const Vector3& vec) {
		*this = *this + -vec;
		return *this;
	}
	//乗算・除算は下に

	//比較演算子
	bool operator ==(const Vector3& vec) const
	{
		bool temp{
			x == vec.x &&
			y == vec.y &&
			z == vec.z
		};
		return temp;
	}
	bool operator !=(const Vector3& vec) const { return!(*this == vec); }

	//添え字演算子
	float operator [](const std::size_t& index) const
	{
		if (index == 0) return this->x;
		if (index == 1) return this->y;
		if (index == 2) return this->z;

		//範囲外参照
		return 0.0f;
	}
};

inline Vector3 operator *(const Vector3& vec, const float& num) 
{
	Vector3 temp = {
		vec.x * num,
		vec.y * num,
		vec.z * num,
	};
	return temp;
}
inline Vector3 operator *(const float& num, const Vector3& vec)
{
	Vector3 temp = vec * num;
	return temp;
}
inline Vector3 operator *(const Vector3& a, const Vector3& b)
{
	Vector3 temp = {
		a.x * b.x,
		a.y * b.y,
		a.z * b.z
	};
	return temp;
}
inline Vector3 operator /(const Vector3& vec, const float& num)
{
	Vector3 temp = {
			vec.x / num,
			vec.y / num,
			vec.z / num,
	};
	return temp;
}
inline Vector3& operator *=(Vector3& vec, const float& num) {
	vec = vec * num;
	return vec;
}
inline Vector3& operator /=(Vector3& vec, const float& num) {
	vec = vec / num;
	return vec;
}

#pragma endregion