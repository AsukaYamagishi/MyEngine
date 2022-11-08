#pragma once
#include "Vector3.h"
#include <DirectXMath.h>

class Quaternion : public XMFLOAT4
{
public:
#pragma region コンストラクタ
	//成分を指定して生成（非推奨）
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//任意軸周りの回転の指定から生成
	Quaternion(const Vector3& axis_normal, float degree)
	{
		float _sin = sin(degree / 2.0f);
		*this = Quaternion(_sin * axis_normal.x, _sin * axis_normal.y, _sin * axis_normal.z, cos(degree / 2.0f));
	}

#pragma endregion

#pragma region 静的メンバ関数
	/// <summary>
	/// 2つの回転の間の角度を返す
	/// </summary>
	/// <param name="from">測定元</param>
	/// <param name="to">測定先</param>
	/// <returns>角度:degree（float）</returns>
	static float Angle(const Quaternion& from, const Quaternion& to);

	/// <summary>
	/// 2つの回転の内積を返す
	/// </summary>
	/// <returns>内積:degree（float）</returns>
	static float Dot(const Quaternion& lhs, const Quaternion& rhs);

	/// <summary>
	/// オイラー→クォータニオン変換（float3要素）
	/// </summary>
	/// <param name="">roll,pitch,yaw（rad）</param>
	/// <returns>変換後（Quaternion）</returns>
	static Quaternion Euler(const float& roll, const float& pitch, const float& yaw);

	/// <summary>
	/// オイラー→クォータニオン変換（Vector3）
	/// </summary>
	/// <param name="">roll,pitch,yaw（rad）</param>
	/// <returns>変換後（Quaternion）</returns>
	static Quaternion Euler(const Vector3& rotaVector);

	/// <summary>
	/// クォータニオンの正規化（書き換えあり）
	/// </summary>
	/// <returns>正規化したクォータニオン（Quaternion）</returns>
	static Quaternion Normalize(Quaternion& quat);

#pragma endregion

#pragma region メンバ関数
	/// <summary>
	/// 正規化したクォータニオンを返す（書き換えなし）
	/// </summary>
	/// <returns>正規化したクォータニオン（Quaternion）</returns>
	Quaternion Normalized() const;

	/// <summary>
	/// クォータニオン→オイラー変換
	/// </summary>
	/// <returns>オイラー角（Vector3）</returns>
	Vector3 EulerAngles() const;

#pragma endregion

#pragma region 演算子
	//単項演算子オーバーロード
	Quaternion operator +()
	{
		return *this;
	}
	Quaternion operator -()
	{
		Quaternion temp = {
			-this->x,
			-this->y,
			-this->z,
			-this->w
		};
		return temp;
	}

	//代入演算子オーバーロード
	Quaternion& operator +=(const Quaternion& quat)
	{
		this->x += quat.x;
		this->y += quat.y;
		this->z += quat.z;
		this->w += quat.w;

		return *this;
	}
	Quaternion& operator -=(const Quaternion& quat)
	{
		this->x -= quat.x;
		this->y -= quat.y;
		this->z -= quat.z;
		this->w -= quat.w;

		return *this;
	}
	Quaternion& operator *=(float s)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		this->w *= s;

		return *this;
	}
	Quaternion& operator *=(const Quaternion& quat)
	{
		Quaternion temp{
			 this->x * quat.w + this->y * quat.z - this->z * quat.y + this->w * quat.x, //x成分
			-this->x * quat.z + this->y * quat.w + this->z * quat.x + this->w * quat.y, //y成分
			 this->x * quat.y - this->y * quat.x + this->z * quat.w + this->w * quat.z, //z成分
			-this->x * quat.x - this->y * quat.y - this->z * quat.z + this->w * quat.w  //w成分
		};
		*this = temp;
		return *this;
	}
	Quaternion& operator /=(float s)
	{
		return *this *= 1.0f / s;
	}

	//比較演算子
	bool operator ==(const Quaternion& quat) const
	{
		bool temp{
			x == quat.x &&
			y == quat.y &&
			z == quat.z &&
			w == quat.w
		};
		return temp;
	}
	bool operator !=(const Quaternion& quat) const
	{
		return !(*this == quat);
	}

	//添え字演算子
	float& operator [](const std::size_t& index)
	{
		if (index == 0)return this->x;
		if (index == 1)return this->y;
		if (index == 2)return this->z;
		if (index == 3)return this->w;

		//範囲外参照
		assert(0);
	}
};

//二項演算子オーバーロード
inline Quaternion operator +(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion result = q1;
	return result += q2;
}
inline Quaternion operator -(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion result = q1;
	return result -= q2;
}
inline Quaternion operator *(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion result = q1;
	return result *= q2;
}
inline Quaternion operator *(const Quaternion& q, float s)
{
	Quaternion result = q;
	return result *= s;
}
inline Quaternion operator *(float s, const Quaternion& q)
{
	Quaternion result = q;
	return result *= s;
}
inline Quaternion operator /(const Quaternion& q, float s)
{
	Quaternion result = q;
	return result /= s;
}
inline Vector3 operator *(const Quaternion& rota, const Vector3& point)
{
	float x = rota.x * 2.0f;
	float y = rota.x * 2.0f;
	float z = rota.x * 2.0f;
	float xx = rota.x * x;
	float yy = rota.y * y;
	float zz = rota.z * z;
	float xy = rota.x * y;
	float xz = rota.x * z;
	float yz = rota.y * z;
	float wx = rota.w * x;
	float wy = rota.w * y;
	float wz = rota.w * z;

	Vector3 res;
	res.x = (1.0f - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
	res.y = (xy + wz) * point.x + (1.0f - (xx + zz)) * point.y + (yz - wx) * point.z;
	res.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.0f - (xx + yy)) * point.z;
	return res;
}

#pragma endregion