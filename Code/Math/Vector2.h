#pragma once
#include <DirectXMath.h>
#include "Mathf.h"
#include "Vector3.h"
using namespace DirectX;

struct Vector2 : public XMFLOAT2
{
#pragma region コンストラクタ
	Vector2() {
		x = 0.0f;
		y = 0.0f;
	}
	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Vector2(const XMFLOAT3& num) {
		this->x = num.x;
		this->y = num.y;
	}
	Vector2(const XMVECTOR& other) {
		XMVECTOR temp = other;
		XMStoreFloat2(this, temp);
	}
#pragma endregion

#pragma region 静的メンバ変数
	static const Vector2 up;	  //( 0, 1) 上ベクトル
	static const Vector2 down;	  //( 0,-1) 下ベクトル
	static const Vector2 right;	  //( 1, 0) 右ベクトル
	static const Vector2 left;	  //(-1, 0) 左ベクトル
	static const Vector2 zero;	  //( 0, 0) ゼロベクトル
	static const Vector2 one;	  //( 1, 1) 1(単位)ベクトル
	static const Vector2 positive_infinity; //( inf, inf) 正の無限
	static const Vector2 negative_infinity; //(-inf,-inf) 負の無限

#pragma endregion

#pragma region 静的メンバ関数
	/// <summary>
	/// 2点間の角度を求める
	/// </summary>
	/// <param name="from">測定元ベクトル</param>
	/// <param name="to">測定先ベクトル</param>
	/// <returns>角度：degree（float）</returns>
	static float Angle(const Vector2& from, const Vector2& to);

	/// <summary>
	/// 2つのベクトルの内積
	/// </summary>
	/// <returns>内積（float）</returns>
	static float Dot(const Vector2& lhs, const Vector2& rhs);

	/// <summary>
	/// 2つのベクトルの各成分から一番大きな値でベクトルを作成
	/// </summary>
	/// <returns>作成したベクトル（Vector2）</returns>
	static Vector2 Max(const Vector2& lhs, const Vector2& rhs);

	/// <summary>
	/// 2つのベクトルの各成分から一番小さな値でベクトルを作成
	/// </summary>
	/// <returns>作成したベクトル（Vector2）</returns>
	static Vector2 Min(const Vector2& lhs, const Vector2& rhs);

	/// <summary>
	/// ベクトルの大きさを制限
	/// </summary>
	/// <param name="vec">コピーするベクトル</param>
	/// <param name="max_length">最大の大きさ</param>
	/// <returns>大きさを max_length 以下に制限した vec のコピー</returns>
	static Vector2 ClampLength(const Vector2& vec, const float& max_length);

	/// <summary>
	/// 法線で定義された平面でベクトルを反射
	/// </summary>
	/// <param name="inDirection">平面に入る方向ベクトル</param>
	/// <param name="inNormal">平面を定義する正規化済みの垂直ベクトル</param>
	/// <returns>反射後のベクトル（Vector2）</returns>
	static Vector2 Reflect(const Vector2& inDirection, const Vector2& inNormal);

	/// <summary>
	/// 2点間の距離を求める
	/// </summary>
	/// <returns>2点間の距離（float）</returns>
	static float Distance(const Vector2& lhs, const Vector2& rhs);

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
	/// <returns>正規化ベクトル（Vector2）</returns>
	Vector2 Normalized() const;

	/// <summary>
	/// 2つのベクトルの内積(引数1つ)
	/// </summary>
	/// <returns>内積（float）</returns>
	float Dot(const Vector2& vec);

#pragma endregion

#pragma region 演算子
	//単項演算子
	Vector2 operator +() const { return *this; }
	Vector2 operator -() const
	{
		Vector2 temp = {
			-this->x,
			-this->y,
		};
		return temp;
	}

	//二項演算子
	Vector2 operator +(const Vector2& vec) const
	{
		Vector2 temp = {
			this->x + vec.x,
			this->y + vec.y
		};
		return temp;
	}
	Vector2 operator -(const Vector2& vec) const 
	{ 
		return *this + -vec;
	}
	Vector2& operator +=(const Vector2& vec) {
		*this = *this + vec;
		return *this;
	}
	Vector2& operator -=(const Vector2& vec) {
		*this = *this + -vec;
		return *this;
	}
	//乗算・除算は下に

	//比較演算子
	bool operator ==(const Vector2& vec) const
	{
		bool temp{
			x == vec.x &&
			y == vec.y
		};
		return temp;
	}
	bool operator !=(const Vector3& vec) const 
	{
		return !(*this == vec);
	}

	//添え字演算子
	float operator [](const std::size_t& index) const
	{
		if (index == 0) return this->x;
		if (index == 1) return this->y;

		//範囲外参照
		return 0.0f;
	}

	//Vector3へのキャスト
	operator Vector3() const
	{
		Vector3 temp{
			this->x,
			this->y,
			0.0f
		};
		return temp;
	}
};

inline Vector2 operator *(const Vector2& vec, const float& num)
{
	Vector2 temp = {
		vec.x * num,
		vec.y * num
	};
	return temp;
}
inline Vector2 operator *(const float& num, const Vector2& vec)
{
	Vector2 temp = vec * num;
	return temp;
}
inline Vector2 operator *(const Vector2& a, const Vector2& b)
{
	Vector2 temp = {
		a.x * b.x,
		a.y * b.y
	};
	return temp;
}
inline Vector2 operator /(const Vector2& vec, const float& num)
{
	Vector2 temp = {
			vec.x / num,
			vec.y / num
	};
	return temp;
}
inline Vector2& operator *=(Vector2& vec, const float& num) {
	vec = vec * num;
	return vec;
}
inline Vector2& operator /=(Vector2& vec, const float& num) {
	vec = vec / num;
	return vec;
}

#pragma endregion
